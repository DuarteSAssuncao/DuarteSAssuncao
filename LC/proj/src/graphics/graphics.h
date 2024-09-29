/**
 * @file graphics.h
 * @brief Declaration of functions to handle the graphics (VBE)
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_VBE_H
#define LCOM_VBE_H

#include <lcom/lcf.h>
#include <app/window.h>
#include <lcom/xpm.h>

#ifndef byte_t
    #define byte_t uint8_t
#endif

//! Match of video modes
typedef enum {
    COLOR_INDEXED = XPM_INDEXED,
    RGB_5_5_5 = XPM_1_5_5_5,
    RGB_5_6_5 = XPM_5_6_5,
    RGB_8_8_8 = XPM_8_8_8,
    RGB_8_8_8_8 = XPM_8_8_8_8,
    COLOR_INVALID = INVALID_XPM
} color_type_t;

/**
 * @brief Sets up the current mode to be used in the project, along with the allocated memory and constants
 * @param uint16_t mode : the mode to set
 * @return int : 0 on success
 */
int (vg_start)(uint16_t mode);

/**
 * @brief Returns to text mode
 * @return int : 0 on success
 */
int (vg_set_text_mode)();

/**
 * @brief Refresh the page by changing buffers
 * @return int : 0 on success
 */
int (vg_refresh)();

/**
 * @brief Alternative, less fallible function to draw a rectangle
 * @param window_t *win : which window to draw the rectangle on
 * @param uint16_t x : x-position of leftmost pixel
 * @param uint16_t y : y-position of upmost pixel
 * @param uint16_t width : width of the rectangle
 * @param uint16_t height : height of the rectangle
 * @param uint32_t color : color of the rectangle
 * @return int : 0 on success
 */
int (draw_rect)(window_t *win, int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t color);

#define vg_draw_rect(x,y,width,height,color) draw_rect(NULL,x,y,width,height,color)

/**
 * @brief Draw an image on a certain window
 * @param window_t *win : which window to draw the image on
 * @param uint8_t *image : image to draw
 * @param uint16_t width : width of the image
 * @param uint16_t height : height of the image
 * @param uint16_t x : x-position of leftmost pixel
 * @param uint16_t y : y-position of upmost pixel
 * @return int : 0 on success
 */
int (draw_image)(window_t *window, uint8_t *image, uint16_t width, uint16_t height, int16_t x, int16_t y);

/**
 * @brief Draw a sprite on a certain window
 * @param window_t *win : which window to draw the sprite on
 * @param const sprite_t *img : sprite to draw
 * @param int16_t x : x-position of leftmost pixel
 * @param int16_t y : y-position of upmost pixel
 * @return int : 0 on success
 */
int (draw_sprite)(window_t *window, const xpm_image_t *img, int16_t x, int16_t y);

#define vg_draw_image(image,width,height,x,y) draw_image(NULL,image,width,height,x,y)
#define vg_draw_sprite(img,x,y) draw_sprite(NULL,img,x,y)
#define vg_draw_xpm vg_draw_sprite

/**
 * @brief Draws a transparent image on a certain window
 * @param window_t *window : window on where to draw
 * @param uint8_t *image : transparent image to draw
 * @param uint16_t width : width of the image
 * @param uint16_t height : height of the image
 * @param int16_t x : x-position of leftmost pixel
 * @param int16_t y : y-position of upmost pixel
 * @param uint32_t ignore : color to ignore, i.e., draw as transparent
 * @return int : 0 on success
 */
int (draw_transparent_image)(window_t * win, uint8_t * image, uint16_t width, uint16_t height, uint16_t x, uint16_t y, uint32_t ignore);

#define vg_draw_transparent_image(image,width,height,x,y,i) draw_transparent_image(NULL,image,width,height,x,y,i)

/**
 * @brief Fills the whole buffer
 * @param uint8_t *from : from where to copy
 * @return int : always 0
 */
int (vg_fill)(uint8_t *from);

/**
 * @brief Clear the screen
 * @return int : 0 on success
 */
int (vg_clrscr)();

/**
 * @brief Get the x-resolution of the current mode
 * @return uint16_t : x-resolution
 */
uint16_t (vg_get_xres)();

/**
 * @brief Get the y-resolution of the current mode
 * @return uint16_t : y-resolution
 */
uint16_t (vg_get_yres)();

/**
 * @brief Get the number of bytes per pixel
 * @return uint8_t : number of bytes per pixel
 */
uint8_t (vg_bytes_per_pixel)();

/**
 * @brief Get the size of the frame buffer
 * @return size_t : size of the frame buffer
 */
size_t (vg_frame_buffer_size)();

//! Struct with the information about the color
typedef struct color_info {
    enum {
        INDEXED,                    /*!< The color is represented by an index */
        DIRECT                      /*!< The color is represented as RGB(A) */
    } type;
    uint8_t RedMaskSize;            /*!< Size of direct color red mask in bits */
    uint8_t RedFieldPosition;       /*!< Bit position of lsb of red mask */
    uint8_t GreenMaskSize;          /*!< Size of direct color green mask in bits */
    uint8_t GreenFieldPosition;     /*!< Bit position of lsb of green mask */
    uint8_t BlueMaskSize;           /*!< Size of direct color blue mask in bits */
    uint8_t BlueFieldPosition;      /*!< Bit position of lsb of blue mask */
    uint8_t RsvdMaskSize;           /*!< Size of direct color reserved mask in bits */
    uint8_t RsvdFieldPosition;      /*!< Bit position of lsb of reserved mask */
    uint8_t DirectColorModeInfo;    /*!< Direct color mode attributes */
    uint8_t BitsPerPixel;           /*!< @brief bits per pixel */
} color_info_t;

/**
 * @brief Get the information about the color of the current mode
 * @return color_info_t : struct with information about the color
 */
color_info_t (vg_get_color_info)();

#endif /* LCOM_VBE_H */
