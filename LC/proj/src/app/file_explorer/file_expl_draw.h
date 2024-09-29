/**
 * @file file_expl_draw.h
 * @brief Load sprites and draw directories entries
 * @author T17_G1
 * @date 31/05/2024
 */

#ifndef LCOM_PROJ_FILE_EXPL_DRAW_H
#define LCOM_PROJ_FILE_EXPL_DRAW_H

#include "../ipc/api.h"
#include "../directories.h"

//! Sprites (folder, file, left-arrow, right-arrow, character in black and white
extern sprite_t folder_sprite, file_sprite, arrow_left_sprite, arrow_right_sprite, black_char_sprites[256], white_char_sprites[256];

/**
 * @brief Loads file/dir icons and letters. Must be called so that you can use the file explorer drawing functions
 * @return int : 0 on success, non-zero otherwise
 */
int file_expl_load_sprites();

/**
 * @brief Draw a directory entry in the center of a square on the file explorer
 * @param win_t *win : window to draw the entry on
 * @param const dir_item_t *entry : entry to draw on the window
 * @param int16_t x : x-position of leftmost pixel of the entry
 * @param int16_t y : y-position of upmost pixel of the entry
 * @param uint16_t square_side_size : 
 * @return int : 0 on success
 */
int fe_draw_dir_entry(win_t *win, const dir_item_t *entry, int16_t x, int16_t y, uint16_t square_side_size);

#endif /* LCOM_PROJ_FILE_EXPL_DRAW_H */
