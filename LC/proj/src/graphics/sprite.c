/**
 * @file sprite.c
 * @brief Definition of functions to load a sprite from a xpm and to replace a color in a sprite
 * @author T17_G1
 * @date 31/05/2024
 */

#include "sprite.h"
#include <auxiliary/vector.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//#define DEBUG
//#define DEBUG2
#include <auxiliary/debug.h>

/**
 * @brief Load a sprite from a XPM
 * @param const char *const *image : XPM to get the sprite from
 * @param sprite_t *result : where to store the resulting sprite
 * @return int : 0 on success, EINVAL otherwise
 */
int load_sprite_from_xpm(const char *const* image, sprite_t *result) {
    if (image == NULL || result == NULL)
        return EINVAL;

    // read first line (header)
    uint32_t n_colors, chars_per_pixel;
    int values_read = sscanf(image[0], "%hu %hu %u %u", &result->width, &result->height, &n_colors, &chars_per_pixel);

    if (values_read == 3)
        chars_per_pixel = 1; // 4th number is 1 by omittion
    else if (values_read != 4) {
        DEBUG_ERRORV("Expected 3 or 4 numbers on first line, got %d instead\n", values_read);
        return EINVAL;
    }

    // Warning: Variable-length arrays are not widely supported
    char color_map[n_colors][chars_per_pixel + 1];
    argb_t colors[n_colors];
    result->pixels = calloc(1, result->width * result->height * sizeof(argb_t));
    char color_name[16];

    DEBUG_INFOV("width = %d, height = %d, n_colors = %d, chars_per_pixel = %d\n", result->width, result->height, n_colors, chars_per_pixel);

    DEBUG_INFOV("Reading color table...\n");
    const char *const*colors_lines = image + 1;
    for (uint32_t i = 0; i < n_colors; ++i) {
        DEBUG_PRINTF2("%s\n", colors_lines[i]);

        // copy color name/identifier
        memcpy(color_map[i], colors_lines[i], chars_per_pixel);
        color_map[i][chars_per_pixel] = '\0';

        // ignore 'c' and read color hex
        sscanf(colors_lines[i] + chars_per_pixel, "%s %s", color_name, color_name);

        // ignore '#' and get hex value
        sscanf(color_name + 1, "%x", &colors[i].hex);

        if (strlen(color_name) == 7) // no alpha channel -> default to 0xFF
            colors[i].a = 0xff;
        else if (!strcmp(color_name, "None"))
            colors[i].hex = 0;

        DEBUG_PRINTF2("%s -> %s -> #%08x\n", color_map[i], color_name, colors[i].hex);
    }

    DEBUG_INFOV("Reading pixels...\n");
    const char *const*pixels_lines = image + 1 + n_colors;

    color_name[chars_per_pixel] = '\0';
    for (uint16_t y = 0; y < result->height; ++y) {
        const char *ptr = pixels_lines[y]; // pointer to iterate over the line

        for (uint16_t x = 0; x < result->width; ++x, ptr += chars_per_pixel) {
            memcpy(color_name, ptr, chars_per_pixel);
            DEBUG_PRINTF2("%s", color_name);

            // find corresponding color
            bool found = false;
            for (uint32_t i = 0; i < n_colors; ++i) {
                if (!memcmp(color_name, color_map[i], chars_per_pixel)) {
                    DEBUG_PRINTF2(" -> #%08x", colors[i].hex);
                    *sprite_at(*result, x, y) = colors[i];
                    found = true;
                    break;
                }
            }
            if (!found)
                DEBUG_WARNV("Color for \"%s\" not found!\n", color_name);
            DEBUG_PRINTF2("\n");
        }
    }

    DEBUG_SUCCESSV("XPM loaded successfully!\n");
    return 0;
}

/**
 * @brief Replace a color in a sprite
 * @param sprite_t *sprite : sprite on where to replace the color
 * @param argb_t to_replace : replaced color
 * @param argb_t val : replacement color
 * @return int : always 0
 */
int sprite_replace_color(sprite_t *sprite, argb_t to_replace, argb_t val) {
    argb_t *end = sprite_at(*sprite, sprite->width, sprite->height);
    for (argb_t *pixel = sprite->pixels; pixel != end; ++pixel)
        if (pixel->hex == to_replace.hex)
            *pixel = val;
    return 0;
}
