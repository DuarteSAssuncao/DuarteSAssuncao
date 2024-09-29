/**
 * @file server.h
 * @brief Declaration of server functions
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef LCOM_PROJ_IPC_SERVER_H
#define LCOM_PROJ_IPC_SERVER_H

#include "messages.h"
#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Server-side window info
 */
typedef struct _win {
    int fd;             /*!< socket file descriptor */
    win_attr_t attr;    /*!< window attributes (x,y,width,height,etc.) */
    uint8_t *winbuf;    /*!< window buffer */
} _win_t;

/**
 * @brief Initializes the socket which will be used to communicate with multiple windows
 * @return 0 on success, otherwise errno is set and -1 is returned
 */
int server_init();

/**
 * @brief Handles a request
 * @return int : 0 on success
 */
int server_handle_requests();

/**
 * @brief Send events to the middleman
 * @return int : 0 on success
 */
int server_send_events();

/**
 * @brief Remove a client
 * @param size_t idx : index of client to remove
 * @param bool notify_middleman : whether to notify the middleman about the removal
 * @return int : 0 on success
 */
int remove_client_(size_t idx, bool notify_middleman);
#define remove_client(idx) remove_client_(idx,true)

/**
 * @brief Puts the window at the specified index on top of every other window
 * @return 0 on success, non-zero otherwise
 */
int win_set_top(size_t idx);

/**
 * @brief Cleans up the server by freeing memory and closing sockets
 * @return void
 */
void server_cleanup();

#endif /* LCOM_PROJ_IPC_BACKEND_H */
