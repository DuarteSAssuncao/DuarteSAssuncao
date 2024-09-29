/**
 * @file file_explorer.c
 * @brief Definition of functions to display the file explorer
 * @author T17_G1
 * @date 29/05/2024
 */

#include <lcom/lcf.h>
#include <stdio.h>
#include "file_explorer.h"
#include "shared.h"
#include <graphics/icons.h>
#include <graphics/graphics.h>

/**
 * @brief Generate the elements (icons) on the given window
 * @param file_explorer_window_t *this : where to generate the elements (icons)
 * @return int : 0 on success
 */
int generate_fe_elements(file_explorer_window_t * this) {
    if (this->elements != NULL) free(this->elements);
    this->n_elements = 0;
    file_element_t * el = (file_element_t*) calloc(this->items.size, sizeof(file_element_t));
    if(el == NULL) return 1;
    this->elements = el;
    uint16_t x = 23, y = 50;
    for(uint16_t i = 0; i < this->items.size; i++) {
        if (y + 50 >= this->window->height) break;
        
        this->elements[i] = (file_element_t) {
            .x_pos = x,
            .y_pos = y,
            .width = 77,
            .height = 50,
            .item = &this->items.at[i],
        };

        this->n_elements++;

        x += 77 + 40;
        if(x + 77 >= this->window->width) {
            x = 23;
            y += 50 + 40;
        }
    }

    return 0;
}

/**
 * @brief Closes a file explorer window, freeing its elements
 * @param file_explorer_window_t *this : window to close
 * @return int : 0 on success
 */
int close_fe_window(file_explorer_window_t * this) {
    free(this->elements);
    this->n_elements = 0;
    free(this->items.at);
    this->items.cap = 0;
    this->items.size = 0;
    for(uint8_t i = 0; i < n_fe; i++) { // Remove the FE from the FE array:
        if((file_explorers + i * sizeof(*file_explorers)) == this) {
            void * dest = NULL;
            dest = memmove(
                file_explorers + i,
                file_explorers + i + 1,
                (n_fe - i - 1) * sizeof(*file_explorers)
            );
            if(dest == NULL) return 1;
            n_fe--;
            break;
        }
    }
    return 0;
}

/**
 * @brief Draws the elements on the given window
 * @param file_explorer_window_t *this : window to draw the elements on
 * @return int : 0 on success
 */
int draw_fe_elements(file_explorer_window_t * this) {
    
    xpm_image_t xpm_doc;
    uint8_t* doc = xpm_load(doc_icon, XPM_8_8_8_8, &xpm_doc);
    if (doc == NULL) {
        printf("Error: Fail load image doc.\n");
        return 1;
    }
    xpm_image_t xpm_folder;
    uint8_t* folder = xpm_load(folder_icon, XPM_8_8_8_8, &xpm_folder);
    if (folder == NULL) {
        printf("Error: Fail load image.\n");
        return 1;
    }
    

    file_element_t *listOfItems = this->elements;
    size_t size = this->n_elements;

    for(uint16_t y = 0; y < size; y++){
        file_element_t item =  listOfItems[y];
        if(item.item->type == ENTRY_DIR){
            draw_image(this->window, folder, xpm_folder.width, xpm_folder.height, item.x_pos, item.y_pos);
        }
        else{
            draw_image(this->window, doc, xpm_doc.width, xpm_doc.height, item.x_pos, item.y_pos);
        }     
    }
    return 0;
}
