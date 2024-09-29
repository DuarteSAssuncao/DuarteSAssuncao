/**
 * @file sprite.h
 * @brief Declaration of functions to deal with sprites
 * @author T17_G1
 * @date 02/06/2024
 */

#ifndef LCOM_PROJ_SPRITE_H
#define LCOM_PROJ_SPRITE_H

#include <lcom/lcf.h>
#include <lcom/xpm.h>
#include <stdint.h>
#include "color.h"

//! A simple sprite
typedef struct sprite {
    uint16_t width,height;  /*!< sprite width/height (in pixels) */
    argb_t *pixels;         /*!< sprite/image buffer */
} sprite_t;

/**
 * @return A pointer to the pixel at (x,y)
 */
#define sprite_at(sprite,x,y) ((sprite).pixels + (sprite).width * (y) + (x))

/**
 * @brief Loads an XPM image with RGB/ARGB colors into an ARGB sprite.
 * @param image An array of strings, must contain information in the XPM format.
 * @param result Where to store the resulting sprite.
 * @return 0 on success, non-zero otherwise.
 */
int load_sprite_from_xpm(const char *const*image, sprite_t *result);

/**
 * @brief Sets the color of all pixels that have the 'to_replace' color to 'val'
 * @param sprite Sprite to execute the operation on.
 * @param to_replace Color to be replaced.
 * @param val New color.
 * @return 0 on success, non-zero otherwise.
 */
int sprite_replace_color(sprite_t *sprite, argb_t to_replace, argb_t val);

#endif /* LCOM_PROJ_SPRITE_H */
