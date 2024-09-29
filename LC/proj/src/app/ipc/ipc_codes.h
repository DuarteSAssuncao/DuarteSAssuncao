/**
 * @file ipc_codes.h
 * @brief Codes (macros) related to Inter Process Communication
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef LCOM_PROJ_RAKOON_IPC_CODES_H
#define LCOM_PROJ_RAKOON_IPC_CODES_H

/**
 * @brief Enum for requests that a window can send (RKR stands for RaKoonRequest)
 */
typedef enum rakoon_req {
    RKR_CREATE_WIN, /*!< Create a window */
    RKR_REMOVE_WIN, /*!< Remove a window */
    RKR_UPD_WIN,    /*!< Update window */
    RKR_SET_ATTR,   /*!< Set window attributes */
    RKR_SEND_SERIAL_PORT_FILE,
    RKR_RECEIVE_SERIAL_PORT_FILE,
} rakoon_req_t;

/**
 * @brief Enum for events that a window may receive (RKE stands for RaKoonEvent)
 * @note MANY OF THESE MIGHT NOT BE IMPLEMENTED YET
 */
typedef enum rakoon_ev {
    RKE_MOUSE,          /*!< Mouse event */
    RKE_KEYBOARD,       /*!< Keyboard event */
    RKE_CLOSE_WIN,      /*!< Request to close window */
    RKE_SET_ATTR,       /*!< Request to set attributes */
    RKE_WIN_INIT,       /*!< Request to initialize a window */
    RKE_RESIZE,         /*!< The window was resized */
    RKE_SHUTDOWN,       /*!< Window was forced to close (calling win_close() is still valid and recommended, though) */
    RKE_REFRESH_READY,  /*!< Window is ready to be refreshed */
} rakoon_ev_t;

#endif /* LCOM_PROJ_RAKOON_IPC_CODES_H */
