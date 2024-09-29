/**
 * @file server.c
 * @brief Definition of server functions
 * @author T17_G1
 * @date 29/05/2024
 */

#include "server.h"
#include "protocol.h"
#include "ipc_codes.h"
#include <app/shared.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <serial_port/sp_ih.h>

#define DEBUG
//#define DEBUG2
#include <auxiliary/debug.h>

//! Maximum number of sockets
#define MAX_SOCKETS (MAX_CLIENTS + 3)

//! Array of windows
extern _win_t wins[MAX_CLIENTS];

//! 
static int socket_fds[MAX_SOCKETS];

//!
#define clients (socket_fds + MAX_SOCKETS - MAX_CLIENTS)

//!
#define n_sockets (n_windows + MAX_SOCKETS - MAX_CLIENTS)

//!
#define server_fd socket_fds[0]

//!
#define midman_fd socket_fds[1]

//!
#define winbuf_fd socket_fds[2]

//! Whether the server is active
bool server_on;

/**
 * @brief Initializes the socket which will be used to communicate with multiple windows
 * @return 0 on success, otherwise errno is set and -1 is returned
 */
int server_init() {
    struct sockaddr_un server_addr, client_addr;

    // make sure that the socket address is available
    if (unlink(MAIN_SOCKET_ADDR) && errno != ENOENT && errno != -ENOENT) return -1;

    server_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (server_fd == -1) return -1;

    // set up server socket type and address
    server_addr.sun_family = AF_LOCAL;
    strcpy(server_addr.sun_path, MAIN_SOCKET_ADDR);

    // bind/associate socket to the address
    if (bind(server_fd, (struct sockaddr *)&server_addr, SUN_LEN(&server_addr)) == -1) {
        close(server_fd);
        return -1;
    }
    // make the socket available for connections (with a queue capacity of 3)
    if (listen(server_fd, 3) == -1) {
        close(server_fd);
        return -1;
    }
    // connect to middleman
    socklen_t len = sizeof(client_addr);
    if ((midman_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len)) == -1) {
        close(server_fd);
        return -1;
    }
    // connect (again) to middleman to transfer buffers separately -> avoids interference
    if ((winbuf_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len)) == -1) {
        close(server_fd);
        return -1;
    }
    server_on = true;
    return 0;
}

/**
 * @brief Handles requests made by windows
 * @return int : 0 on success
 */
int server_handle_requests() {
    rakoon_msg_t msg;
    // TODO: read multiple messages at once
    int n_bytes = recv(midman_fd, &msg, sizeof(msg), MSG_DONTWAIT);
    if (n_bytes == -1) { // probably has nothing to receive
        if (errno == EWOULDBLOCK || errno == -EWOULDBLOCK || errno == EAGAIN || errno == -EAGAIN)
            return 0; // nothing to receive
        DEBUG_PERRORV("recv(midmad_fd, ...)");
        return -1; // recv() error
    }
    else if (n_bytes == 0) { // middleman closed connection (for whatever reason)
        return 1;
    }
    else if (n_bytes != sizeof(msg)) {
        DEBUG_ERRORV("recv: message size mismatch (%d/%zu)\n", n_bytes, sizeof(msg));
        errno = EPROTO;
        return -1;
    }

    DEBUG_PRINTF2("Main socket received message!\n");

    size_t i = 0; while (wins[i].attr.win_id != msg.win_id && i < n_windows) ++i;
    DEBUG_INFOV("msg.m_type = %d\n", msg.m_type);
    switch (msg.m_type) {
        case RKR_CREATE_WIN: {
            struct sockaddr_un client_addr;
            socklen_t len = sizeof(client_addr);
            DEBUG_INFOV("Waiting for connection to new window...\n");
            _win_t new_win = {.fd = accept(server_fd, (struct sockaddr*)&client_addr, &len)};
            if (new_win.fd == -1) {
                close(new_win.fd);
                DEBUG_PERRORV("accept");
                break;
            }
            win_attr_t *attr = (win_attr_t*)&new_win.attr;
            memcpy(attr, msg.data, sizeof(new_win.attr));

            // TODO: adjust other attributes
            attr->bytes_per_pixel = 4;
            attr->n_buffers = 1;
            attr->frame_buffer_size = attr->width * attr->height * attr->bytes_per_pixel;

            new_win.winbuf = calloc(1, attr->frame_buffer_size);
            if (new_win.winbuf == NULL) {
                close(new_win.fd);
                DEBUG_PERRORV("malloc");
                break;
            }
            DEBUG_INFOV("Sending adjusted attributes to middleman...\n");
            msg.m_type = RKE_WIN_INIT;
            memcpy(msg.data, attr, sizeof(*attr));
            send(midman_fd, &msg, sizeof(msg), 0);

            memmove(wins+1, wins, sizeof(*wins)*n_windows);
            memmove(clients+1, clients, sizeof(*clients)*n_windows);
            memcpy(wins, &new_win, sizeof(new_win));
            clients[0] = wins[0].fd;
            ++n_windows;
            break;
        }
        case RKR_REMOVE_WIN: {
            bool found = false;
            for (size_t i = 0; i < n_windows; ++i) {
                if (wins[i].attr.win_id == msg.win_id) {
                    if (remove_client_(i, false))
                        DEBUG_ERRORV("Main socket failed to remove window #%zu: %s\n", i, strerror(errno));
                    found = true;
                    break;
                }
            }
            if (!found)
                DEBUG_WARNV("Middleman requested to remove window #%d but it was not found\n", msg.win_id);
            break;
        }
        case RKR_UPD_WIN: {
            if (i > n_windows) break;
            int to_receive = (int) wins[i].attr.frame_buffer_size;
            uint8_t *ptr = wins[i].winbuf;

            rakoon_msg_t msg_to_send = {.win_id = wins[i].attr.win_id, .m_type = RKE_REFRESH_READY};
            if (send(midman_fd, &msg_to_send, sizeof(msg_to_send), 0) == -1) {
                DEBUG_ERRORV("Server failed to notify midman to refresh window #%d: %s\n", wins[i].attr.win_id, strerror(errno));
                break;
            }

            do {
                int n_bytes = recv(winbuf_fd, ptr, to_receive, 0);
                if (n_bytes == -1) {
                    DEBUG_ERRORV("Failed to recv() frame buffer from window #%zu: %s\n", i, strerror(errno));
                    break;
                } else if (n_bytes == 0) {
                    DEBUG_WARNV("RKR_UPD_WIN: Midman closed connection while passing frame buffer\n");
                    break;
                }
                to_receive -= n_bytes;
                ptr += n_bytes;
            } while (to_receive > 0);
            update_screen = true;
            DEBUG_PRINTF2("Received %zd/%zu bytes from window #%d\n", ptr - wins[i].winbuf, wins[i].attr.frame_buffer_size, wins[i].attr.win_id);
            break;
        }
        case RKR_SEND_SERIAL_PORT_FILE:
        case RKR_RECEIVE_SERIAL_PORT_FILE:
            DEBUG_INFOV("msg.m_type = %d\n", msg.m_type);
            DEBUG_INFOV("%s\n", msg.m_type == RKR_SEND_SERIAL_PORT_FILE ? "RKR_SEND_SERIAL_PORT_FILE" : "RKR_RECEIVE_SERIAL_PORT_FILE");
            if (is_locked()) {
                DEBUG_WARNV("Serial port is already in use!\n");
                break;
            }
            uint8_t stance = msg.m_type == RKR_SEND_SERIAL_PORT_FILE ? SENDER : RECEIVER;
            DEBUG_PRINTF("stance = %d\n", stance);
            FILE *fp = fopen(SERIAL_PORT_PATH, "r");
            if (fp == NULL) {
                DEBUG_PERRORV("fopen(SERIAL_PORT_PATH, \"r\")");
                break;
            }
            char fullpath[1024];
            fgets(fullpath, sizeof(fullpath), fp);
            DEBUG_INFOV("Serial port origin/destination path: \"%s\"\n", fullpath);

            if (stance == SENDER) {
                if (set_origin_file(fopen(fullpath, "w")))
                    DEBUG_PERRORV("set_origin_file");
            } else {
                if (set_destination_file(fopen(fullpath, "r")))
                    DEBUG_PERRORV("set_destination_file");
            }

            if (set_stance(stance)) {
                DEBUG_PERRORV("set_stance");
                break;
            }

            DEBUG_SUCCESSV("Initialized serial port\n");
            break;
        default:
            DEBUG_WARNV("Invalid/unhandled message code %d from middleman\n", msg.m_type);
    }
    return 0;
}

/**
 * @brief Send events to the middleman
 * @return int : 0 on success
 */
int server_send_events() {
    if (msgbufsize == 0) return 0; // sending 0 bytes counts as closing the connection
    // TODO: non-blocking I/O
    if (send(midman_fd, msgbuf, sizeof(*msgbuf)*msgbufsize, 0) == -1) {
        DEBUG_PERRORV("send");
        return -1;
    }
    msgbufsize = 0;
    return 0;
}

/**
 * @brief Remove a client
 * @param size_t idx : index of client to remove
 * @param bool notify_middleman : whether to notify the middleman about the removal
 * @return int : 0 on success
 */
int remove_client_(size_t idx, bool notify_middleman) {
    if (idx >= n_windows) {
        errno = EINVAL;
        return -1;
    }
    close(clients[idx]);
    free(wins[idx].winbuf);
    if (notify_middleman) {
        rakoon_msg_t msg = {.m_type = RKE_CLOSE_WIN, .win_id = wins[idx].attr.win_id};
        send(midman_fd, &msg, sizeof(msg), 0);
    }
    memmove(clients+idx, clients+idx+1, sizeof(*clients)*(n_windows-idx-1));
    memmove(wins+idx, wins+idx+1, sizeof(*wins)*(n_windows-idx-1));
    --n_windows;
    return 0;
}

/**
 * @brief Set a window as the top one (the one with focus)
 * @param size_t idx : the index of the window to set on top
 * @return int : 0 on success
 */
int win_set_top(size_t idx) {
    if (idx == 0) {
        DEBUG_PRINTF2("Window already was on top!\n");
        return 0;
    }
    if (idx >= n_windows)
        return EINVAL;
    _win_t tmp_win = wins[idx];
    int tmp_fd = clients[idx];
    memmove(wins + 1, wins, idx * sizeof(*wins));
    memmove(clients + 1, clients, idx * sizeof(*clients));
    wins[0] = tmp_win;
    clients[0] = tmp_fd;
    return 0;
}

/**
 * @brief Cleans up the server by freeing memory and closing sockets
 * @return void
 */
void server_cleanup() {
    if (!server_on)
        return;

    for (size_t i = 0; i < n_windows; ++i)
        free(wins[i].winbuf);
    for (size_t i = 0; i < n_sockets; ++i)
        if (close(socket_fds[i]) == -1)
            DEBUG_ERRORV("failed to close socket #%zu (fd = %d): %s\n", i, socket_fds[i], strerror(errno));
}
