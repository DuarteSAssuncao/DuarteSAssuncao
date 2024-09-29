/**
 * @file messages.c
 * @brief Transform keyboard data into a character
 * @author T17_G1
 * @date 29/05/2024
 */

#include "messages.h"
#include <interrupts/scancodes.h>
#include <interrupts/keyboard.h>
#include <ctype.h>

char char_shifted(char c) {
    if (c >= 'a' && c <= 'z')
        return toupper((int) c);

    // these depend a lot on the layout, so this code is very subject to change
    switch (c) {
        case ',': return ';';
        case '.': return ':';
        case '-': return '_';
        case '~': return '^';
        case '+': return '*';
        case '<': return '>';
        case '1': return '!';
        case '2': return '\"';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '&';
        case '7': return '/';
        case '8': return '(';
        case '9': return ')';
        case '0': return '=';
        case '\'': return '?';
        case '\\': return '|';
        default: return c;
    }
}

/**
 * @brief Convert keyboard data into a char, either directly, shifted or transformed
 * @example data.code == KEY_ESC -> '\0'
 * @example data.code == KEY_R && data.modifiers == 0 -> 'r'
 * @example data.code == KEY_A && data.modifiers == MOD_SHIFT -> 'A'
 * @example data.code == KEY_K && data.modifiers == MOD_CAPSLOCK -> 'K'
 * @example data.code == KEY_O && data.modifiers == MOD_CTRL -> '\0'
 * @example data.code == KEY_O && data.modifiers == MOD_SHIFT | MOD_CAPSLOCK -> 'o'
 * @example data.code == KEY_N && data.modifiers == MOD_CTRL | MOD_SHIFT -> '\0'
 * @example data.code == KEY_1 && data.modifiers == MOD_SHIFT | MOD_CAPSLOCK -> '!'
 * @param keyboard_data_t data : data from the keyboard
 * @return char : the corresponding character
 */
char keyboard_data_to_char(keyboard_data_t data) {
    if (data.release) return '\0';
    char res = keycode_to_char(data.code);
    if (res == '\0') return res;

    switch (data.modifiers) {
        case MOD_SHIFT:
            return char_shifted(res);
        case MOD_CAPSLOCK:
            return toupper((int) res);
        case MOD_SHIFT | MOD_CAPSLOCK:
            if (res >= 'a' && res <= 'z')
                return res;
            return char_shifted(res);
        default:
            return res;
    }
}
