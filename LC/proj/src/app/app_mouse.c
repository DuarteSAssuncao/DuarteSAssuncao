/**
 * @file app_mouse.c
 * @brief Definition of "higher" mouse functions used in the project
 * @author T17_G1
 * @date 27/05/2024
 */

#include "app_mouse.h"
#include "shared.h"
#include <lcom/lab4.h>
#include <interrupts/mouse.h>
#include "app_timer.h"
#include <auxiliary/extra_utils.h>
#include <graphics/graphics.h>
#include "ipc/ipc_codes.h"
#include <sys/socket.h>
#include <interrupts/timer.h>

#define DEBUG
//#define DEBUG2
#include <auxiliary/debug.h>

//! Packet with the bytes sent from the mouse
static struct packet packet;

/**
 * @brief This functions handles a penguin
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t (penguin_mouse_handler)() {
    reset_timer();
    if (mouse_packet_ready()) {
        mouse_get_packet(&packet);
        if (!packet.x_ov) penguin_x += packet.delta_x;
        if (!packet.y_ov) penguin_y -= packet.delta_y;
    }
    return INT_CONTINUE;
}

#define MOUSE_LEFT BIT(0)       /*!< Left button of the mouse was clicked */
#define MOUSE_RIGHT BIT(1)      /*!< Right button of the mouse was clicked */
#define MOUSE_MIDDLE BIT(2)     /*!< Middle button of the mouse was clicked */

//! ID to remove observer from timer
static int double_click_timer_id;

//! Data from the mouse, current and old
static mouse_data_t mouse_data, old_mouse_data;
#define prev_buttons old_mouse_data.buttons
#define mouse_buttons mouse_data.buttons

/**
 * @brief Mouse handler with windows on the screen
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t windows_mouse_handler() {
    if (!mouse_packet_ready()) return INT_CONTINUE;
    mouse_get_packet(&packet);
    packet.delta_y = -packet.delta_y;

    int16_t dx, dy;
    if (mouse_x < -packet.delta_x)
        dx = -mouse_x;
    else if (mouse_x + packet.delta_x >= vg_get_xres())
        dx = vg_get_xres() - mouse_x - 1;
    else
        dx = packet.delta_x;
    
    if (mouse_y < -packet.delta_y)
        dy = -mouse_y;
    else if (mouse_y + packet.delta_y >= vg_get_yres())
        dy = vg_get_yres() - mouse_y - 1;
    else
        dy = packet.delta_y;
    
    prev_buttons = mouse_buttons;
    if (packet.lb) mouse_buttons |= MOUSE_LEFT;
    else mouse_buttons &= ~MOUSE_LEFT;
    
    if (packet.rb) mouse_buttons |= MOUSE_RIGHT;
    else mouse_buttons &= ~MOUSE_RIGHT;
    
    if (packet.mb) mouse_buttons |= MOUSE_MIDDLE;
    else mouse_buttons &= ~MOUSE_MIDDLE;

    if (prev_buttons == MOUSE_LEFT && mouse_buttons != MOUSE_LEFT && moving_window != NULL) {
        // draw_image(&background, moving_window->buffer, moving_window->width, moving_window->height, moving_window->x, moving_window->y);
        
        if (mouse_x > moving_window->x + moving_window->width - 30 && mouse_y < moving_window->y + 30) {
            // If the mouse was on the closing button, then close the window:
            for(uint8_t i = 0; i < n_fe; i++) {
                if((file_explorers + i * sizeof(*file_explorers))->window == moving_window) {
                    // If the window belonged to a FE window, then close the FE window too:
                    if(close_fe_window(file_explorers + i * sizeof(*file_explorers)) != 0) return INT_EXIT;
                    break;
                }
            }
            if(close_window(moving_window) != 0) return INT_EXIT;
        }
        
        moving_window = NULL;
    }
    else if (prev_buttons == 0 && mouse_buttons == MOUSE_LEFT) { // changed from no click to only left click
        for (size_t i = 0; i < n_windows; ++i) {
            if (windows[i].x < mouse_x && mouse_x < windows[i].x + windows[i].width && windows[i].y < mouse_y && mouse_y < windows[i].y + windows[i].height) {
                window_t tmp = windows[i];

                // put the window on top
                memmove(windows + 1, windows, i * sizeof(*windows));
                windows[0] = tmp;

                if(mouse_y < tmp.y + 30) moving_window = windows;
                break;
            }
        }
    }

    if (moving_window != NULL) {
        // moving_window->updated = true;
        moving_window->x += dx;
        moving_window->y += dy;
/*         if(moving_window->y < 60) {
            dy = 0;
            moving_window->y = 60;
            // This was to prevent the window to overlap the top bar, but doesn't work well
        } */
    }

    mouse_x += dx;
    mouse_y += dy;

    update_screen = true;

    return INT_CONTINUE;
}

//! Mouse states
static void mouse_normal(), mouse_dragging(), mouse_moving_window(), mouse_maybe_left_click(), mouse_maybe_left_double_click();
static void (*mouse_state)() = mouse_normal;

/**
 * @brief Changes the mouse state to normal
 * @return void
 */
static void mouse_set_normal_state() {mouse_state = mouse_normal;}

//! Used to send mouse events to the respective window
static int send_mouse_data(mouse_data_t *maus_data, _win_t *win);

/**
 * @brief Mouse handler of the IPC
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */
int_ret_t ipc_mouse_handler() {
    if (!mouse_packet_ready()) return INT_CONTINUE;
    mouse_get_packet(&packet);
    packet.delta_y = -packet.delta_y;

    // calculate actual mouse movement
    if (mouse_data.x < -packet.delta_x)
        mouse_data.dx = -mouse_data.x;
    else if (mouse_data.x + packet.delta_x >= vg_get_xres())
        mouse_data.dx = vg_get_xres() - mouse_data.x - 1;
    else
        mouse_data.dx = packet.delta_x;
    
    if (mouse_data.y < -packet.delta_y)
        mouse_data.dy = -mouse_data.y;
    else if (mouse_data.y + packet.delta_y >= vg_get_yres())
        mouse_data.dy = vg_get_yres() - mouse_data.y - 1;
    else
        mouse_data.dy = packet.delta_y;


    old_mouse_data = mouse_data;
    // update button masks
    if (packet.lb) mouse_buttons |= MOUSE_LEFT;
    else mouse_buttons &= ~MOUSE_LEFT;

    if (packet.rb) mouse_buttons |= MOUSE_RIGHT;
    else mouse_buttons &= ~MOUSE_RIGHT;

    if (packet.mb) mouse_buttons |= MOUSE_MIDDLE;
    else mouse_buttons &= ~MOUSE_MIDDLE;

    mouse_data.x += mouse_data.dx;
    mouse_data.y += mouse_data.dy;

    mouse_state();

    update_screen = true;
    return INT_CONTINUE;
}

/**
 * @brief Normal state of the mouse
 * @return void
 */
static void mouse_normal() {
    mouse_data.type = MOUSE_UNKNOWN;
    for (size_t i = 0; i < n_windows; ++i) {
        win_attr_t attr = wins[i].attr;

        // check if mouse in window
        if (attr.x <= old_mouse_data.x && old_mouse_data.x < attr.x + attr.width && attr.y - window_bar_height() <= old_mouse_data.y && old_mouse_data.y < attr.y + attr.height) {

            if (mouse_buttons) { // any click -> select/focus window
                if (i != n_windows - 1) { // if not home/desktop
                    win_set_top(i);
                    i = 0;
                }
                selected_win = wins + i;
            }

            if (old_mouse_data.y >= attr.y) { // mouse was on client's window
                switch (mouse_buttons) {
                    case MOUSE_LEFT:
                        if (mouse_data.dx || mouse_data.dy) { // click + move -> drag
                            mouse_data.type = MOUSE_LEFT_DRAG_START;
                            mouse_state = mouse_dragging;
                        } else { // no movement -> maybe it's a click
                            mouse_state = mouse_maybe_left_click;
                        }
                        break;
                }
                send_mouse_data(&mouse_data, selected_win);
            }

            else { // mouse on window bar
                if(i == n_windows - 1) break;
                if (old_mouse_data.x >= attr.x + attr.width - window_bar_height()) { // X (close) button
                    if (prev_buttons == MOUSE_LEFT && mouse_buttons == 0) {
                        DEBUG_PRINTF("Pressed X to close!\n");
                        remove_client(i);
                        selected_win = NULL;
                    }
                } else { // window bar -> move window
                    if (mouse_buttons == MOUSE_LEFT) {
                        attr.x += mouse_data.dx;
                        attr.y += mouse_data.dy;
                        mouse_state = mouse_moving_window;
                        break;
                    }
                }
            }
            break;
        }
    }
}

/**
 * @brief The user is dragging the mouse
 * @return void
 */
static void mouse_dragging() {
    if (mouse_buttons != MOUSE_LEFT) {
        mouse_data.type = MOUSE_LEFT_DRAG_STOP;
        send_mouse_data(&mouse_data, selected_win);
        mouse_state = mouse_normal;
        return;
    }
    mouse_data.type = MOUSE_LEFT_DRAG;
    send_mouse_data(&mouse_data, selected_win);
}

/**
 * @brief The user is using the mouse to move a window
 * @return void
 */
static void mouse_moving_window() {
    if (mouse_buttons != MOUSE_LEFT) {
        mouse_state = mouse_normal;
        return;
    }
    selected_win->attr.x += mouse_data.dx;
    selected_win->attr.y += mouse_data.dy;
}

/** 
 * @brief Left button and no movement - if released without moving, it's a left click
 * @return void
 */
static void mouse_maybe_left_click() {
    switch (mouse_buttons) {
        case 0: // button release
            if (mouse_data.dx || mouse_data.dy) { // mouse movement -> not a click
                mouse_state = mouse_normal;
                break;
            }
            mouse_data.type = MOUSE_LEFT_CLICK;
            send_mouse_data(&mouse_data, selected_win);
            timer_add_observer(timer_millis_to_ticks(500), &double_click_timer_id, mouse_set_normal_state, false);
            mouse_state = mouse_maybe_left_double_click;
            break;
        case MOUSE_LEFT: // considering that the left button was already pressed, we can assume there was movement
            mouse_data.type = MOUSE_LEFT_DRAG_START;
            send_mouse_data(&mouse_data, selected_win);
            mouse_state = mouse_dragging;
            break;
        default:
            mouse_state = mouse_normal;
    }
}

/** 
 * @brief Checks if the user just performed a left double click
 * @return void
 */
static void mouse_maybe_left_double_click() {
    if (mouse_buttons == MOUSE_LEFT && !mouse_data.dx && !mouse_data.dy) {
        mouse_data.type = MOUSE_LEFT_DOUBLE_CLICK;
        send_mouse_data(&mouse_data, selected_win);
    }
    timer_remove_observer(&double_click_timer_id);
    mouse_state = mouse_normal;
}

/**
 * @brief Sends mouse data to the given window
 * @param mouse_data_t *maus_data : information about the mouse
 * @param _win_t *win : which window to send the information to
 * @return int
 */
static int send_mouse_data(mouse_data_t *maus_data, _win_t *win) {
    if (win == NULL) {
        DEBUG_PRINTF2("%s: win == NULL\n", __func__);
        return 0;
    }
    rakoon_msg_t msg = {.win_id = win->attr.win_id, .m_type = RKE_MOUSE};

    memcpy(msg.data, maus_data, sizeof(*maus_data));
    ((mouse_data_t*)msg.data)->x = maus_data->x - win->attr.x;
    ((mouse_data_t*)msg.data)->y = maus_data->y - win->attr.y;

    msgbuf[msgbufsize++] = msg;
    return 0;
}

/**
 * @brief Get the x-position of the mouse
 * @return int16_t* : pointer to the x-position of the mouse
 */
int16_t* mouse_x_() {
    return &mouse_data.x;
}

/**
 * @brief Get the y-position of the mouse
 * @return int16_t* : pointer to the y-position of the mouse
 */
int16_t* mouse_y_() {
    return &mouse_data.y;
}

