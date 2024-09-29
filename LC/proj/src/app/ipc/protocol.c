/**
 * @file protocol.c
 * @brief Allocates memory for a shared window buffer
 * @author T17_G1
 * @date 29/05/2024
 */

#include "protocol.h"
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

#define DEBUG
#include <auxiliary/debug.h>

#define WINBUF_FTOK_PATH MAIN_SOCKET_ADDR

#ifdef SHARED_WINBUF

/**
 * @brief Allocates memory for a shared window buffer
 * @param int win_id : id of the window
 * @param size_t size : size of the allocated memory
 * @return void* : location in memory
 */
void* shared_winbuf_alloc(int win_id, size_t size) {
    DEBUG_PRINTF("%s(win_id = %d, size = %zu)\n", __func__, win_id, size);
    int key = ftok(WINBUF_FTOK_PATH, win_id);
    if (key == -1) {
        DEBUG_PERRORV("ftok");
        return NULL;
    }
    DEBUG_PRINTF("key = %d\n", key);

    int shmid = shmget(key, size, 0666 | IPC_CREAT);
    if (shmid == -1) {
        DEBUG_PERRORV("shmget");
        return NULL;
    }
    DEBUG_PRINTF("shmid = %d\n", shmid);

    void *shm = shmat(shmid, NULL, 0);
    if (shm == (void*)-1) {
        DEBUG_PERRORV("shmat");
        return NULL;
    }

    return shm;
}

/**
 * @brief Gets the shared window buffer
 * @param int win_id : id of the window
 * @param size_t size : size of the allocated memory
 * @param int flags : flags to pass to shmget
 * @param int *resulting_shmid : to hold the identifier of the shared memory
 * @return void* : location in memory
 */
void* shared_winbuf_get(int win_id, size_t size, int flags, int *resulting_shmid) {
    DEBUG_PRINTF("%s(win_id = %d, size = %zu)\n", __func__, win_id, size);
    int key = ftok(WINBUF_FTOK_PATH, win_id);
    if (key == -1) {
        DEBUG_PERRORV("ftok");
        return WINBUF_ALLOC_FAIL;
    }
    DEBUG_PRINTF("key = %d\n", key);

    int shmid = shmget(key, size, flags);
    if (shmid == -1) {
        DEBUG_PERRORV("shmget");
        return WINBUF_ALLOC_FAIL;
    }
    DEBUG_PRINTF("shmid = %d\n", shmid);
    if (resulting_shmid != NULL)
        *resulting_shmid = shmid;

    void *shm = shmat(shmid, NULL, 0);
    if (shm == (void*)-1) {
        DEBUG_PERRORV("shmat");
        return WINBUF_ALLOC_FAIL;
    }

    return shm;
}

#endif /* SHARED_WINBUF */
