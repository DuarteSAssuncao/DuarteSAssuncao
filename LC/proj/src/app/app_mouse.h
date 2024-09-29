/**
 * @file app_mouse.h
 * @brief Declaration of "higher" mouse functions used in the project
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_PROJ_APP_MOUSE_H
#define LCOM_PROJ_APP_MOUSE_H

#include "../interrupts/interrupts.h"

/**
 * @brief This functions handles a penguin
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t (penguin_mouse_handler)();

/**
 * @brief Mouse handler with windows on the screen
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t windows_mouse_handler();

/**
 * @brief Mouse handler of the IPC
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t ipc_mouse_handler();

#endif /* LCOM_PROJ_APP_MOUSE_H */
