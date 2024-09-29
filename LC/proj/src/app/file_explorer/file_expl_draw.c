/**
 * @file file_expl_draw.c
 * @brief Load sprites and draw directories entries
 * @author T17_G1
 * @date 31/05/2024
 */

#include "file_expl_draw.h"
#include "file_expl_icons.h"
#include <graphics/letters.h>
#include <auxiliary/extra_utils.h>

#include <string.h>

#define DEBUG
#include <auxiliary/debug.h>

//! Sprite of a folder, sprite of a file, sprites of characters in black and in white
sprite_t folder_sprite, file_sprite, arrow_left_sprite, arrow_right_sprite, image_sprite, black_char_sprites[256], white_char_sprites[256];

/**
 * @brief Loads file/dir icons and letters. Must be called so that you can use the file explorer drawing functions
 * @return int : 0 on success, non-zero otherwise
 */
int file_expl_load_sprites() {
    if (load_sprite_from_xpm(folder_icon, &folder_sprite)) {
        DEBUG_ERRORV("Failed to load folder icon: %s\n", strerror(errno));
        return -1;
    }
    if (load_sprite_from_xpm(doc_icon, &file_sprite)) {
        DEBUG_ERRORV("Failed to load file icon: %s\n", strerror(errno));
        return -1;
    }
    if (load_sprite_from_xpm(arrow_left_xpm, &arrow_left_sprite)) {
        DEBUG_PERRORV("Failed to load arrow_left_xpm");
        return -1;
    }
    uint16_t width = arrow_left_sprite.width, height = arrow_left_sprite.height;
    arrow_right_sprite = (sprite_t) {
        .width = width,
        .height = height,
        .pixels = malloc(width * height * sizeof(argb_t)),
    };
    if (arrow_right_sprite.pixels == NULL)
        return -1;
    
    for (uint16_t i = 0; i < width; ++i)
        for (uint16_t j = 0; j < height; ++j)
            *sprite_at(arrow_right_sprite, i, j) = *sprite_at(arrow_left_sprite, width-i-1, j);
    
    if (load_sprite_from_xpm(image_icon, &image_sprite)) {
        DEBUG_ERRORV("Failed to load image icon: %s\n", strerror(errno));
        return -1;
    }

    if (load_char_sprites(black_char_sprites)) return -1;

    // generate white characters
    for (size_t i = 0; i < sizeof(black_char_sprites) / sizeof(*black_char_sprites); ++i) {
        uint16_t w = black_char_sprites[i].width, h = black_char_sprites[i].height;
        size_t buffer_size = w * h * sizeof(argb_t);
        white_char_sprites[i] = (sprite_t) {
            .width = w,
            .height = h,
            .pixels = malloc(buffer_size),
        };
        memcpy(white_char_sprites[i].pixels, black_char_sprites[i].pixels, buffer_size);
        sprite_replace_color(&white_char_sprites[i], (argb_t) {.hex = 0xff000000}, (argb_t) {.hex = 0xffffffff});
    }
    return 0;
}

/**
 * @brief Places len or 3 '.' at the end of the string
 * @param const char *original_str : original string to be modified
 * @param char *str : string with the ellipsis
 * @param size_t len : number of dots to place in the string. Reduced to 3 if greater than 3
 * @return void
 */
static void put_ellipsis_on_end(const char *original_str, char *str, size_t len) {
    size_t n_dots = min(3,len);
    memset(str + len - n_dots, '.', n_dots);
}

/**
 * @brief Draw a directory entry on the file explorer
 * @param win_t *win : window to draw the entry on
 * @param const dir_item_t *entry : entry to draw on the window
 * @param int16_t x : x-position of leftmost pixel of the entry
 * @param int16_t y : y-position of upmost pixel of the entry
 * @param uint16_t square_side_size : height and width of the entry
 * @return int : 0 on success
 */
int fe_draw_dir_entry(win_t *win, const dir_item_t *entry, int16_t x, int16_t y, uint16_t square_side_size) {
    const sprite_t *entry_sprite;
    switch (entry->type) {
        case ENTRY_DIR: entry_sprite = &folder_sprite; break;
        default: entry_sprite = &file_sprite;
    }
    if(strcmp(entry->name + entry->name_len - 4, ".bmp") == 0) entry_sprite = &image_sprite;

    // center sprite
    int16_t sprite_x = x + square_side_size / 2 - entry_sprite->width / 2;
    int16_t sprite_y = y + square_side_size / 2 - entry_sprite->height / 2 - square_side_size / 10;

    win_draw_sprite(win, entry_sprite, sprite_x, sprite_y);

    uint16_t scale = 1;
    win_draw_text(win, entry->name, black_char_sprites, x + scale, y + square_side_size - black_char_sprites->height * scale + scale, square_side_size, scale, put_ellipsis_on_end, true);
    win_draw_text(win, entry->name, white_char_sprites, x, y + square_side_size - white_char_sprites->height * scale, square_side_size, scale, put_ellipsis_on_end, true);

    return 0;
}
