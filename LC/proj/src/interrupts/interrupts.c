/**
 * @file interrupts.c
 * @brief Definition of functions related to handling interrupts
 * @author T17_G1
 * @date 24/05/2024
 */

#include <lcom/lcf.h>
#include "interrupts.h"
#include "kbc_i8042.h"
#include "timer_i8254.h"
#include <lab6/rtc.h>
#include <lab6/rtc_macros.h>
#include <serial_port/sp_ih.h>
#include <serial_port/uart.h>

//#define DEBUG
#include <auxiliary/debug.h>

//! Information about each subscription
typedef struct int_info {
    int hook_id;            /*!< ID of the interrupt (when subscribing) */
    void (*ih)();           /*!< under-the-hood interrupt handler */
    int_handler_t handler;  /*!< application interrupt handler */
    bool is_enabled;        /*!< Whether the subscription is active */
} int_info_t;

//! Contains info about each device's interrupts, their index represents the bitno
static int_info_t interrupts[DEVICE_COUNT] = {
    [TIMER].ih = timer_int_handler,
    [KEYBOARD].ih = kbc_ih,
    [MOUSE].ih = mouse_ih,
    [RTC].ih = rtc_ih,
    [SERIAL_PORT].ih = serial_ih,
};

//! Amound of devices with enabled interrupts
static uint8_t enabled_interrupts = 0;

/**
 * @brief Enables interrupts on the provided device
 * @param device_t device : device in which to subscribe for interruptions
 * @param int_handler_t handler : function to call in case of an interruption
 * @return int : INT_SUCCESS if successful
 */
int (interrupts_enable)(device_t device, int_handler_t handler) {
    if (device >= DEVICE_COUNT) 
        return INT_INVALID_DEVICE;

    int_info_t *info = &interrupts[device];

    if (info->is_enabled) 
        return INT_ALREADY_ENABLED;

    info->hook_id = device;
    switch (device) {
        case TIMER:
            if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &info->hook_id))
                return INT_UNKNOWN_ERROR;
            break;
        case KEYBOARD:
            if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &info->hook_id))
                return INT_UNKNOWN_ERROR;
            break;
        case MOUSE:
            if (kbc_mouse_write(MOUSE_ENABLE_DATA_REPORTING))
                return INT_UNKNOWN_ERROR;
            if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &info->hook_id))
                return INT_UNKNOWN_ERROR;
            break;
        case RTC:
            if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &info->hook_id))
                return INT_UNKNOWN_ERROR;
            break;
        case SERIAL_PORT:
            if (sys_irqsetpolicy(COM1_IRQ, IRQ_REENABLE, &info->hook_id))
                return INT_UNKNOWN_ERROR;
            break;
        default:
            return INT_INVALID_DEVICE;
    }
    info->is_enabled = true;
    info->handler = handler;
    ++enabled_interrupts;
    return INT_SUCCESS;
}

/**
 * @brief Unsubscribe on a device
 * @param device_t device : on where to unsubscribe
 * @return int : INT_SUCCESSFUL if successful
 */
int (interrupts_disable)(device_t device) {
    if (device >= DEVICE_COUNT) 
        return INT_INVALID_DEVICE;

    int_info_t *info = &interrupts[device];

    if (!info->is_enabled) 
        return INT_ALREADY_DISABLED;
    
    if (sys_irqrmpolicy(&info->hook_id)) 
        return INT_BAD;

    --enabled_interrupts;
    info->is_enabled = false;

    switch (device) {
        case MOUSE:
            if (kbc_mouse_write(MOUSE_DISABLE_DATA_REPORTING))
                return INT_UNKNOWN_ERROR;
            break;
        case RTC:
            if (rtc_disable_interrupts())
                return INT_BAD;
            break;
        default: break;
    }
    if (device == MOUSE && kbc_mouse_write(MOUSE_DISABLE_DATA_REPORTING))
        return INT_UNKNOWN_ERROR;

    return INT_SUCCESS;
}

/**
 * @brief Unsubscribes all interrupts on all subscribed devices
 * @return int : INT_SUCCESS if successful
 */
int (interrupts_disable_all)() {
    int retv = INT_SUCCESS, r;
    for (int i = 0; i < DEVICE_COUNT; ++i) {
        if (interrupts[i].is_enabled) {
            r = interrupts_disable(i);
            if (r != INT_SUCCESS && retv != INT_BAD) // don't overwrite INT_BAD
                retv = r;
        }
    }
    return retv;
}

/**
 * @brief Resubscribes a certain device
 * @param device_t device : where to resubscribe
 * @return int : INT_SUCCESS if successful
 */
int (interrupts_reenable)(device_t device) {
    if (device >= DEVICE_COUNT) 
        return INT_INVALID_DEVICE;

    if (interrupts[device].handler == NULL) 
        return INT_WAS_NEVER_ENABLED;

    return interrupts_enable(device, interrupts[device].handler);
}

/**
 * @brief Check if the device is currently subscribed
 * @param device_t device : where to check if is subscribed
 * @return bool : whether the device is subscribed
 */
bool (interrupts_check_enabled)(device_t device) {
    return device >= DEVICE_COUNT ? false : interrupts[device].is_enabled;
}

/*
 * @brief Subscribes if unsubscribed and vice-versa
 * @param device_t device : where to toggle subscriptions
 * @return int : INT_SUCCESSFUL if managed to toggle subscriptions
 */
int (interrupts_toggle)(device_t device) {
    if (device >= DEVICE_COUNT) 
        return INT_INVALID_DEVICE;

    if (interrupts[device].is_enabled) 
        return interrupts_disable(device);
    else if (interrupts[device].handler == NULL) 
        return INT_WAS_NEVER_ENABLED;
    else 
        return interrupts_reenable(device);
}

/**
 * @brief Main function - calls interrupt handles if there was an interruption of their type
 * @return int : INT_SUCCESS if function completed successfully
 */
int (interrupts_run)() {
    int ipc_status;
    message msg;
    while(enabled_interrupts > 0) {
        while(driver_receive(ANY, &msg, &ipc_status));
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            uint64_t bit = 1;
            for (int i = 0; i < DEVICE_COUNT; ++i, bit <<= 1) {
                if (msg.m_notify.interrupts & bit) {
                    interrupts[i].ih();
                    if (interrupts[i].handler == NULL) {
                        DEBUG_ERRORV("%s handler is NULL despite being enabled\n", device_to_str(i));
                        continue;
                    }
                    switch (interrupts[i].handler()) {
                        case INT_CONTINUE:
                            break;
                        case INT_EXIT:
                            return 0;
                    }
                }
            }
        }
    }
    return INT_SUCCESS;
}

/**
 * @brief What to print in each situation
 * @param int_errno_t int_errno : Value returned from interruption-related function
 * @return const char* : Char* to return depending on input
 */
const char *(int_strerror)(int_errno_t int_errno) {
    switch (int_errno) {
        case INT_SUCCESS: return "Success";
        case INT_ALREADY_ENABLED: return "Interrupts for the device were already enabled";
        case INT_ALREADY_DISABLED: return "Interrupts for the device were already disabled";
        case INT_WAS_NEVER_ENABLED: return "Interrupts for the device were never enabled";
        case INT_UNKNOWN_ERROR: return "Unable to perform action due to an internal error";
        case INT_BAD: return "Run.";
        case INT_INVALID_DEVICE: return "An invalid device ID was provided";
        default: return "Invalid error number";
    }
}

/**
 * @brief Turn the device name (enum) to a char* (string)
 * @param device_t device : device to turn to string
 * @return const char* : device name
 */
const char *(device_to_str)(device_t device) {
    switch (device) {
        case TIMER: return "timer";
        case KEYBOARD: return "keyboard";
        case MOUSE: return "mouse";
        case RTC: return "rtc";
        default: return "invalid device";
    }
}
