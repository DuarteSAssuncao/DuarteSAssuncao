/**
 * @file shared.h
 * @brief Declaration of functions and variables used throughout the project
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_PROJ_SHARED_H
#define LCOM_PROJ_SHARED_H

#include "directories.h"
#include <lab6/rtc.h>
#include "window.h"
#include <interrupts/interrupts.h>
#include <lcom/xpm.h>
#include <sys/mman.h>
#include "ipc/server.h"
#include "ipc/protocol.h"
#include "file_explorer.h"
#include <graphics/sprite.h>
#include <graphics/letters.h>

#define SHARED_FILE "/tmp/lcom_proj_shared.txt"
#define BUFFER_SIZE 1024

//! Home directory, current directory
extern dir_node_t *home, *curdir;

//! Top-left corner coordinates, width, height (maybe?)
extern int16_t penguin_x, penguin_y, penguin_vx, penguin_vy;

//! x-coordinate and y-coordinate of the mouse
extern int16_t mouse_x, mouse_y;

//! XPM of the penguin
extern xpm_image_t penguin_sprite;

//! Function array of interrupt handles
extern int_handler_t handlers[DEVICE_COUNT];

//! List of items in the current directory
extern vector_dir_item_t curdir_items;

//! Background image (also represents the "static" objects)
extern window_t background;

//! The top bar that shows the time and the power button
extern window_t top_bar;

/**
 * @brief Top bar of the desktop environment. Works as a static window
 * @return int : 0 on success
 */
int load_top_bar();

//! Currently selected window
extern window_t *selected_window;

//! Non-moving objects, including the wallpaper
extern window_t background;

//! Window being moved
extern window_t *moving_window;

//! Whether or not to update the screen
extern bool update_screen;

//! Whether to update the clock
extern bool update_clock;

//! Array of windows on the screen
extern window_t windows[64];

//! Number of available windows
extern size_t n_windows;

//! Current date
extern date_t date;

//! Windows of the file explorer
extern file_explorer_window_t file_explorers[5];

//! Number of file explorer windows
extern size_t n_fe;

//! Sprite of the mouse
extern uint8_t * mouse_sprite;

//! Information about the sprite of the mouse
extern xpm_image_t mouse_sprite_info;

//! Sprite of the close window icon
extern uint8_t * cross_sprite;

//! Information about the sprite of the close window icon
extern xpm_image_t cross_sprite_info;

/**
 * @brief Draws the Desktop Environment background in the background window
 * @details Draws a dark top bar, the minix logo as wallpaper and a power button element (that is added to the window)
 * @return int 0 if succeeded and non-zero otherwise
 */
int draw_background();

//! Array of windows
extern _win_t wins[MAX_CLIENTS];

//! Currently selected window
extern _win_t *selected_win;

#define window_bar_height() 30

/**
 * @bried Get the x-position of the mouse
 * @return int16_t* : pointer to x-position of the mouse
 */
int16_t* mouse_x_();

/**
 * @bried Get the x-position of the mouse
 * @return int16_t* : pointer to x-position of the mouse
 */
int16_t* mouse_y_();
#define mouse_x (*mouse_x_())
#define mouse_y (*mouse_y_())

#define MAX_MSGS 256

//! 
extern rakoon_msg_t msgbuf[MAX_MSGS]; // messages to send
                                      
//!                                  
extern size_t msgbufsize;

//!
extern rakoon_msg_t msgq[MAX_MSGS]; // received messages

//!
extern size_t msgqsize;

/**
 * @brief Draws the folders
 * @return int : 0 on success
 */
int draw_folders();

#endif /* LCOM_PROJ_SHARED_H */
