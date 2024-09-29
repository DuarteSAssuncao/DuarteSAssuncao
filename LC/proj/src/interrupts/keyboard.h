/**
 * @file keyboard.h
 * @brief Declaration of functions and some macros related with the KBC
 * @author T17_G1
 * @date 26/05/2024
 */

#ifndef LCOM_PROJ_KEYBOARD_H
#define LCOM_PROJ_KEYBOARD_H

#include <lcom/lcf.h>
#include "scancodes.h"

#define BREAKCODE_BIT BIT(7)    /*!< @brief Mask for checking breakcodes (aka key release) */
#define SCANCODE_2_BYTES 0xE0   /*!< @brief If read byte is equal to this, the next byte is part of the same scancode */

/**
 * @brief A simple keystroke
 */
typedef struct {
    keystroke_code_t code;  /*!< Code returned by the KBC corresponding to the keystroke */
    bool release;           /*!< true if the key was released */
} keystroke_t;

/**
 * @return True if you are allowed to call kbc_get_keystroke(), false otherwise.
 */
bool (keyboard_ready)();

/**
 * @brief Gets the information about the current key press/release.
 * @param keystroke_t *keystroke : pointer to keystroke_t to hold the obtained values
 * @return 0 on success, non-zero if (!keyboard_ready() || keystroke == NULL)
 */
int (keystroke_get)(keystroke_t *keystroke);

#endif /* LCOM_PROJ_KEYBOARD_H */
