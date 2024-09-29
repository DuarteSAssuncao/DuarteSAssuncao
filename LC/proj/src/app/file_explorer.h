/**
 * @file file_explorer.h
 * @brief Declaration of functions to display the file explorer
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef LCOM_PROJ_FILE_EXPLORER_H
#define LCOM_PROJ_FILE_EXPLORER_H

#include "window.h"
#include "directories.h"

//! Element displayed
typedef struct file_element {
    uint16_t x_pos, y_pos, width, height;   /*!< x-position, y-position, width, height */
    dir_item_t * item;                      /*!< Corresponding item */
} file_element_t;

//! "Special" window
typedef struct file_explorer_window {
    window_t * window;          /*!< Actual window */
    dir_node_t * dir;           /*!< Corresponding directory */
    vector_dir_item_t items;    /*!< Corresponding items (list) */
    file_element_t *elements;   /*!< Elements in the window */
    size_t n_elements;          /*!< Number of elements */
} file_explorer_window_t;

/**
 * @brief Generate the elements from the dir_item_list of the given window
 * @param file_explorer_window_t *this : where to generate the elements (icons)
 * @return int : 0 on success
 */
int generate_fe_elements(file_explorer_window_t * this);

/**
 * @brief Closes a file explorer window, freeing its elements
 * @param file_explorer_window_t *this : window to close
 * @return int : 0 on success
 */
int close_fe_window(file_explorer_window_t * this);

/**
 * @brief Draws the elements on the given window
 * @param file_explorer_window_t *this : window to draw the elements on
 * @return int : 0 on success
 */
int draw_fe_elements(file_explorer_window_t * this);

#endif // LCOM_PROJ_FILE_EXPLORER_H
