/**
 * @file home.c
 * @brief Handles the home directory
 * @author T17_G1
 * @date 29/05/2024
 */

#include "../../ipc/api.h" // window api
#include <lcom/xpm.h>
#include "../../file_explorer.h" // to load home directory
#include <graphics/icons.h>
#include <auxiliary/vector.h>
#include <graphics/sprite.h>
#include <stdio.h>
#include <stdlib.h>

#include "../file_expl_draw.h"

#define DEBUG
#include <auxiliary/debug.h>

//! Sprite of a folder, sprite of a file
sprite_t folder_sprite, file_sprite;

//! A simple element
typedef struct element {
    int16_t x,y;            /*!< Coordinates */
    uint16_t width,height;  /*!< Width and height */
    void (*handler)(struct element* target, const rakoon_msg_t* msg);   /*!< Custom handler */
    void *info;             /*!< Information about the element */
} element_t;

//! Element of a directory
typedef struct dir_element {
    element_t e_info;       /*!< Information - pseudo-inheritance */
    dir_item_t *dir_item;   /*!< Corresponding directory element (struct) */
} dir_element_t;

//! List of items
vector_dir_item_t items;

//! Array of elements of directory
vector(dir_element_t) dir_elements;

static void dir_element_handler(element_t* target, const rakoon_msg_t* msg);

//! Home directory
const char *homedir;

/**
 * @brief Main function
 * @return int : 0 on success
 */
int main() {
    homedir = getenv("HOME");
    if (homedir == NULL) {
        perror("getenv(\"HOME\")");
        return 1;
    }

    if (file_expl_load_sprites()) {
        perror("file_expl_load_sprites");
        return 1;
    }

    if (vector_init(&items)) {
        perror("vector_init");
        return 1;
    }

    if (load_dir(homedir, &items)) {
        perror("load_dir");
        return 1;
    }

    if (vector_init_cap(&dir_elements, items.size)) {
        perror("vector_init_cap");
        return 1;
    }

    for (size_t i = 0; i < items.size; ++i) {
        dir_element_t *element = vector_extend(&dir_elements);
        if (element == NULL) {
            perror("vector_extend");
            return 1;
        }
        *element = (dir_element_t) {
            .dir_item = items.at + i
        };
    }

    win_attr_t attr = {
        .y = 60,
        .width = 1152, // WARNING: HARDCODED (screen width)
        .height = 804, // WARNING: HARDCODED (screen height - 60)
    };

    win_t *win = win_create(&attr);
    if (win == NULL) {
        perror("win_create");
        return 1;
    }

    win_fill_rgb(win, (rgb_t) {.hex = 0xdddddd});

    sprite_t rakoon_sprite;
    load_sprite_from_xpm(minix3_xpm, &rakoon_sprite);
    uint16_t scale = 4;
    win_draw_sprite_scaled(win, &rakoon_sprite,
        (win_width(win) - scale * rakoon_sprite.width) / 2,
        (win_height(win) - scale * rakoon_sprite.height) / 2,
        scale
    );

    int16_t square_size = 100, padding = 25;
    int16_t x = padding, y = padding;
    size_t fit_on_screen = 0;
    for (size_t i = 0; i < dir_elements.size; ++i, ++fit_on_screen) {
        dir_elements.at[i].e_info = (element_t) {
            .x = x,
            .y = y,
            .width = square_size,
            .height = square_size,
            .handler = dir_element_handler,
            .info = &items.at[i],
        };

        win_draw_rect(win,x,y,square_size,square_size,(argb_t) {.hex = 0x77666666});

        fe_draw_dir_entry(win, dir_elements.at[i].dir_item, x, y, square_size);

        x += square_size + padding;
        if (x > win_width(win) - square_size - padding) {
            y += square_size + padding;
            if (y > win_height(win))
                break;
            x = padding;
        }
    }

    if (win_refresh(win)) {
        perror("win_refresh");
        return 1;
    }

    bool end = false;
    while (!end) {
        rakoon_msg_t msg;
        if (win_wait_event(win, &msg)) {
            perror("win_wait_event");
            break;
        }

        switch (msg.m_type) {
            case RKE_MOUSE: {
                mouse_data_t *info = (mouse_data_t*) msg.data;

                if (info->type == MOUSE_LEFT_DOUBLE_CLICK) {
                    for (size_t i = 0; i < fit_on_screen; ++i) {
                        element_t *el = &dir_elements.at[i].e_info;
                        if (info->x >= el->x && info->y >= el->y && info->x <= el->x + el->width && info->y <= el->y + el->height) {
                            if (el->handler == NULL) {
                                DEBUG_WARNV("dir_element should not have NULL handler\n");
                                continue;
                            }
                            el->handler(el, &msg); // el handler
                            break;
                        }
                    }
                }
                break;
            }
            case RKE_SHUTDOWN:
            case RKE_CLOSE_WIN:
                end = true;
                break;
        }
    }
    win_close(win);
    return 0;
}

/**
 * @brief Handler of a directory element
 * @param element_t* target : which element to handle
 * @param const rakoon_msg_t* msg : a message
 * @return void
 */
static void dir_element_handler(element_t* target, const rakoon_msg_t* msg) {
    if (msg->m_type != RKE_MOUSE || ((mouse_data_t*)msg->data)->type != MOUSE_LEFT_DOUBLE_CLICK) {
        DEBUG_WARNV("handler called without double click!\n");
        return;
    }

    dir_item_t *entry = target->info;
    char path[1024];
    char * end = stpcpy(path, homedir);
    *end = '/';
    end[1] = '\0';
    strcat(end + 1, entry->name);

    DEBUG_INFOV("Directory/File/Image Path: %s\n", path);

    if (entry->type == ENTRY_DIR) {
        if (fork() == 0) {
            execl("file_expl", "file_expl", path, NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        }
    } else if (entry->type == ENTRY_REG && strcmp(entry->name + entry->name_len - 4, ".bmp") == 0) {
        if (fork() == 0) {
            execl("image_viewer", "image_viewer", path, NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        }
    } else if (entry->type == ENTRY_REG) {
        if (fork() == 0) {
            execl("text_viewer", "text_viewer", path, NULL);
            perror("execl");
            exit(EXIT_FAILURE);
        }
    }
}
