/**
 * @file app_timer.c
 * @brief Definition of "higher" Timer0 functions used in the project
 * @author T17_G1
 * @date 27/05/2024
 */

#include "app_timer.h"
#include "shared.h"
#include <graphics/graphics.h>
#include <graphics/icons.h>
#include "ipc/server.h"

#define DEBUG
#define DEBUG2
#include <auxiliary/debug.h>

#define FPS 60                              /*!< Frames per second */
#define interrupts_per_frame (60 / FPS)     /*!< Number of interruptions per frame */

//! Timer counter, interruptions counter, number of seconds
static uint32_t timer_cnt = 0, int_cnt = 0, seconds = 0;

/**
 * @brief Handles the interrupts of the Timer0 in the project
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t (timer_handler)() {
    if (++timer_cnt >= 60) {
        if (++seconds >= 10)
            return INT_EXIT; // terminate after 10 seconds of not doing anything
        timer_cnt = 0;
    }
    if (++int_cnt >= interrupts_per_frame) {
        penguin_x += penguin_vx;
        penguin_y += penguin_vy;
        vg_clrscr();
        vg_draw_xpm(&penguin_sprite, penguin_x, penguin_y);
        int_cnt = 0;
    }
    return INT_CONTINUE;
}

//! Current date
extern date_t date;

/**
 * @brief Handles the Timer with windows on the screen
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t timer_windows_handler() {
    if(update_clock) {
        char date_str[17];
        uint16_t x_res = vg_get_xres();
        uint8_t text_size = 2;
        uint16_t text_width = (8 * 16 - 2) * text_size; // 16 is the length of the date string
        uint16_t text_height = 8 * text_size;
        // each letter (at size=1) has a height of 11 pixels, but here I'm using 8, because the 3 bottom pixels are only used in very special cases, like characters 'j' or ','
        uint16_t x = (x_res - text_width) / 2;
        uint16_t y = (60 - text_height) / 2; // 60 is the top bar height
        draw_rect(&background, x, y, text_width, text_height, 0x555555); // clean previous time
        sprintf(date_str, "%02d/%02d/%d %02d:%02d", date.day, date.month, 2000 + date.year, date.hour, date.min);
        int err = draw_text(&background, x, y, date_str, strlen(date_str), 0xFFFFFF, text_size);
        if(err != 0) return INT_EXIT;

        update_clock = false;
    }

    if (++int_cnt >= interrupts_per_frame && update_screen) {
        // Updates Screen:
        vg_fill(background.buffer);

        // bool update = true;
        for (size_t i = n_windows - 1; i != SIZE_T_MAX; --i) {
            // draw_window(windows + i);
            /* if (windows[i].updated) {
                update = true;
                windows[i].updated = false;
            } */
            if(draw_window(windows + i) != 0) return INT_EXIT;
        }
        vg_draw_transparent_image(mouse_sprite, mouse_sprite_info.width, mouse_sprite_info.height, mouse_x, mouse_y, 0x100000);
        vg_refresh();
        update_screen = false;
        int_cnt = 0;
    }
    return INT_CONTINUE;
}

/**
 * @brief Resets some timer variables
 * @return void
 */
void (reset_timer)() {
    timer_cnt = seconds = 0;
}

/**
 * @brief Timer handler of the IPC
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t ipc_timer_handler() {
    if (++int_cnt < interrupts_per_frame) return INT_CONTINUE;

    int retv = server_handle_requests();
    if (retv) {
        if (retv == 1) return INT_EXIT;
        DEBUG_PRINTF("server_handle_requests: %s\n", strerror(errno));
    }

    if (server_send_events())
        DEBUG_PRINTF("server_send_events: %s\n", strerror(errno));

    if (update_screen) {
        for (size_t i = n_windows - 1; i != SIZE_T_MAX; --i) {
            // TODO: make entire block of code more readable and modular
            _win_t *win = wins + i; win_attr_t *attr = &win->attr;

            if(i == n_windows -1) {
                //vg_draw_transparent_image(win->winbuf, attr->width, attr->height, attr->x, attr->y, 0xFF660000); // FIXME: the files background is still red because of the transparency.
                // TODO: maybe draw this in the background only, so the desktop isn't drawn every frame
                vg_draw_image(win->winbuf, attr->width, attr->height, attr->x, attr->y);
                continue;
            }

            const uint32_t outline_color = 0xFF777777, bar_color = 0xFF777777;

            // draw window outline
            vg_draw_rect(attr->x - 1, attr->y - window_bar_height() - 1, attr->width + 2, 1, outline_color);
            vg_draw_rect(attr->x - 1, attr->y + attr->height, attr->width + 2, 1, outline_color);
            vg_draw_rect(attr->x - 1, attr->y - window_bar_height() - 1, 1, attr->height + window_bar_height() + 2, outline_color);
            vg_draw_rect(attr->x + attr->width, attr->y - window_bar_height() - 1, 1, attr->height + window_bar_height() + 2, outline_color);

            // draw window bar
            vg_draw_rect(attr->x, attr->y - window_bar_height(), attr->width, window_bar_height(), bar_color);
            vg_draw_transparent_image(cross_sprite, cross_sprite_info.width, cross_sprite_info.height, attr->x + attr->width - cross_sprite_info.width - 3, attr->y - window_bar_height() + 3, 0x010000);

            // draw window contents
            vg_draw_image(win->winbuf, attr->width, attr->height, attr->x, attr->y);
        }

        if(update_clock) {
            DEBUG_PRINTF2("Update clock!\n");
            char date_str[30];
            uint16_t x_res = vg_get_xres();
            uint8_t text_size = 2;
            uint16_t text_width = (8 * 16 - 2) * text_size; // 16 is the length of the date string
            uint16_t text_height = 8 * text_size;
            // each letter (at size=1) has a height of 11 pixels, but here I'm using 8, because the 3 bottom pixels are only used in very special cases, like characters 'j' or ','
            uint16_t x = (x_res - text_width) / 2;
            uint16_t y = (top_bar.height - text_height) / 2; // 60 is the top bar height
            DEBUG_PRINTF2("Drawing date at (%d,%d), width = %d, height = %d\n", x, y, text_width, text_height);
            draw_rect(&top_bar, x, y, text_width, text_height, 0x555555); // clean previous time
            sprintf(date_str, "%02d/%02d/%d %02d:%02d", date.day, date.month, 2000 + date.year, date.hour, date.min);
            int err = draw_text(&top_bar, x, y, date_str, strlen(date_str), 0xFFFFFF, text_size);
            if(err != 0) return INT_EXIT;

            update_clock = false;
        }
        vg_draw_image(top_bar.buffer, top_bar.width, top_bar.height, 0, 0);
        vg_draw_transparent_image(mouse_sprite, mouse_sprite_info.width, mouse_sprite_info.height, mouse_x, mouse_y, 0x010000);
        vg_refresh();
        update_screen = false;
        int_cnt = 0;
    }

    return INT_CONTINUE;
}
