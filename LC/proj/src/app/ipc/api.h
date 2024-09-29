/**
 * @file api.c
 * @brief Declaration of functions related to windows (not the OS, thankfully)
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef LCOM_PROJ_RAKOON_API_H
#define LCOM_PROJ_RAKOON_API_H

#include "ipc_codes.h"
#include "messages.h"
#include <stdint.h>
#include <graphics/color.h>
#include <graphics/sprite.h>

//! A struct to relate a window to its process
typedef struct win {
    int server_fd;      /*!< Server */
    int midman_fd;      /*!< Middleman (not an actual attack) */
    win_attr_t attr;    /*!< Attributes (x-position, y-position, width, height, etc.) */
    uint8_t *buf;       /*!< Window buffer */
} win_t;

/**
 * @brief Creates a window with initial attributes
 * @param const win_attr_t *init_attr : initial attributes
 * @return win_t* : pointer to window created, NULL if there was an error
 */
win_t *win_create(const win_attr_t *init_attr);

/**
 * @brief Closes a window
 * @param win_t *win : window to close
 * @return void
 */
void win_close(win_t *win);

/**
 * @brief Waits for an event in a window, blocking the current thread
 * @param win_t *win : window to wait for an event on
 * @param rakoon_msg_t *msg : where to store the event
 * @return int : 0 on success
 */
int win_wait_event(win_t *win, rakoon_msg_t *msg);

/**
 * @brief Refresh the given window
 * @param win_t *win : window to refresh (redraw)
 * @return int : 0 on success
 */
int win_refresh(win_t *win);

/**
 * @brief Paste a rectangle on a window
 * @param win_t *win : window to paste the rectangle on
 * @param int16_t x : x-position of the leftmost pixel of the rectangle
 * @param int16_t y : y-position of the upmost pixel of the rectangle
 * @param int16_t width : width of the rectangle
 * @param int16_t height : height of the rectangle
 * @param rgb_t color : color of the rectangle
 * @return int : 0 on success
 */
int win_paste_rect(win_t *win, int16_t x, int16_t y, int16_t width, int16_t height, rgb_t color);

/**
 * @brief Fills the entire window with the specified color.
 * @return 0 on success, non-zero otherwise.
 */
#define win_fill_rgb(win,color) win_paste_rect(win,0,0,win_width(win),win_height(win),color)

/**
 * @brief Draw a rectangle on a window
 * @param win_t *win : window to draw the rectangle on
 * @param int16_t x : x-position of the leftmost pixel of the rectangle
 * @param int16_t y : y-position of the upmost pixel of the rectangle
 * @param int16_t width : width of the rectangle
 * @param int16_t height : height of the rectangle
 * @param argb_t color : color of the rectangle (with alpha channel)
 * @return int : 0 on success
 */
int win_draw_rect(win_t *win, int16_t x, int16_t y, int16_t width, int16_t height, argb_t color);

/**
 * @brief Paste a sprite on a window
 * @param win_t *win : window to paste the sprite on
 * @param const sprite_t *sprite : sprite to paste on the window
 * @param int16_t x : x-position of the leftmost pixel of the sprite
 * @param int16_t y : y-position of the upmost pixel of the sprite
 * @return int : 0 on success
 */
int win_paste_sprite(win_t *win, const sprite_t *sprite, int16_t x, int16_t y);

/**
 * @brief Draw a sprite on a window
 * @param win_t *win : window to draw the sprite on
 * @param const sprite_t *sprite : sprite to draw on the window
 * @param int16_t x : x-position of the leftmost pixel of the sprite
 * @param int16_t y : y-position of the upmost pixel of the sprite
 * @return int : 0 on success
 */
int win_draw_sprite(win_t *win, const sprite_t *sprite, int16_t x, int16_t y);

/**
 * @brief Draw a sprite on a window with a scale
 * @param win_t *win : window to draw the sprite on
 * @param const sprite_t *sprite : sprite to draw on the window
 * @param int16_t x : x-position of the leftmost pixel of the sprite
 * @param int16_t y : y-position of the upmost pixel of the sprite
 * @param uint16_t scale : scale to draw the sprite (e.g., 2 -> four times bigger)
 * @return int : 0 on success
 */
int win_draw_sprite_scaled(win_t *win, const sprite_t *sprite, int16_t x, int16_t y, uint16_t scale);

/**
 * @brief Draws a line with the specified color
 * @param wint_t *win : window to draw the line on
 * @param int16_t x1 : x-position of the start of the line
 * @param int16_t y1 : y-position of the start of the line
 * @param int16_t x2 : x-position of the end of the line
 * @param int16_t y2 : y-position of the end of the line
 * @param argb_t color : color of the line with alpha channel
 * @return int : 0 on success, non-zero otherwise.
 */
int win_draw_line(win_t *win, int16_t x1, int16_t y1, int16_t x2, int16_t y2, argb_t color);

/**
 * @brief Draw a pixel on the window
 * @param win_t *win : window to draw the pixel on
 * @param int16_t x : x-position of the pixel
 * @param int16_t y : y-position of the pixel
 * @param argb_t color : color of the pixel
 * @return int : 0 on success
 */
int win_draw_pixel(win_t *win, int16_t x, int16_t y, argb_t color);

/**
 * @brief Draws a text on the window
 * @param win_t *win : window to draw the text on
 * @param const char *text : C-string to draw
 * @param const sprite_t char_sprites[256] : an array of monospaced sprites for each char value
 * @param int16_t x : X coordinate of the top-left pixel of the text on the window
 * @param int16_t y : Y coordinate of the top-left pixel of the text on the window
 * @param uint16_t max_width : Maximum width that the text can take
 * @param uint16_t scale : Scale of the text (1 for original, 2 for double width and height, and so on)
 * @param void (*if_too_long)(const char *, char *, size_t) : If not NULL, will be called whenever the text is too long
 *                    First parameter (const char*) : the original text
 *                    Second parameter (char*) : pointer to a copy of the N first characters that fit (are modifiable)
 *                    Third parameter (size_t) : N
 * @param bool center : If true, the string will be centered. Otherwise, it will be aligned to the left
 * @return int : 0 on success, non-zero otherwise
 */
int win_draw_text(
    win_t *win,
    const char *text,
    const sprite_t char_sprites[256],
    int16_t x,
    int16_t y,
    uint16_t max_width,
    uint16_t scale,
    void (*if_too_long)(const char *original_str, char *truncated_str, size_t len),
    bool center
);

/**
 * @brief Requests to send a file through the serial port
 * @param const char *fullpath : The full path of the file to send
 * @return int : 0 on success, non-zero otherwise
 */
int send_file_through_serial_port(const win_t *win, const char *fullpath);

/**
 * @brief Requests to receive a file, storing its contents in the given file
 * @param fullpath 
 * @return int : 0 on success, non-zero otherwise
 */
int receive_file_through_serial_port(const win_t *win, const char *fullpath);

/**
 * @brief Get the width of the window
 * @param const win_t *win : window to get the width of
 * @return uint16_t : width of the window
 */
uint16_t win_width(const win_t *win);

/**
 * @brief Get the height of the window
 * @param const win_t *win : window to get the height of
 * @return uint16_t : width of the window
 */
uint16_t win_height(const win_t *win);

/**
 * @brief Get the x-position of the window
 * @param const win_t *win : window to get the x-position of
 * @return uint16_t : x-position of the leftmost pixel of the window
 */
int16_t win_x(const win_t *win);

/**
 * @brief Get the y-position of the window
 * @param const win_t *win : window to get the y-position of
 * @return uint16_t : y-position of the upmost pixel of the window
 */
int16_t win_y(const win_t *win);

#endif /* LCOM_PROJ_RAKOON_API_H */
