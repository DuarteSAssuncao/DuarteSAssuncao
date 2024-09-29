/**
 * @file app_timer.h
 * @brief Declaration of "higher" Timer0 functions used in the project
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_PROJ_APP_TIMER_H
#define LCOM_PROJ_APP_TIMER_H

#include <interrupts/interrupts.h>

/**
 * @brief Resets some timer variables
 * @return void
 */
void (reset_timer)();

/**
 * @brief Handles the interrupts of the Timer0 in the project
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t (timer_handler)();

/**
 * @brief Handles the Timer with windows on the screen
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t timer_windows_handler();

/**
 * @brief Timer handler of the IPC
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t ipc_timer_handler();

#endif /* LCOM_PROJ_APP_TIMER_H */
