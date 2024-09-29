/**
 * @file kbc_i8042.c
 * @brief Definition of functions used with the KBC
 * @author T17_G1
 * @date 24/05/2024
 */

#include "kbc_i8042.h"

#define DEBUG
#include <auxiliary/debug.h>

static bool mouse_enabled;

/**
 * @brief Writes a byte on the specified port of the KBC. Tries a constant number of times
 * @param int port : where to write the byte
 * @param uint8_t byte : byte to write
 * @return 0 on success, non-zero otherwise.
 */
static int (kbc_write)(int port, uint8_t byte) {
    uint8_t status;
    for (uint32_t tries = KBC_ATTEMPTS; tries > 0; --tries) {
        if (util_sys_inb(KBC_STAT_REG, &status)) return 1;
        if (!(status & KBC_ST_IBF)) return sys_outb(port, byte);
        tickdelay(micros_to_ticks(KBC_DELAY_MICROSECONDS));
    }
    return ETIMEDOUT;
}

/**
 * @brief Write a command to the KBC
 * @param uint8_t byte : byte to write
 * @return int : 0 on success, non-zero otherwise
 */
int (kbc_write_cmd)(uint8_t byte) {
    return kbc_write(KBC_IN_CMD, byte);
}

/**
 * @brief Write an argument to the KBC
 * @param uint8_t byte : byte to write
 * @return int : 0 on success, non-zero otherwise
 */
int (kbc_write_arg)(uint8_t byte) {
    return kbc_write(KBC_IN_ARGS, byte);
}

/**
 * @brief Helper function to write to the mouse
 * @param uint8_t byte : byte to write to the mouse
 * @return int : 0 on success
 */
static int kbc_mouse_write_helper(uint8_t byte) {
    #define helper_return(retv) {\
        if (kbc_write_cmd(KBD_ENABLE))\
            DEBUG_ERRORV("FAILED TO REENABLE KEYBOARD ON EXIT\n");\
        return (retv);\
    }

    // disable keyboard to prevent interference
    if (kbc_write_cmd(KBD_DISABLE)) {
        DEBUG_ERRORV("Failed to disable keyboard\n");
        helper_return(1);
    }

    uint8_t b;

    // flush any existing output
    while (true) {
        util_sys_inb(KBC_STAT_REG, &b);
        if (b & KBC_ST_OBF) {
            DEBUG_INFOV("Flushing output register...\n");
            util_sys_inb(KBC_OUT_BUF, &b);
        }
        else
            break;
    }

    // tell the controller you're sending to the mouse
    if (kbc_write(KBC_IN_CMD, KBC_MOUSE_WRITE)) {
        DEBUG_ERRORV("Failed to send KBC_MOUSE_WRITE\n");
        helper_return(1);
    }

    // send the byte
    if (kbc_write(KBC_IN_ARGS, byte)) {
        DEBUG_ERRORV("Failed to pass argument\n");
        helper_return(1);
    }

    // check acknowledgement byte
    if (util_sys_inb(KBC_OUT_BUF, &b))
        helper_return(1);
    
    tickdelay(micros_to_ticks(KBC_DELAY_MICROSECONDS));

    if (b == MOUSE_ACK)
        helper_return(0);
    DEBUG_ERRORV("Byte received after command is not ACK (ACK = 0x%02x, received = 0x%02x)\n", MOUSE_ACK, b);
    helper_return(1);

    #undef helper_return
}

/**
 * @brief Writes a byte to the mouse through the KBC
 * @param uint8_t byte : byte to write to the mouse
 * @return int : 0 on success, non-zero otherwise
 */
int (kbc_mouse_write)(uint8_t byte) {
    switch (byte) {
        case MOUSE_ENABLE_DATA_REPORTING:
        case MOUSE_DISABLE_DATA_REPORTING:
            if (kbc_mouse_write_helper(byte)) {
                DEBUG_ERRORV("Failed to %s mouse data reporting\n", byte == MOUSE_ENABLE_DATA_REPORTING ? "enable" : "disable");
                return 1;
            }
            mouse_enabled = byte == MOUSE_ENABLE_DATA_REPORTING;
            break;
        default:
            // disable mouse data to avoid interference
            if (mouse_enabled && kbc_mouse_write_helper(MOUSE_DISABLE_DATA_REPORTING)) {
                DEBUG_ERRORV("Failed to disable mouse before sending byte\n");
                return 1;
            }

            // send byte
            if (kbc_mouse_write_helper(byte)) {
                DEBUG_ERRORV("Failed to send byte after disabling mouse\n");
                if (mouse_enabled && kbc_mouse_write_helper(MOUSE_ENABLE_DATA_REPORTING))
                    DEBUG_ERRORV("Failed to reenable mouse after failing to send byte\n");
                return 1;
            }

            // reenable mouse data
            if (mouse_enabled && kbc_mouse_write_helper(MOUSE_ENABLE_DATA_REPORTING)) {
                DEBUG_ERRORV("Failed to reenable mouse after sending byte\n");
                return 1;
            }
    }
    return 0;
}
