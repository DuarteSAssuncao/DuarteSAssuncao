/**
 * @file middleman.c
 * @brief Takes care of connections
 * @author T17_G1
 * @date 29/05/2024
 */

#include "middleman.h"
#include "ipc_codes.h"
#include "protocol.h"
#include "messages.h"
#include "client.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <errno.h>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define DEBUG
//#define DEBUG2
#include <auxiliary/debug.h>

//! Maximum number of sockets
#define MAX_SOCKETS (MAX_CLIENTS + 3)

//! 
static struct pollfd socket_pollfds[MAX_SOCKETS];

//!
#define self_pollfd socket_pollfds[0]

//!
#define self_fd self_pollfd.fd

//! 
#define server_pollfd socket_pollfds[1]

//! 
#define server_fd server_pollfd.fd

//! 
#define winbuf_pollfd socket_pollfds[2]

//!
#define winbuf_fd winbuf_pollfd.fd

//!
#define clients (socket_pollfds + MAX_SOCKETS - MAX_CLIENTS)

//! Number of current clients
static size_t n_clients;

//! Number of sockets
#define n_sockets (n_clients + MAX_SOCKETS - MAX_CLIENTS)

/**
 * @brief Initializes the middleman
 * @return int : 0 on success
 */
int rakoon_middleman_init() {
    // make sure that the socket address is available
    if (unlink(MIDDLEMAN_SOCKET_ADDR) && errno != ENOENT && errno != -ENOENT) {
        DEBUG_ERRORV("unlink(\"%s\"): %s\n", MIDDLEMAN_SOCKET_ADDR, strerror(errno));
        return -1;
    }

    self_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (self_fd == -1) return -1;

    // set up server socket type and address
    struct sockaddr_un self_addr;
    self_addr.sun_family = AF_LOCAL;
    strcpy(self_addr.sun_path, MIDDLEMAN_SOCKET_ADDR);

    DEBUG_INFOV("Binding socket to \"%s\"...\n", self_addr.sun_path);
    if (bind(self_fd, (struct sockaddr*)&self_addr, SUN_LEN(&self_addr)) == -1) {
        close(self_fd); close(server_fd);
        return -1;
    }

    DEBUG_INFOV("Connecting to \"%s\"...\n", MAIN_SOCKET_ADDR);
    if ((server_fd = rakoon_connect(MAIN_SOCKET_ADDR, 10, 100)) == -1) {
        close(self_fd);
        return -1;
    }

    // connect (again) to main socket to transfer buffers separately
    if ((winbuf_fd = rakoon_connect(MAIN_SOCKET_ADDR, 10, 100)) == -1) {
        close(self_fd); close(server_fd);
        return -1;
    }

    // make the socket available for connections (with a queue capacity of 3)
    if (listen(self_fd, 3) == -1) {
        close(self_fd); close(server_fd); close(winbuf_fd);
        return -1;
    }

    // create initial client (home/desktop)
    int pid = fork();
    if (pid == 0) {
        DEBUG_INFOV("Forking to execute home...\n");
        execl("home","home",NULL);
        DEBUG_ERRORV("execl on home/desktop executable: %s\n", strerror(errno));
        exit(EXIT_FAILURE); // exit() may be a bad idea
    } else if (pid == -1) {
        DEBUG_ERRORV("fork: %s\n", strerror(errno));
        close(self_fd); close(server_fd); close(winbuf_fd);
        return -1;
    }
    return 0;
}

/**
 * @brief Middleman-sided window struct
 */
typedef struct mwin {
    win_attr_t attr;            /*!< Attributes */

    #ifdef SHARED_WINBUF
        uint8_t *winbuf;        /*!< Window buffer */
        bool waiting_refresh;   /*!< Whether the window is waiting to be refreshed */
    #endif
} mwin_t;

//! Windows (not the OS)
mwin_t wins[MAX_CLIENTS];

static int rakoon_middleman_accept_connection();
static int remove_client(size_t idx, bool notify_server);

/**
 * @brief Starts the middleman
 * @return int : 0 on success
 */
int rakoon_middleman_start() {
    self_pollfd.events = server_pollfd.events = POLLIN;
    rakoon_msg_t msg;
    while (1) {
        for (size_t i = 0; i < n_sockets; ++i)
            socket_pollfds[i].revents = 0;
        int n_fds = poll(socket_pollfds, n_sockets, -1);
        if (n_fds == -1) {
            DEBUG_PERRORV("poll");
            continue;
        }

        if (server_pollfd.revents & POLLIN) {
            int n_bytes = recv(server_fd, &msg, sizeof(msg), MSG_DONTWAIT);
            if (n_bytes != sizeof(msg)) {
                if (n_bytes == 0)
                    return 0;
                else if (n_bytes == -1)
                    DEBUG_PERRORV("recv(server_fd, ...)");
                else
                    DEBUG_ERRORV("recv(server_fd, ...): message size mismatch (%d/%zu)\n", n_bytes, sizeof(msg));
                continue;
            }
            DEBUG_PRINTF2("Midman received server message! (m_type = %d, win_id = %d)\n", msg.m_type, msg.win_id);

            mwin_t *win = NULL;
            size_t i = 0;
            for (; i < n_clients; ++i) {
                if (wins[i].attr.win_id == msg.win_id) {
                    win = wins + i;
                    break;
                }
            }

            switch (msg.m_type) {
                case RKE_CLOSE_WIN:
                    if (win != NULL) {
                        remove_client(i, false);
                        break;
                    }
                    DEBUG_WARNV("Server requested to remove window #%d but it was not found\n", msg.win_id);
                    break;
                case RKE_REFRESH_READY: {
                    int sent = send(winbuf_fd, win->winbuf, win->attr.frame_buffer_size, 0);
                    if (sent == -1) {
                        DEBUG_PERRORV("RKR_UPD_WIN: send");
                        break;
                    }
                    DEBUG_PRINTF2("Midman sent %d/%zu winbuf bytes to server\n", sent, win->attr.frame_buffer_size);
                    win->waiting_refresh = false;
                    break;
                }
                case RKE_WIN_INIT:
                    #ifdef SHARED_WINBUF
                        memcpy(&win->attr, msg.data, sizeof(win->attr));

                        DEBUG_INFOV("Checking for an existing block for win_id = %d...\n", win->attr.win_id);
                        int shmid;
                        win->winbuf = shared_winbuf_get(win->attr.win_id, 1, 0666, &shmid);
                        if (win->winbuf == WINBUF_ALLOC_FAIL) { // likely just doesn't exist
                            DEBUG_INFOV("shared_winbuf_get(size = 1): %s\n", strerror(errno));
                        }
                        else { // buffer already exists!
                            DEBUG_INFOV("Deleting shm block...\n");
                            if (shmctl(shmid, IPC_RMID, NULL))
                                DEBUG_PERRORV("shmctl(cmd = IPC_RMID)");
                        }


                        DEBUG_INFOV("Allocating shared window buffer...\n");
                        win->winbuf = WINBUF_ALLOC(win->attr.win_id, win->attr.frame_buffer_size);
                        if (win->winbuf == WINBUF_ALLOC_FAIL) {
                            DEBUG_PERRORV("RKE_WIN_INIT: WINBUF_ALLOC");
                            remove_client(i, true);
                            break;
                        }
                    #endif /* SHARED_WINBUF */
                    if (send(clients[i].fd, &msg, sizeof(msg), 0) == -1) {
                        DEBUG_PERRORV("RKE_WIN_INIT: Failed to send window attributes to client");
                        remove_client(i, true);
                        break;
                    }
                    break;
                default: {
                    bool found = false;
                    for (size_t i = 0; i < n_clients; ++i)
                        if (wins[i].attr.win_id == msg.win_id) {
                            send(clients[i].fd, &msg, sizeof(msg), 0);
                            found = true;
                            break;
                        }
                    if (!found)
                        DEBUG_WARNV("Server requested to send and event to window #%d but it was not found\n", msg.win_id);
                }
            }
        }

        for (size_t i = 0; i < n_clients; ++i) {
            struct pollfd *client = clients + i;
            if (!client->revents) continue;
            mwin_t *win = wins + i;

            if (client->revents & POLLIN) { // probably received request
                int n_bytes = recv(client->fd, &msg, sizeof(msg), 0);
                if (n_bytes == sizeof(msg)) { // expected case
                    DEBUG_PRINTF2("Midman received client message! (m_type = %d, win_id = %d)\n", msg.m_type, msg.win_id);
                    if (msg.win_id != win->attr.win_id) {
                        DEBUG_WARNV("window #%d provided wrong win_id (%d)\n", win->attr.win_id, msg.win_id);
                        msg.win_id = win->attr.win_id;
                    }
                    switch (msg.m_type) {
                        case RKR_UPD_WIN:
                            if (win->waiting_refresh) {
                                DEBUG_PRINTF2("Window #%d requested refresh before server could even process previous refresh\n", win->attr.win_id);
                                continue;
                            } else win->waiting_refresh = true;
                            break;
                        case RKR_CREATE_WIN:
                            DEBUG_PRINTF2("RKR_CREATE_WIN\n");
                            ((win_attr_t*)msg.data)->win_id = win->attr.win_id;
                            break;
                        case RKR_SEND_SERIAL_PORT_FILE:
                        case RKR_RECEIVE_SERIAL_PORT_FILE:
                            DEBUG_INFOV("%s\n", msg.m_type == RKR_SEND_SERIAL_PORT_FILE ? "RKR_SEND_SERIAL_PORT_FILE" : "RKR_RECEIVE_SERIAL_PORT_FILE");
                            break;
                        default: break;
                    }
                    if (send(server_fd, &msg, sizeof(msg), 0) == -1)
                        DEBUG_PERRORV("send(server_fd, ...)");
                }
                else {
                    if (n_bytes == 0) { // was not actually a request, connection was closed
                        DEBUG_INFOV("Window #%d sent 0 bytes, closing socket...\n", win->attr.win_id);
                        remove_client(i, true);
                    }
                    else if (n_bytes > 0)
                        // TODO: maybe flush queue?
                        DEBUG_ERRORV("recv: message size mismatch (%d/%zu)\n", n_bytes, sizeof(msg));
                    else
                        DEBUG_PERRORV("recv");
                }
            }

            if (client->revents & (POLLHUP | POLLNVAL)) {
                DEBUG_INFOV("Window #%d triggered revents %d, closing socket...\n", win->attr.win_id, client->revents);
                remove_client(i, true);
            }

            client->revents = 0;
        }

        if (self_pollfd.revents & POLLIN)
            if (rakoon_middleman_accept_connection())
                DEBUG_PERRORV("failed to accept connection");
    }
}

/**
 * @brief The middleman accepts the connection (or not)
 * @return int : 0 on success
 */
static int rakoon_middleman_accept_connection() {
    static uint16_t win_id;
    DEBUG_INFOV("Middleman accepting connection...\n");
    struct pollfd *client = clients + n_clients;
    mwin_t *win = wins + n_clients;

    struct sockaddr_un addr;
    socklen_t len = sizeof(addr);
    *client = (struct pollfd) {
        .fd = accept(self_fd, (struct sockaddr*)&addr, &len),
        .events = POLLIN,
    };
    if (client->fd == -1) return -1;
    win->attr.win_id = ++win_id;

    DEBUG_SUCCESSV("Midman connected to client!\n");
    ++n_clients;
    return 0;
}

/**
 * @brief Remove a client from the server
 * @param size_t idx : index of client to remove
 * @param bool notify_server : whether to notify the server
 * @return int : 0 on success
 */
static int remove_client(size_t idx, bool notify_server) {
    if (idx >= n_clients) {
        errno = EINVAL;
        return -1;
    }

    if (close(clients[idx].fd))
        DEBUG_PERRORV("close");
    #ifdef SHARED_WINBUF
    if (WINBUF_DEALLOC(wins[idx].winbuf))
        DEBUG_PERRORV("WINBUF_DEALLOC");
    #endif /* SHARED_WINBUF */

    if (notify_server) {
        rakoon_msg_t msg = {.win_id = wins[idx].attr.win_id, .m_type = RKR_REMOVE_WIN};
        if (send(server_fd, &msg, sizeof(msg), 0) == -1)
            DEBUG_PERRORV("send");
    }

    memmove(clients+idx, clients+idx+1, sizeof(*clients)*(n_clients-idx-1));
    memmove(wins+idx, wins+idx+1, sizeof(*wins)*(n_clients-idx-1));
    --n_clients;
    return 0;
}

/**
 * @brief Cleans up the middleman
 * @return void
 */
void rakoon_middleman_cleanup() {
    for (size_t i = 0; i < n_sockets; ++i)
        if (close(socket_pollfds[i].fd))
            DEBUG_ERRORV("Failed to close socket #%zu (fd = %d): %s\n", i, socket_pollfds[i].fd, strerror(errno));
    #ifdef SHARED_WINBUF
    for (size_t i = 0; i < n_clients; ++i)
        if (WINBUF_DEALLOC(wins[i].winbuf))
            DEBUG_ERRORV("WINBUF_DEALLOC on window #%d: %s\n", wins[i].attr.win_id, strerror(errno));
    if (unlink(MIDDLEMAN_SOCKET_ADDR))
        DEBUG_PERRORV("unlink");
    #endif /* SHARED_WINBUF */
}
