/**
 * @file scancodes.c
 * @brief Turn a scancode into the respective character
 * @author T17_G1
 * @date 02/06/2024
 */

#include "scancodes.h"

/**
 * @brief Turn a scancode into the respective character
 * @param keystroke_code_t code : scancode
 * @return char : the respective character
 */
char (keycode_to_char)(keystroke_code_t code) {
    switch (code) {
            case KEY_1: return '1';
            case KEY_2: return '2';
            case KEY_3: return '3';
            case KEY_4: return '4';
            case KEY_5: return '5';
            case KEY_6: return '6';
            case KEY_7: return '7';
            case KEY_8: return '8';
            case KEY_9: return '9';
            case KEY_0: return '0';
            case KEY_Q: return 'q';
            case KEY_W: return 'w';
            case KEY_E: return 'e';
            case KEY_R: return 'r';
            case KEY_T: return 't';
            case KEY_Y: return 'y';
            case KEY_U: return 'u';
            case KEY_I: return 'i';
            case KEY_O: return 'o';
            case KEY_P: return 'p';
            case KEY_A: return 'a';
            case KEY_S: return 's';
            case KEY_D: return 'd';
            case KEY_F: return 'f';
            case KEY_G: return 'g';
            case KEY_H: return 'h';
            case KEY_J: return 'j';
            case KEY_K: return 'k';
            case KEY_L: return 'l';
            case KEY_Z: return 'z';
            case KEY_X: return 'x';
            case KEY_C: return 'c';
            case KEY_V: return 'v';
            case KEY_B: return 'b';
            case KEY_N: return 'n';
            case KEY_M: return 'm';
            case KEY_SPACE: return ' ';
            case KEY_ENTER: return '\n';
            case KEY_BACKSPACE: return '\b';
            case KEY_OEM_PERIOD: return '.';
            case KEY_OEM_COMMA: return ',';

            default: return '\0';
        }
}
