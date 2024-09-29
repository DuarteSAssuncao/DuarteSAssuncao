/**
 * @file client.c
 * @brief Definition of a function to handle a client
 * @author T17_G1
 * @date 29/05/2024
 */

#include "client.h"
#include "protocol.h"

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/poll.h>

#define DEBUG
#include <auxiliary/debug.h>

/**
 * @brief The Rakoon tries to connect to a client
 * @param const char *addr : where to connect to (using sockets)
 * @param int n_attempts : maximum number of tries before error
 * @param int delay_millis : delay between polls
 * @return int : fd on success, otherwise -1
 */
int rakoon_connect(const char *addr, int n_attempts, int delay_millis) {
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd == -1) return -1;

    struct sockaddr_un sockaddr = {.sun_family = AF_LOCAL};
    strcpy(sockaddr.sun_path, addr);

    int i = 1;
    while (1) {
        if (connect(fd, (struct sockaddr*)&sockaddr, SUN_LEN(&sockaddr)) == 0) {
            DEBUG_SUCCESSV("Connection to %s successful!\n", addr);
            break;
        }
        DEBUG_WARNV("Attempt #%d to connect to %s failed: %s\n", i, addr, strerror(errno));
        if (++i > n_attempts) {
            DEBUG_ERRORV("Gave up trying to connect to %s after %d attempts\n", addr, n_attempts);
            close(fd);
            errno = ETIMEDOUT;
            return -1;
        }
        struct pollfd pollfd = {.fd = fd};
        DEBUG_INFOV("Retrying in %dms...\n", delay_millis);
        poll(&pollfd, 1, delay_millis); // sleep and usleep are undefined
    }

    return fd;
}
