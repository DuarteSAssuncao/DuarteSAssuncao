/**
 * @file interrupts.h
 * @brief Declaration of functions related to handling interrupts
 * @author T17_G1
 * @date 24/05/2024
 */

#ifndef LCOM_PROJ_INTERRUPTS_H
#define LCOM_PROJ_INTERRUPTS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @enum Return values of functions related to interruptions
 */
typedef enum {
    INT_SUCCESS,            /*!< zero, the universal number of success in C */
    INT_ALREADY_ENABLED,    /*!< attempted to enable interrupts of a device that were already enabled */
    INT_ALREADY_DISABLED,   /*!< attempted to disable interrupts of a device that were already disabled */
    INT_WAS_NEVER_ENABLED,  /*!< interrupts were never enabled on the device and therefore cannot be re-enabled */
    INT_UNKNOWN_ERROR,      /*!< an internal error occured but it's not critical (e.g. failed to enable interrupts) */
    INT_BAD,                /*!< an internal error occured that leaves the program in a bad state (e.g. failed to disable interrupts) */
    INT_INVALID_DEVICE      /*!< an invalid value for device_t was provided */
} int_errno_t;

/**
 * @enum Enum used to identify a device for interrupts.
 */
typedef enum {
    TIMER,          /*!< Timer0 - i8254 */
    KEYBOARD,       /*!< KBC - i8042 */
    MOUSE,          /*!< PS/2 - i8042 */
    RTC,            /*!< Real Time Clock */
    SERIAL_PORT,    /*!< UART Serial Port */
    DEVICE_COUNT    /*!< How many devices there are (as it is the last argument of the enum) */
} device_t;

/**
 * @brief Enum used to "speak" to the interrupts loop.
 * When you call interrupts_run(), it repeatedly waits for interrupts and handles them.
 * If your handler returns INT_CONTINUE, the loop will continue normally, while INT_EXIT will make the loop end.
 */
typedef enum {
    INT_CONTINUE,   /*!< Continue the loop normally */
    INT_EXIT,       /*!< End the loop */
} int_ret_t;

typedef int_ret_t (*int_handler_t)();

/**
 * @brief Enables interrupts on the provided device
 * @param device_t device : device in which to subscribe for interruptions
 * @param int_handler_t handler : function to call in case of an interruption
 * @return int : INT_SUCCESS if successful
 */
int (interrupts_enable)(device_t device, int_handler_t handler);

/**
 * @brief Unsubscribe on a device
 * @param device_t device : on where to unsubscribe
 * @return int : INT_SUCCESSFUL if successful
 */
int (interrupts_disable)(device_t device);

/**
 * @brief Unsubscribes all interrupts on all subscribed devices
 * @return int : INT_SUCCESS if successful
 * @note In case of error, it will either return INT_BAD or the last error occured.
 */
int (interrupts_disable_all)();

/**
 * @brief Resubscribes a certain device
 * @param device_t device : where to resubscribe
 * @return int : INT_SUCCESS if successful
 */
int (interrupts_reenable)(device_t device);

/**
 * @brief Check if the device is currently subscribed
 * @param device_t device : where to check if is subscribed
 * @return bool : whether the device is subscribed
 */
bool (interrupts_check_enabled)(device_t device);

/*
 * @brief Subscribes if unsubscribed and vice-versa
 * @param device_t device : where to toggle subscriptions
 * @return int : INT_SUCCESSFUL if managed to toggle subscriptions
 */
int (interrupts_toggle)(device_t device);

/**
 * @brief Main function - calls interrupt handles if there was an interruption of their type
 * @return int : INT_SUCCESS if function completed successfully
 */
int (interrupts_run)();

/**
 * @brief What to print in each situation
 * @param int_errno_t int_errno : Value returned from interruption-related function
 * @return const char* : Char* to return depending on input
 */
const char *(int_strerror)(int_errno_t int_errno);

/**
 * @brief Turn the device name (enum) to a char* (string)
 * @param device_t device : device to turn to string
 * @return const char* : device name
 */
const char *(device_to_str)(device_t);

#endif /* LCOM_PROJ_INTERRUPTS_H */
