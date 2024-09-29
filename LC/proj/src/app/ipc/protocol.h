/**
 * @file protocols.h
 * @brief Macros and a function associated with allocating memory for a window buffer
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef LCOM_PROJ_IPC_PROTOCOL_H
#define LCOM_PROJ_IPC_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>

//! Maximum number of clients
#define MAX_CLIENTS 64

//! Address of the main socket
#define MAIN_SOCKET_ADDR "/tmp/sock"

//! Address of the middleman socket
#define MIDDLEMAN_SOCKET_ADDR "/tmp/middleman"

//! Used to define/get the path of the origin or destination of the file transfer
#define SERIAL_PORT_PATH "/tmp/serial_port_path"

#define SHARED_WINBUF
#ifdef SHARED_WINBUF
    /**
     * @brief Allocates memory for a shared window buffer
     * @param int win_id : id of the window
     * @param size_t size : size of the allocated memory
     * @return void* : location in memory
     */
    void* shared_winbuf_alloc(int win_id, size_t size);

    /**
     * @brief Gets the shared window buffer
     * @param int win_id : id of the window
     * @param size_t size : size of the allocated memory
     * @param int flags : flags to pass to shmget
     * @param int *resulting_shmid : to hold the identifier of the shared memory
     * @return void* : location in memory
     */
    void* shared_winbuf_get(int win_id, size_t size, int flags, int *resulting_shmid);
    #define WINBUF_ALLOC(win_id, size) shared_winbuf_alloc(win_id, size)
    #define WINBUF_ALLOC_FAIL NULL
    #define WINBUF_DEALLOC(winbuf) shmdt(winbuf)
#else
    #define WINBUF_ALLOC(win_id,size) calloc(1,size)
    #define WINBUF_ALLOC_FAIL NULL
    #define WINBUF_DEALLOC(winbuf) free(winbuf)
#endif /* SHARED_WINBUF */

#endif /* LCOM_PROJ_IPC_PROTOCOL_H */
