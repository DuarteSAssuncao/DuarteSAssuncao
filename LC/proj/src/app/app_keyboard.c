/**
 * @file app_keyboard.c
 * @brief Definition of "higher" functions used in the project related to the keyboard
 * @author T17_G1
 * @date 27/05/2024
 */

#include <lcom/lcf.h>
#include "app_keyboard.h"
#include "shared.h"
#include <interrupts/keyboard.h>
#include <ctype.h>
#include "app_timer.h"
#include "directories.h"
#include "ipc/server.h"
#include "ipc/ipc_codes.h"
#include <graphics/graphics.h>

#define DEBUG
#include <auxiliary/debug.h>

//! The current keystroke
static keystroke_t k;

//! Data from the keyboard
keyboard_data_t kb_data;

#define modifiers kb_data.modifiers

//! Hold Keys (CTRL, ALT, ALT GR, SHIFT, FN)
static uint64_t hold_keys = 0;

//! Buffer to hold the characters obtained from the keyboard
static char buf[1024];

//! Size of the buffer
static size_t bufsize = 0;

/**
 * @brief Handler of the keyboard in the project
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t (proj_keyboard_handler)() {
    if (!keyboard_ready()) return INT_CONTINUE;

    keystroke_get(&k);

    if (k.release) {
        switch (k.code) {
            case KEY_ESC:
                return INT_EXIT;
            case KEY_LSHIFT:
                hold_keys &= ~HOLD_LSHIFT;
                if (!(hold_keys & HOLD_RSHIFT)) modifiers &= ~MOD_SHIFT;
                break;
            case KEY_RSHIFT:
                hold_keys &= ~HOLD_RSHIFT;
                if (!(hold_keys & HOLD_LSHIFT)) modifiers &= ~MOD_SHIFT;
                break;
            case KEY_LCTRL:
                hold_keys &= ~HOLD_LCTRL;
                if (!(hold_keys & HOLD_RCTRL)) modifiers &= ~MOD_CTRL;
                break;
            case KEY_RCTRL:
                hold_keys &= ~HOLD_RCTRL;
                if (!(hold_keys & HOLD_LCTRL)) modifiers &= ~MOD_CTRL;
                break;
            case KEY_LALT:
                hold_keys &= ~HOLD_LALT;
                if (!(hold_keys & HOLD_RALT)) modifiers &= ~MOD_ALT;
                break;
            case KEY_RALT:
                hold_keys &= ~HOLD_RALT;
                if (!(hold_keys & HOLD_LALT)) modifiers &= ~MOD_ALT;
                break;
            case KEY_CAPSLOCK:
                hold_keys &= ~HOLD_CAPSLOCK;
                break;
            default:
                break;
        }
        return INT_CONTINUE;
    }

    char c = keycode_to_char(k.code);
    if (c != '\0' && !(modifiers & ~(MOD_SHIFT | MOD_CAPSLOCK))) {
        if (bufsize < sizeof(buf)-1) {
            if ((bool) (modifiers & MOD_SHIFT) != (bool) (modifiers & MOD_CAPSLOCK)) // either shift or capslock
                c = char_shifted(c);
            buf[bufsize] = c;
            ++bufsize;
            printf("%c", c);
        }
        return INT_CONTINUE;
    }

    dir_node_t *dir = NULL;
    bool refresh = false;
    switch (k.code) {
        case KEY_ENTER:
            if (bufsize == 0)
                break;
            printf("\n");
            buf[bufsize] = '\0';
            refresh = true;

            if (chdir(buf)
                || (dir = calloc(1, sizeof(*dir))) == NULL
                || getcwd(dir->fullpath, sizeof(dir->fullpath)) == NULL
            ) {
                free(dir);
                dir = NULL;
                printf("Failed to open %s: %s\n", buf, strerror(errno));
            }

            break;
        case KEY_BACKSPACE:
            if (bufsize > 0) {
                --bufsize;
                printf("\b \b");
            }
            break;
        case KEY_ARROW_LEFT:
            if (modifiers == MOD_ALT && curdir->previous != NULL) {
                curdir = curdir->previous;
                chdir(curdir->fullpath);
                refresh = true;
            }
            break;
        case KEY_ARROW_RIGHT:
            if (modifiers == MOD_ALT && curdir->next != NULL) {
                curdir = curdir->next;
                chdir(curdir->fullpath);
                refresh = true;
            }
            break;
        case KEY_LSHIFT:
            modifiers |= MOD_SHIFT;
            hold_keys |= HOLD_LSHIFT;
            break;
        case KEY_RSHIFT:
            modifiers |= MOD_SHIFT;
            hold_keys |= HOLD_RSHIFT;
            break;
        case KEY_LALT:
            modifiers |= MOD_ALT;
            hold_keys |= HOLD_LALT;
            break;
        case KEY_RALT:
            modifiers |= MOD_ALT;
            hold_keys |= HOLD_RALT;
            break;
        case KEY_LCTRL:
            modifiers |= MOD_CTRL;
            hold_keys |= HOLD_LCTRL;
            break;
        case KEY_RCTRL:
            modifiers |= MOD_CTRL;
            hold_keys |= HOLD_RCTRL;
            break;
        case KEY_CAPSLOCK:
            if (!(hold_keys & HOLD_CAPSLOCK)) {
                hold_keys |= HOLD_CAPSLOCK;
                modifiers ^= MOD_CAPSLOCK;
            }
            break;
        case KEY_F5:
            refresh = true;
            break;
        default:
            break;
    }

    if (refresh) {
        if (dir != NULL) {
            free_dir_node_and_descendants(curdir->next);
            dir->previous = curdir;
            curdir->next = dir;
            curdir = dir;
        }

        bufsize = 0;
        vector_dir_item_t temp_items;
        if (load_dir(".", &temp_items)) {
            printf("Failed to load %s: %s\n", curdir->fullpath, strerror(errno));
            free(dir);
            return INT_CONTINUE;
        }

        curdir_items = temp_items;
        if (getcwd(buf, sizeof(buf)) == NULL)
            memcpy(buf, "The void", sizeof("The void"));
        printf("%s\n%s\n", buf, curdir->fullpath);
        print_dir_items(&curdir_items);
        printf("Type directory: ");
    }
    return INT_CONTINUE;
}

/**
 * @brief This functions handles a penguin
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t (penguin_keyboard_handler)() {
    reset_timer();
    if (!keyboard_ready()) return INT_CONTINUE;

    keystroke_get(&k);

    if (!k.release) { // key press
        switch (k.code) {
            case KEY_M:
                interrupts_toggle(MOUSE); // disable/enable mouse by pressing M
                break;
            case KEY_W: case KEY_ARROW_UP:
                penguin_vy = -5;
                break;
            case KEY_S: case KEY_ARROW_DOWN:
                penguin_vy = 5;
                break;
            case KEY_A: case KEY_ARROW_LEFT:
                penguin_vx = -5;
                break;
            case KEY_D: case KEY_ARROW_RIGHT:
                penguin_vx = 5;
                break;
            default:
                break;
        }
    } else { // key release
        switch (k.code) {
            case KEY_ESC:
                return INT_EXIT; // terminate upon releasing ESC
            case KEY_W: case KEY_ARROW_UP:
                if (penguin_vy < 0) penguin_vy = 0;
                break;
            case KEY_S: case KEY_ARROW_DOWN:
                if (penguin_vy > 0) penguin_vy = 0;
                break;
            case KEY_A: case KEY_ARROW_LEFT:
                if (penguin_vx < 0) penguin_vx = 0;
                break;
            case KEY_D: case KEY_ARROW_RIGHT:
                if (penguin_vx > 0) penguin_vx = 0;
                break;
            default:
                break;
        }
    }
    return INT_CONTINUE;
}

/**
 * @brief Debug function for the keyboard (when it wasn't working)
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t (debug_keyboard_handler)() {
    reset_timer();
    if (!keyboard_ready()) return INT_CONTINUE;

    keystroke_get(&k);
    printf("%04x", k.code | (k.release ? BIT(7) : 0));
    char c = keycode_to_char(k.code);
    if (c != '\0')
        printf(" ('%c')", c);
    if (k.release)
        printf(" release");
    printf("\n");

    if (k.code == KEY_ESC && k.release) return INT_EXIT;
    return INT_CONTINUE;
}

/**
 * @brief Handles the keyboard with windows on the screen
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t windows_keyboard_handler() {
    if (!keyboard_ready()) return INT_CONTINUE;

    keystroke_get(&k);

    if (!k.release && k.code == KEY_N) {
        if (n_windows >= sizeof(windows) / sizeof(*windows)) return INT_CONTINUE;
        // Creates a new Window:
        memmove(windows + 1, windows, n_windows * sizeof(*windows));

        window_t *win = windows + (moving_window != NULL);

        if(new_window(
            win,
            rand() % vg_get_xres(),
            rand() % vg_get_yres(),
            300 + rand() % 150,
            200 + rand() % 100
        ) != 0 ) return INT_EXIT;

        ++n_windows;
        update_screen = true;
        // windows->updated = true;
    } else if (k.release && k.code == KEY_E) {
        if (n_windows >= sizeof(windows) / sizeof(*windows)) return INT_CONTINUE;
        if (n_fe >= sizeof(file_explorers) / sizeof(*file_explorers)) return INT_CONTINUE;

        memmove(windows + 1, windows, n_windows * sizeof(*windows));
        window_t *win = windows + (moving_window != NULL);
        if(new_window(win, 20, 80, 576, 576) != 0) return INT_EXIT;
        ++n_windows;
        
        file_explorer_window_t * new_fe_window = file_explorers + n_fe;
        *new_fe_window = (file_explorer_window_t) {
            .window = win,
            .dir = home,
            .elements = NULL,
            .n_elements = 0
        };
        if (load_dir(home->fullpath, &(new_fe_window->items)) != 0) return INT_EXIT;
        if (generate_fe_elements(new_fe_window) != 0) return INT_EXIT;
        char string[14] = "File Explorer";
        uint16_t x = (win->width - (8 * 13 - 2) * 2) / 2;
        uint16_t y = (30 - 11 * 2) / 2;
        draw_text(win, x, y, string, 13, 0x222222, 2);
        if (draw_fe_elements(new_fe_window)!= 0) return INT_EXIT;
        ++n_fe;

        update_screen = true;
    } else if (k.release && k.code == KEY_ESC) return INT_EXIT;

    return INT_CONTINUE;
}

static void send_keyboard_data(keyboard_data_t key, _win_t *win);

/**
 * @brief Send keyboard data
 * @param keyboard_data_t key : key pressed
 * @param _win_t *win : window from where to get the information
 * @return void
 */
static void send_keyboard_data(keyboard_data_t key, _win_t *win) {
    if (win == NULL) {
        DEBUG_PRINTF("%s: win == NULL\n", __func__);
        return;
    }
    DEBUG_PRINTF("Sending keyboard data!\n");
    rakoon_msg_t msg = {.m_type = RKE_KEYBOARD, .win_id = win->attr.win_id};
    memcpy(msg.data, &key, sizeof(key));
    msgbuf[msgbufsize++] = msg;
}

/**
 * @brief Keyboard handler of the IPC
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t ipc_keyboard_handler() {
    if (!keyboard_ready()) return INT_CONTINUE;
    keystroke_get(&k);
    if (k.release && k.code == KEY_ESC) return INT_EXIT;
    kb_data.code = k.code;
    kb_data.release = k.release;

    if (k.release) {
        switch (k.code) {
            case KEY_ESC:
                return INT_EXIT;
            case KEY_LSHIFT:
                hold_keys &= ~HOLD_LSHIFT;
                if (!(hold_keys & HOLD_RSHIFT)) modifiers &= ~MOD_SHIFT;
                break;
            case KEY_RSHIFT:
                hold_keys &= ~HOLD_RSHIFT;
                if (!(hold_keys & HOLD_LSHIFT)) modifiers &= ~MOD_SHIFT;
                break;
            case KEY_LCTRL:
                hold_keys &= ~HOLD_LCTRL;
                if (!(hold_keys & HOLD_RCTRL)) modifiers &= ~MOD_CTRL;
                break;
            case KEY_RCTRL:
                hold_keys &= ~HOLD_RCTRL;
                if (!(hold_keys & HOLD_LCTRL)) modifiers &= ~MOD_CTRL;
                break;
            case KEY_LALT:
                hold_keys &= ~HOLD_LALT;
                if (!(hold_keys & HOLD_RALT)) modifiers &= ~MOD_ALT;
                break;
            case KEY_RALT:
                hold_keys &= ~HOLD_RALT;
                if (!(hold_keys & HOLD_LALT)) modifiers &= ~MOD_ALT;
                break;
            case KEY_CAPSLOCK:
                hold_keys &= ~HOLD_CAPSLOCK;
                break;
            default:
                break;
        }
    } else {
        // key press
        switch (k.code) {
            case KEY_LSHIFT:
                modifiers |= MOD_SHIFT;
                hold_keys |= HOLD_LSHIFT;
                break;
            case KEY_RSHIFT:
                modifiers |= MOD_SHIFT;
                hold_keys |= HOLD_RSHIFT;
                break;
            case KEY_LALT:
                modifiers |= MOD_ALT;
                hold_keys |= HOLD_LALT;
                break;
            case KEY_RALT:
                modifiers |= MOD_ALT;
                hold_keys |= HOLD_RALT;
                break;
            case KEY_LCTRL:
                modifiers |= MOD_CTRL;
                hold_keys |= HOLD_LCTRL;
                break;
            case KEY_RCTRL:
                modifiers |= MOD_CTRL;
                hold_keys |= HOLD_RCTRL;
                break;
            case KEY_CAPSLOCK:
                if (!(hold_keys & HOLD_CAPSLOCK)) {
                    hold_keys |= HOLD_CAPSLOCK;
                    modifiers ^= MOD_CAPSLOCK;
                }
                break;
            default:
                break;
        }
    }
    send_keyboard_data(kb_data, selected_win);
    return INT_CONTINUE;
}
