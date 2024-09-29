/**
 * @file scancodes.h
 * @brief Definition of keyboard scancodes to later translated them to characters
 * @author T17_G1
 * @date 26/05/2024
 * @note Pedro Gorobey: I wanted to include this in keyboard.h, but I wanted to make a forward declaration so that whoever reads the file isn't met with a list of scancodes. However, "ISO C forbids forward references to 'enum' types", so I made this file.
 * @note Layout source: https://kbdlayout.info/kbdusx/scancodes
 * @note The meaning of codes with OEM on them is very likely to change between layouts/languages.
 */

#ifndef LCOM_PROJ_SCANCODES_H
#define LCOM_PROJ_SCANCODES_H

/*
 * @brief Enum with a lot of scancodes
Layout source: https://kbdlayout.info/kbdusx/scancodes
The meaning of codes with OEM on them is very likely to change between layouts/languages.
*/
typedef enum keystroke_code {
    KEY_ESC = 0x01,

    KEY_1 = 0x02,
    KEY_2 = 0x03,
    KEY_3 = 0x04,
    KEY_4 = 0x05,
    KEY_5 = 0x06,
    KEY_6 = 0x07,
    KEY_7 = 0x08,
    KEY_8 = 0x09,
    KEY_9 = 0x0A,
    KEY_0 = 0x0B,

    KEY_OEM_MINUS = 0x0C,
    KEY_OEM_PLUS = 0x0D,
    
    KEY_BACKSPACE = 0x0E,
    KEY_TAB = 0x0F,

    KEY_Q = 0x10,
    KEY_W = 0x11,
    KEY_E = 0x12,
    KEY_R = 0x13,
    KEY_T = 0x14,
    KEY_Y = 0x15,
    KEY_U = 0x16,
    KEY_I = 0x17,
    KEY_O = 0x18,
    KEY_P = 0x19,

    KEY_OEM_4 = 0x1A,
    KEY_OEM_6 = 0x1B,
    KEY_ENTER = 0x1C,
    KEY_LCTRL = 0x1D,

    KEY_A = 0x1E,
    KEY_S = 0x1F,
    KEY_D = 0x20,
    KEY_F = 0x21,
    KEY_G = 0x22,
    KEY_H = 0x23,
    KEY_J = 0x24,
    KEY_K = 0x25,
    KEY_L = 0x26,

    KEY_OEM_1 = 0x27,
    KEY_OEM_7 = 0x28,
    KEY_OEM_3 = 0x29,
    KEY_LSHIFT = 0x2A,
    KEY_OEM_5 = 0x2B,

    KEY_Z = 0x2C,
    KEY_X = 0x2D,
    KEY_C = 0x2E,
    KEY_V = 0x2F,
    KEY_B = 0x30,
    KEY_N = 0x31,
    KEY_M = 0x32,

    KEY_OEM_COMMA = 0x33,
    KEY_OEM_PERIOD = 0x34,
    KEY_OEM_2 = 0x35,
    KEY_RSHIFT = 0x36,
    KEY_MULTIPLY = 0x37,
    KEY_LALT = 0x38,

    KEY_SPACE = 0x39,

    KEY_CAPSLOCK = 0x3A,

    KEY_F1 = 0x3B,
    KEY_F2 = 0x3C,
    KEY_F3 = 0x3D,
    KEY_F4 = 0x3E,
    KEY_F5 = 0x3F,
    KEY_F6 = 0x40,
    KEY_F7 = 0x41,
    KEY_F8 = 0x42,
    KEY_F9 = 0x43,
    KEY_F10 = 0x44,

    KEY_NUMLOCK = 0x45,
    KEY_SCROLL = 0x46,

    KEY_NUMPAD_HOME = 0x47,
    KEY_NUMPAD_UP = 0x48,
    KEY_NUMPAD_PRIOR = 0x49,
    KEY_NUMPAD_SUBTRACT = 0x4A,
    KEY_NUMPAD_LEFT = 0x4B,
    KEY_NUMPAD_MIDDLE = 0x4C,
    KEY_NUMPAD_RIGHT = 0x4D,
    KEY_NUMPAD_ADD = 0x4E,
    KEY_NUMPAD_END = 0x4F,
    KEY_NUMPAD_DOWN = 0x50,
    KEY_NUMPAD_NEXT = 0x51,
    KEY_INSERT = 0x52,
    KEY_DELETE = 0x53,
    KEY_NUMPAD_ENTER = 0xE01C,

    KEY_SNAPSHOT = 0x54,

    KEY_OEM_10 = 0x56,

    KEY_F11 = 0x57,
    KEY_F12 = 0x58,

    KEY_RALT = 0xE038,
    KEY_RWIN = 0xE05C,
    KEY_APPS = 0xE05D,
    KEY_RCTRL = 0xE01D,

    KEY_ARROW_UP = 0xE048,
    KEY_ARROW_DOWN = 0xE050,
    KEY_ARROW_LEFT = 0xE04B,
    KEY_ARROW_RIGHT = 0xE04D
} keystroke_code_t;

/**
 * @return The corresponding character if applicable, null-terminator ('\0') otherwise.
 */
char (keycode_to_char)(keystroke_code_t code);

#endif /* LCOM_PROJ_SCANCODES_H */
