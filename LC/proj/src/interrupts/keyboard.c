/**
 * @file keyboard.c
 * @brief Definition of functions related to the keyboard
 * @author T17_G1
 * @date 26/05/2024
 */

#include <lcom/lcf.h>
#include <lcom/utils.h>
#include "keyboard.h"
#include "kbc_i8042.h"
#include <ctype.h>

/**
 * @brief Scancode obtained from the KBC
 */
static struct kbc_scancode {
    uint8_t size;       /*!< Number of bytes in scancode */
    uint8_t bytes[2];   /*!< Bytes in the scancode */
} scancode = {.size = 0, .bytes = {0}};

//! Pointer to the scancode bytes
static uint8_t *byte_ptr = scancode.bytes;

/**
 * @brief State of the scancode
 */
static enum {
    SCANCODE_EMPTY,     /*!< @brief After kbc_get_scancode() */
    SCANCODE_READY,     /*!< @brief The scancode can be read */
    SCANCODE_WAITING    /*!< @brief Waiting for next byte */
} scancode_state = SCANCODE_EMPTY;

/**
 * @brief Keyboard Interrupt Handler
 * @return void
 */
void (kbc_ih)() {
    uint8_t status;
    if (
        (util_sys_inb(KBC_STAT_REG, &status)) ||
        (status & KBC_ST_INVALID) ||
        (util_sys_inb(KBC_OUT_BUF, byte_ptr))
    ) { /* Something went wrong -> just reset the scancode */
        memset(&scancode, 0, sizeof(scancode));
        byte_ptr = scancode.bytes;
        scancode_state = SCANCODE_EMPTY;
        return;
    }
    ++scancode.size;

    switch (scancode_state) {
        case SCANCODE_READY: /* overwrote previous scancode */
            scancode.bytes[1] = 0;
            scancode.size = 1;
            // fall through
        case SCANCODE_EMPTY: /* got first byte */
            if (scancode.bytes[0] == SCANCODE_2_BYTES) {
                scancode_state = SCANCODE_WAITING;
                ++byte_ptr;
            } else {
                scancode_state = SCANCODE_READY;
                byte_ptr = scancode.bytes;
            }
            break;
        case SCANCODE_WAITING: /* got remaining byte */
            byte_ptr = scancode.bytes;
            scancode_state = SCANCODE_READY;
            break;
    }
}

/**
 * @brief Whether the scancode can be read
 * @return bool : true if the scancode is ready
 */
bool (keyboard_ready)() {
    return scancode_state == SCANCODE_READY;
}

/**
 * @brief Receive the keystroke from the current scancode
 * @param keystroke_t *k : pointer to keystroke to hold the obtained values
 * @return int : 0 on success
 */
int (keystroke_get)(keystroke_t *k) {
    if (!keyboard_ready() || k == NULL)
        return 1;
    
    k->release = scancode.bytes[scancode.size - 1] & BREAKCODE_BIT;

    if (scancode.size == 1) // 1-byte scancode
        k->code = scancode.bytes[0] & ~BREAKCODE_BIT;
    else // 2-byte scancode
        k->code = (scancode.bytes[0] << 8) | (scancode.bytes[1] & ~BREAKCODE_BIT);
    
    scancode = (struct kbc_scancode) {0, {0}};
    return 0;
}
