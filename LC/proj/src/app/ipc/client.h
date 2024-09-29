/**
 * @file client.h
 * @brief Declaration of a function to handle a client
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef LCOM_PROJ_IPC_CLIENT_H
#define LCOM_PROJ_IPC_CLIENT_H

#include <stdlib.h>

/**
 * @brief The Rakoon tries to connect to a client
 * @param const char *addr : where to connect to (using sockets)
 * @param int n_attempts : maximum number of tries before error
 * @param int delay_millis : delay between polls
 * @return int : fd on success, otherwise -1
 */
int rakoon_connect(const char *addr, int n_attempts, int delay_millis);

#endif /* LCOM_PROJ_IPC_CLIENT_H */
