/**
 * @file example.c
 * @brief Just an example
 * @author T17_G1
 * @date 29/05/2024
 */

#include "api.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <auxiliary/ansi_colors.h>
#include <auxiliary/vector.h>
#include <graphics/letters.h>

#define DEBUG
//#define DEBUG2
#include <auxiliary/debug.h>

//! A dot
typedef struct dot {
    int16_t x,y;    /*!< Coordinates */
} dot_t;

//! Number of previous buttons
uint8_t prev_buttons = 0;

//! Whether the window is being dragged
bool dragging = false;

//! Box: x-position, y-position, width, height
int16_t box_x, box_y, box_width, box_height;

//! Vector of dots
vector(dot_t) dots;

//! Current window
win_t *win;

//! Current character
char current_char;

//! Sprites of the characters
sprite_t char_sprites[256];

/**
 * @brief Draw elements on the current window (global variable)
 * @return int : 0 on success
 */
int draw_elements() {
    win_paste_rect(win, 0, 0, win_width(win), win_height(win), (rgb_t) {.hex = 0x000044});
    for (size_t i = 0; i < dots.size; ++i)
        win_paste_rect(win, dots.at[i].x - 1, dots.at[i].y - 1, 3, 3, (rgb_t) {.hex = 0xffffffff});
    win_draw_sprite_scaled(win, char_sprites + current_char, 50, 30, 2);

    if (dragging) {
        win_draw_rect(win, box_x, box_y, box_width, box_height, (argb_t) {.hex = 0x772d9d92});
        win_draw_line(win, box_x, box_y, box_x + box_width, box_y + box_height, (argb_t) {.hex = 0xffffffff});
    }
    win_refresh(win);
    return 0;
}

/**
 * @brief Main function of example
 * @param int argc : number of elements passed to the function
 * @param char **argv : array of elements passed to the function
 * @return int : 0 on success
 */
int main(int argc, char **argv) {
    int n = argc == 1 ? 0 : atoi(argv[1]) - 1;
    for (int i = 0; i < n; ++i)
        if (fork() == 0) break;

    vector_init(&dots);

    if (load_char_sprites(char_sprites)) {
        perror("load_char_sprites");
        return 1;
    }

    for (int c = 0; c < 256; ++c)
        sprite_replace_color(char_sprites + c, (argb_t) {.hex = 0xff000000}, (argb_t) {.hex = 0xffffffff});

    win = win_create(NULL);
    if (win == NULL) {
        perror("win_create");
        return 1;
    }
    DEBUG_PRINTF("(%d,%d), width = %d, height = %d\n", win_x(win), win_y(win), win_width(win), win_height(win));

    if (draw_elements()) {
        perror("draw_elements");
        return 1;
    }

    rakoon_msg_t msg;
    bool end = false;
    while (!end) {
        DEBUG_PRINTF("Waiting for event...\n");
        int r = win_wait_event(win, &msg);
        if (r == -1) {
            perror("win_wait_event");
            break;
        }

        bool draw_window = true;
        switch (msg.m_type) {
            case RKE_MOUSE: {
                DEBUG_PRINTF("Mouse event!\n");
                mouse_data_t *info = (mouse_data_t*) msg.data;

                DEBUG_PRINTF("(%d, %d) + (%d,%d), buttons = ", info->x, info->y, info->dx, info->dy);
                for (int bit = 1 << 2; bit != 0; bit >>= 1)
                    putchar(info->buttons & bit ? '1' : '0');
                putchar('\n');

                switch (info->type) {
                    case MOUSE_LEFT_DRAG_START:
                        dragging = true;
                        box_x = info->x - info->dx;
                        box_y = info->y - info->dy;
                        DEBUG_PRINTF(ANSI_GREEN "Created box!\nBox Start = (%d,%d)\n" ANSI_RESET, box_x, box_y);
                        // fall-through
                    case MOUSE_LEFT_DRAG:
                        DEBUG_PRINTF(ANSI_CYAN "Drawing box!\n" ANSI_RESET);
                        box_width = info->x - box_x;
                        box_height = info->y - box_y;
                        break;
                    case MOUSE_LEFT_DRAG_STOP:
                        dragging = false;
                        DEBUG_PRINTF(ANSI_YELLOW "Deleted box!\n" ANSI_RESET);
                        box_width = box_height = 0;
                        break;
                    case MOUSE_LEFT_CLICK:
                        DEBUG_PRINTF("Single click!\n");
                        dot_t *new_dot = vector_extend(&dots);
                        *new_dot = (dot_t) {.x = info->x, .y = info->y};
                        break;
                    case MOUSE_LEFT_DOUBLE_CLICK:
                        DEBUG_PRINTF("Double click!\n");
                        for (size_t i = 0; i < dots.size; ++i) {
                            int16_t diff_x = info->x - dots.at[i].x;
                            int16_t diff_y = info->y - dots.at[i].y;
                            if (diff_x < 100 && diff_x > -100 && diff_y < 100 && diff_y > -100)
                                vector_remove(&dots, i--);
                        }
                        break;
                    default:
                        draw_window = false;
                        DEBUG_PRINTF("Unhandled mouse event type %d\n", info->type);
                }
                break;
            }
            case RKE_KEYBOARD: {
                keyboard_data_t *info = (keyboard_data_t*) msg.data;
                DEBUG_PRINTF("Keyboard data! Modifiers: 0x%02x Character: ", info->modifiers);
                char c = keyboard_data_to_char(*info);
                current_char = c;
                if (c != '\0') {
                    DEBUG_PRINTF("'%c'\n", c);
                }
                else {
                    c = keycode_to_char(info->code);
                    if (c != '\0')
                        DEBUG_PRINTF("'%c' (release)\n", c);
                    else
                        DEBUG_PRINTF("(not a character)\n");
                }
                break;
            }
            case RKE_SHUTDOWN:
                draw_window = false;
                end = true;
                break;
            default:
                draw_window = false;
                DEBUG_PRINTF("Unhandled event %d\n", msg.m_type);
        }

        if (draw_window)
            draw_elements();
    }

    DEBUG_PRINTF("Exitting...\n");
    win_close(win);
    vector_destruct(&dots);
    return 0;
}
