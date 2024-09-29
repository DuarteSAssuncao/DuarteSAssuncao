/**
 * @file window.h
 * @brief Declaration of functions which draws objects on the windows
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_PROJ_WINDOW_H
#define LCOM_PROJ_WINDOW_H

#include <stdint.h>
#include <stdbool.h>

//! Struct with information about a window
typedef struct window {
    int16_t x,y;
    uint16_t width,height;
    uint8_t *buffer;
} window_t;

int draw_window(const window_t *window);

/**
 * @brief Creates a vew window
 * @param window_t *this : pointer to the window struct to be created
 * @param uint16_t x : x-position of leftmost pixel of the window
 * @param uint16_t y : y-position of upmost pixel of the window
 * @param uint16_t width : width of the window
 * @param uint16_t height : height of the window
 * @return int 0 if succeeded and non-zero otherwise
 */
int new_window(window_t * this, uint16_t x, uint16_t y, uint16_t width, uint16_t height);

/**
 * @brief Closes the window
 * @note Note that the window to be closed will be removed from the windows array
 * @param window_t* this : window to be closed
 * @return int 0 if succeeded and non-zero otherwise
 */
int close_window(window_t * this);

/**
 * @brief Get the xpm of the letter
 * 
 * @param c 
 * @return uint8_t* xpm of the letter if succeeded and NULL otherwise
 */
uint8_t * get_letter_xpm(char c);

/**
 * @brief Draws text on one of the windows, whose letters have an interval 2 * size px
 * @param const window_t * window : where to draw the text
 * @param uint16_t x : x-position of leftmost pixel of the text
 * @param uint16_t y : y-position of upmost pixel of the text
 * @param char string[] : text to draw on the window - it will occupy (8 * n_chars - 2) * size px
 * @param uint16_t n_chars : number of characters to draw
 * @param uint32_t color : color of the text
 * @param uint8_t size : font size (each letter has a height of 11px and a width of 6px, which are multiplied by the size)
 * @return int : 0 on success
 */
int draw_text(const window_t * window, uint16_t x, uint16_t y, char string[], uint16_t n_chars, uint32_t color, uint8_t size);

#endif /* LCOM_PROJ_WINDOW_H */
