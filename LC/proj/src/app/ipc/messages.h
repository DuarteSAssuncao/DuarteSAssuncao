/**
 * @file messages.h
 * @brief Attributes and macros related with messages (most of the time)
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef LCOM_PROJ_RAKOON_MESSAGES_H
#define LCOM_PROJ_RAKOON_MESSAGES_H

#include <stdint.h>
#include <stdbool.h>
#include <lcom/utils.h>
#include <interrupts/scancodes.h>
#include <interrupts/keyboard.h>

/**
 * @brief Window attributes to be passed when creating a window
 */
typedef struct win_attr {
    uint16_t width,height;                  /*!< Width, height */
    int16_t x,y;                            /*!< Coordinates */
    uint8_t bytes_per_pixel, n_buffers;     /*!< Number of bytes per pixel, number of buffers */
    uint16_t win_id;                        /*!< unique window identifier (unmodifiable) */
    uint32_t frame_buffer_size;             /*!< size allocated for each frame buffer (may be bigger than needed) */
} win_attr_t;






/**
 * @brief Message structure used in both directions (Rakoon <-> Window).
 * @note Big data like frame buffers must be sent through another socket (or, if the gods have descended to us, through shared memory)
 */
typedef struct rakoon_msg {
    uint16_t win_id; // window whom the message is about
    uint8_t m_type; // message type (either a rakoon_req_t or a rakoon_ev_t value)
    uint8_t data[sizeof(win_attr_t)]; // buffer for additional data
} rakoon_msg_t;






//! Mouse event
typedef enum mouse_event_type {
    MOUSE_UNKNOWN,              /*!< ? */
    MOUSE_LEFT_CLICK,           /*!< Left click */
    MOUSE_LEFT_DOUBLE_CLICK,    /*!< Left double click */
    MOUSE_LEFT_DRAG_START,      /*!< The user started to drag the mouse with the left button pressed */
    MOUSE_LEFT_DRAG,            /*!< The user is dragging the mouse with the left button pressed */
    MOUSE_LEFT_DRAG_STOP,       /*!< The user stopped dragging the mouse with the left button pressed */
} mouse_event_type_t;

//! Data from the mouse
typedef struct mouse_data {
    int16_t x,y;                /*!< current mouse position relative to the top-left pixel of the window */
    int16_t dx,dy;              /*!< mouse movement of this event */
    uint8_t buttons;            /*!< mask with the pressed buttons (check MOUSE_LEFT, MOUSE_RIGHT and MOUSE_MIDDLE) */
    mouse_event_type_t type;    /*!< event type to save you from having to make an entire state machine */
} mouse_data_t;

#define MOUSE_LEFT BIT(0)   /*!< Left button/click */
#define MOUSE_RIGHT BIT(1)  /*!< Right button/click */
#define MOUSE_MIDDLE BIT(2) /*!< Middle button/click */






//! Keyboard event
typedef struct keyboard_data {
    keystroke_code_t code;  /*!< Scancode */
    bool release;           /*!< Whether the key was released */
    uint8_t modifiers;      /*!< Ley modifiers (e.g. if you hold Ctrl, MOD_CTRL will be set) */
} keyboard_data_t;

#define MOD_ALT             BIT(0)  /*!< ALT is being clicked */
#define MOD_CTRL            BIT(1)  /*!< CTRL is being clicked */
#define MOD_SHIFT           BIT(2)  /*!< SHIFT is being clicked */
#define MOD_CAPSLOCK        BIT(3)  /*!< CAPSLOCK is being clicked */

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
char keyboard_data_to_char(keyboard_data_t data);

/**
 * @brief Switches the given char with the SHIFT variant (on the same key, the character above it)
 * @param char c : the character to be "shifted"
 * @return char : the "shifted" character
 */
char (char_shifted)(char c);

#endif /* LCOM_PROJ_RAKOON_MESSAGES_H */
