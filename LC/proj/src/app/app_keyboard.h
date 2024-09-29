/**
 * @file app_keyboard.h
 * @brief Declaration of "higher" functions used in the project related to the keyboard
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_PROJ_APP_KEYBOARD_H
#define LCOM_PROJ_APP_KEYBOARD_H

#include "../interrupts/interrupts.h"

#define MOD_ALT             BIT(0)  /*!< ALT is clicked */
#define MOD_CTRL            BIT(1)  /*!< CTRL is clicked */
#define MOD_SHIFT           BIT(2)  /*!< SHIFT is clicked */
#define MOD_CAPSLOCK        BIT(3)  /*!< CAPSLOCK is clicked */

#define HOLD_LALT           BIT(0)  /*!< Left ALT is being hold */
#define HOLD_RALT           BIT(1)  /*!< Right ALT is being hold */
#define HOLD_LCTRL          BIT(2)  /*!< Left CTRL is being hold */
#define HOLD_RCTRL          BIT(3)  /*!< Right CTRL is being hold */
#define HOLD_LSHIFT         BIT(4)  /*!< Left SHIFT is being hold */
#define HOLD_RSHIFT         BIT(5)  /*!< Right SHIFT is being hold */
#define HOLD_CAPSLOCK       BIT(6)  /*!< CAPSLOCK is being hold */

/**
 * @brief Handler of the keyboard in the project
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t proj_keyboard_handler();

/**
 * @brief Debug function for the keyboard (when it wasn't working)
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t debug_keyboard_handler();

/**
 * @brief This functions handles a penguin
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t penguin_keyboard_handler();

/**
 * @brief Handles the keyboard with windows on the screen
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t windows_keyboard_handler();

/**
 * @brief Keyboard handler of the IPC
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t ipc_keyboard_handler();

#endif /* LCOM_PROJ_APP_KEYBOARD_H */
