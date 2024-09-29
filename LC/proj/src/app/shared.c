/**
 * @file shared.c
 * @brief Definition of functions and declaration of variables used throughout the project
 * @author T17_G1
 * @date 27/05/2024
 */

#include <lcom/pixmap.h>
#include <lcom/xpm.h>
#include "shared.h"

#include <graphics/icons.h>
#include <graphics/graphics.h>
#include <lab6/rtc.h>

//! Home directory, current directory
dir_node_t *home, *curdir;

//! Top-left corner coordinates, width, height (maybe?)
int16_t penguin_x, penguin_y, penguin_vx, penguin_vy;

//! x-coordinate and y-coordinate of the mouse
int16_t mouse_x, mouse_y;

//! XPM of the penguin
xpm_image_t penguin_sprite;

//! Function array of interrupt handles
int_handler_t handlers[DEVICE_COUNT];

//! List of items in the current directory
vector_dir_item_t curdir_items;

//! Background image (also represents the "static" objects)
window_t background;

//! Currently selected window
window_t *selected_window;

//! Window being moved
window_t *moving_window;

//! Whether or not to update the screen
bool update_screen;

//! Array of windows on the screen
window_t windows[64];

//! Number of available windows
size_t n_windows;

//! Current date
date_t date;

//! Windows of the file explorer
file_explorer_window_t file_explorers[5];

//! Number of open windows of the file explorer
size_t n_fe;

//! Mouse sprite
uint8_t * mouse_sprite;

//! Mouse sprite
xpm_image_t mouse_sprite_info;

//! Cross icon sprite
uint8_t * cross_sprite;

//! Cross icon sprite
xpm_image_t cross_sprite_info;

/**
 * @brief Draws the Desktop Environment background in the background window
 * @details Draws a dark top bar, the minix logo as wallpaper and a power button element (that is added to the window)
 * @return int 0 if succeeded and non-zero otherwise
 */
int draw_background(){
    uint8_t Bpp = vg_bytes_per_pixel();
    uint16_t x_res = vg_get_xres();
    draw_rect(&background, 0, 0, x_res, 60, 0x555555); // top bar
    draw_rect(&background, 0, 60, x_res, 804, 0x000000); // black wallpaper
    uint16_t x, y;

    xpm_image_t raccoon_i;
    uint8_t * raccoon = xpm_load(minix3_xpm, XPM_8_8_8_8, &raccoon_i);
    if(raccoon != NULL){
        x = (x_res - raccoon_i.width * 4) / 2;
        y = 70;
        
        // Four fors
        for(uint8_t i = 0; i < raccoon_i.width; i++) {
            for(uint8_t j = 0; j < raccoon_i.height; j++) {
                for(uint8_t ii = 0; ii < 4; ii++) {
                    for(uint8_t jj = 0; jj < 4; jj++) {
                        uint8_t * pixel = background.buffer + ((y + j * 4 + jj) * x_res + x + i * 4 + ii) * Bpp;
                        uint8_t * color = raccoon + (j * raccoon_i.width + i) * Bpp;
                        if(memcpy(pixel, color, Bpp) == NULL){
                            printf("Error drawing raccoon at pixel x=%d y=%d\n.", i, j);
                            return 1;
                        }
                    }
                }
            }
        }
    } else printf("Error: Unable to draw raccoon wallpaper.\n");

    xpm_image_t pbi;
    uint8_t * powerb_pm = xpm_load(power_button_icon, XPM_8_8_8_8, &pbi);
    if(powerb_pm != NULL){
        x = x_res - 10 - (pbi.width * 4) - 1;
        y = 10;

        // More four fors
        for(uint8_t i = 0; i < pbi.width; i++) {
            for(uint8_t j = 0; j < pbi.height; j++) {
                for(uint8_t ii = 0; ii < 4; ii++) {
                    for(uint8_t jj = 0; jj < 4; jj++) {
                        uint8_t * pixel = background.buffer + ((y + j * 4 + jj) * x_res + x + i * 4 + ii) * Bpp;
                        uint8_t * color = powerb_pm + (j * pbi.width + i) * Bpp;
                        if(memcpy(pixel, color, Bpp) == NULL){
                            printf("Error drawing power button at pixel x=%d y=%d\n.", i, j);
                            return 1;
                        }
                    }
                }
            }
        }
    } else printf("Error: Unable to draw power button.\n");

    return 0;
}

//! Array of windows
_win_t wins[MAX_CLIENTS];

//! Window with focus
_win_t *selected_win;

//!
rakoon_msg_t msgbuf[MAX_MSGS];

//! Size of the message buffer
size_t msgbufsize;

//!
rakoon_msg_t msgq[MAX_MSGS];

//! 
size_t msgqsize;

/**
 * @brief Draws the folders on the file explorer
 * @return int : 0 on success
 */
int draw_folders() {
    uint16_t w_x = 100; 
    uint16_t w_y = 140; 
    uint16_t w_width = vg_get_xres() - 200; 
    uint16_t w_height = 600; 
    uint32_t w_color = 0x777777; 

    draw_rect(&background, w_x, w_y-40, w_width, 40, 0x555555);
    //draw_rect(&background, w_x, w_y, w_width, 60, 0xFF0F0F);
    draw_rect(&background, w_x, w_y, w_width, w_height, w_color);

    xpm_image_t xpm_folder;
    uint8_t* folder = xpm_load(folder_icon, XPM_8_8_8_8, &xpm_folder);
    if (folder == NULL) {
        printf("Error: Fail load image.\n");
        return 1;
    }

    uint16_t img_width = xpm_folder.width * 4;
    uint16_t img_height = xpm_folder.height * 4;
    uint16_t space = (w_width - 3 * img_width) / 4;

    if (img_height > w_height || (3 * img_width + 4 * space) > w_width) {
        printf("Error: Images does not fit\n");
        return 1;
    }


    uint16_t start_x = w_x + space;


    for (int i = 0; i < 3; i++) {
        uint16_t current_x = start_x + i * (img_width + space);
        for (uint16_t j = 0; j < xpm_folder.height; j++) {
            for (uint16_t k = 0; k < xpm_folder.width; k++) {
                for (uint16_t z = 0; z < 4; z++) {
                    for (uint16_t y = 0; y < 4; y++) {
                        uint8_t *pixel = background.buffer + (((w_y+20) + j * 4 + y) * vg_get_xres() + current_x + k * 4 + z) * vg_bytes_per_pixel();
                        uint8_t *color = folder + (j * xpm_folder.width + k) * vg_bytes_per_pixel();
                        memcpy(pixel, color, vg_bytes_per_pixel());
                    }
                }
            }
        }
    }

    return 0;
}

//! Top bar of the desktop environment. Works as a static window
window_t top_bar;

/**
 * @brief Loads the bar on the top
 * @return int : 0 on success
 */
int load_top_bar() {
    uint16_t width = vg_get_xres(), height = 60, bpp = vg_bytes_per_pixel();
    top_bar = (window_t) {
        .width = width,
        .height = height,
        .buffer = calloc(1, width * height * bpp),
    };
    if (top_bar.buffer == NULL)
        return -1;
    draw_rect(&top_bar, 0, 0, width, height, 0xFF555555);
    xpm_image_t pbi;
    xpm_load(power_button_icon, XPM_8_8_8_8, &pbi);
    if (pbi.bytes == NULL)
        return -1;

    int16_t x = top_bar.width - 10 - (pbi.width * 4) - 1;
    int16_t y = 10;
    uint8_t Bpp = vg_bytes_per_pixel();

    // copied from old function draw_background
    for(uint8_t i = 0; i < pbi.width; i++) {
        for(uint8_t j = 0; j < pbi.height; j++) {
            for(uint8_t ii = 0; ii < 4; ii++) {
                for(uint8_t jj = 0; jj < 4; jj++) {
                    uint8_t * pixel = top_bar.buffer + ((y + j * 4 + jj) * top_bar.width + x + i * 4 + ii) * Bpp;
                    uint8_t * color = pbi.bytes + (j * pbi.width + i) * Bpp;
                    memcpy(pixel, color, Bpp);
                }
            }
        }
    }
    return 0;
}
