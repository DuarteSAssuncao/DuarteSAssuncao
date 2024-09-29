/**
 * @file file_expl.c
 * @brief Definition of functions to handle the File Explorer
 * @author T17_G1
 * @date 31/05/2024
 */

#include "../ipc/api.h"
#include "../file_explorer.h"
#include <graphics/sprite.h>
#include <graphics/icons.h>
#include <auxiliary/vector.h>
#include <auxiliary/extra_utils.h>
#include <graphics/icons.h>

#include <stdio.h>
#include <stdlib.h>

#include "file_expl_draw.h"

#define TOP_BAR_HEIGHT 40

#define DEBUG
//#define DEBUG2
#include "auxiliary/debug.h"

/**
 * @brief Prints the message to the error output and exits the program
 * @param const char *error_msg : error message
 * @return void
 */
void exit_perror(const char *error_msg) {
    perror(error_msg);
    exit(EXIT_FAILURE);
}

//! The 'root' of the file explorer (argv[0])
dir_node_t *start;

//! Current working directory
dir_node_t *cwd;

//! A simple element
typedef struct element {
    int16_t x,y;            /*!< Coordinates */
    uint16_t width,height;  /*!< Width and height */
} element_t;

bool is_in_hitbox(int16_t x, int16_t y, const element_t *el);

//! Scale of the arrom
const uint16_t arrow_scale = 2;

//! Arrow to the left, arrow to the right
element_t left_arrow, right_arrow;

//! Element of a directory
typedef struct dir_element {
    element_t e_info;   /*!< Information abount the element (inheritance) */
    bool selected;      /*!< Whether the element is selected */
} dir_element_t;

//! Items of the current directory
vector_dir_item_t items;

//! Element-related info for each item of the current directory
vector(dir_element_t) dir_elements;

//! Number of elements that fit on the screen
size_t fit_on_screen;

int draw_elements(win_t *win, size_t *fit_on_screen);

void unselect_all_entries();

/**
 * @brief Changes the current directory of the program to $path and creates a node with the full path
 * @param const char *path : relative/absolute path of the directory
 * @param dir_node_t *cwd : If not NULL, will be updated accordingly (cwd->next = new_node, new_node->previous = cwd, and cwd's descendants are freed)
 * @return dir_node_t* : The new node on success, NULL otherwise
 * @note The new node is allocated dynamically and should be deallocated with free()
 */
dir_node_t* change_dir(const char *path, dir_node_t *cwd);

int load_dir_and_update_state(const char *path, vector_dir_item_t *contents);

bool set_cwd(dir_node_t *node);

//! Information from the keyboard
keyboard_data_t kb_info;

/**
 * @brief Main function
 * @param int argc : number of arguments passed to the function
 * @param char **argv : argv[0] = full path of the directory to start at
 * @return int : 0 on success
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fullpath>\n", argv[0]);
        return 1;
    }

    const char *fullpath = argv[1];

    if (fullpath[0] != '/') {
        fprintf(stderr, "%s: Path provided (\"%s\") is not a full path (it should start with '/')\n", argv[0], fullpath);
        return 1;
    }

    char text_viewer_path[256];
    if (getcwd(text_viewer_path, sizeof(text_viewer_path)) == NULL) {
        DEBUG_PERRORV("getcwd");
        return 1;
    }
    strcat(text_viewer_path + strlen(text_viewer_path), "/text_viewer");

    char image_viewer_path[256];
    if (getcwd(image_viewer_path, sizeof(image_viewer_path)) == NULL) {
        DEBUG_PERRORV("getcwd");
        return 1;
    }
    strcat(image_viewer_path + strlen(image_viewer_path), "/image_viewer");

    if ((start = cwd = change_dir(fullpath, NULL)) == NULL)
        exit_perror("change_dir");
    
    if (vector_init(&items) || vector_init(&dir_elements))
        exit_perror("vector_init");
    
    if (load_dir_and_update_state(".", &items))
        exit_perror("load_dir_and_update_state");

    if (file_expl_load_sprites())
        exit_perror("file_expl_load_sprites");
    
    left_arrow = right_arrow = (element_t) {
        .x = 10,
        .y = 10,
        .width = arrow_scale * arrow_left_sprite.width,
        .height = arrow_scale * arrow_left_sprite.height,
    };
    right_arrow.x += left_arrow.width + 10;

    win_attr_t attr = {
        .x = 50, // rand() % 1152 + 50,
        .y = 90, // rand() % 864 + 90,
        .width = 800, // 150 + rand() % 900,
        .height = 600, // 100 + rand() % 600,
    };

    win_t *win = win_create(&attr);
    if (win == NULL) {
        perror("win_create");
        return 1;
    }

    draw_elements(win, &fit_on_screen);

    bool end = false;
    bool refresh = false;
    while (!end) {
        rakoon_msg_t msg;
        if (win_wait_event(win, &msg)) {
            perror("win_wait_event");
            break;
        }

        switch (msg.m_type) {
            case RKE_MOUSE: {
                mouse_data_t *info = (mouse_data_t*) msg.data;

                size_t i = 0;
                for (; i < fit_on_screen; ++i) {
                    element_t *el = &dir_elements.at[i].e_info;

                    // check if mouse is on element
                    if (is_in_hitbox(info->x, info->y, el))
                        break;
                }

                switch (info->type) {
                    case MOUSE_LEFT_CLICK:
                        if (is_in_hitbox(info->x, info->y, &left_arrow)) {
                            if (set_cwd(cwd->previous))
                                refresh = true;
                            break;
                        }
                        if (is_in_hitbox(info->x, info->y, &right_arrow)) {
                            if (set_cwd(cwd->next))
                                refresh = true;
                            break;
                        }

                        if (i > fit_on_screen) {
                            DEBUG_INFOV("No selected entry on click\n");
                            unselect_all_entries();
                            break;
                        }
                        dir_element_t *el = &dir_elements.at[i];
                        refresh = true;

                        switch (kb_info.modifiers) {
                            case 0:
                                DEBUG_INFOV("No modifiers on click -> select\n");
                                unselect_all_entries();
                                el->selected = true;
                                break;
                            case MOD_CTRL:
                                DEBUG_INFOV("Ctrl on click -> el->selected = !el->selected;\n");
                                el->selected = !el->selected;
                                break;
                            default:
                                DEBUG_INFOV("Invalid modifiers for left click\n");
                                break;
                        }
                        break;
                    case MOUSE_LEFT_DOUBLE_CLICK:
                        if (i > fit_on_screen)
                            break;
                        dir_item_t *entry = &items.at[i];
                        if (entry->type == ENTRY_DIR) {
                            refresh = true;

                            dir_node_t *temp = change_dir(entry->name, cwd);
                            if (temp == NULL)
                                DEBUG_ERRORV("change_dir(\"%s\"): %s\n", entry->name, strerror(errno));
                            else
                                cwd = temp;
                            vector_clear(&items);
                            if (load_dir_and_update_state(".", &items))
                                DEBUG_PERRORV("load_dir_and_update_state");
                        } else if (entry->type == ENTRY_REG && strcmp(entry->name + entry->name_len - 4, ".bmp") == 0) {
                            char path[1024];
                            char * end = stpcpy(path, cwd->fullpath);
                            *end = '/';
                            end[1] = '\0';
                            strcat(end + 1, entry->name);

                            DEBUG_INFOV("Directory/File/Image Path: %s\n", path);

                            if (fork() == 0) {
                                DEBUG_PRINTF2("execl(\"%s\", \"%s\", \"%s\", NULL)\n", image_viewer_path, image_viewer_path, path);
                                execl(image_viewer_path, image_viewer_path, path, NULL);
                                perror("execl");
                                exit(EXIT_FAILURE);
                            }
                        } else if (entry->type == ENTRY_REG) {
                            char path[1024];
                            char * end = stpcpy(path, cwd->fullpath);
                            *end = '/';
                            end[1] = '\0';
                            strcat(end + 1, entry->name);

                            DEBUG_INFOV("Directory/File/Image Path: %s\n", path);

                            if (fork() == 0) {
                                execl(text_viewer_path, text_viewer_path, path, NULL);
                                perror("execl");
                                exit(EXIT_FAILURE);
                            }
                        }

                        break;
                    default:
                        break;
                }
                break;
            }
            case RKE_KEYBOARD: {
                memcpy(&kb_info, msg.data, sizeof(kb_info));
                if (kb_info.release)
                    break;
                else {
                    switch (kb_info.code) {
                        case KEY_ARROW_LEFT:
                            if (kb_info.modifiers == MOD_ALT) {
                                if (cwd->previous != NULL) {
                                    set_cwd(cwd->previous);
                                    refresh = true;
                                }
                            }
                            break;
                        case KEY_ARROW_RIGHT:
                            if (kb_info.modifiers == MOD_ALT) {
                                if (cwd->next != NULL) {
                                    set_cwd(cwd->next);
                                    refresh = true;
                                }
                            }
                            break;
                        case KEY_C:
                            if (kb_info.modifiers == MOD_CTRL)
                                DEBUG_INFOV("Ctrl + C\n");
                            break;
                        case KEY_V:
                            if (kb_info.modifiers == MOD_CTRL)
                                DEBUG_INFOV("Ctrl + V\n");
                            break;
                        case KEY_F5:
                            load_dir_and_update_state(".", &items);
                            refresh = true;
                            break;
                        default:
                            break;
                    }
                }
            }
            break;
            case RKE_SHUTDOWN:
            case RKE_CLOSE_WIN:
                end = true;
                break;
        }

        if (refresh)
            draw_elements(win, &fit_on_screen);
        refresh = false;
    }
    win_close(win);
    vector_destruct(&items);
    vector_destruct(&dir_elements);
    free_dir_node_and_descendants(start);
    return 0;
}

/**
 * @brief Places either len or 3 '.' at the beginning of a string
 * @param const char *orig : original string
 * @param char *copy : copy string
 * @param size_t len : number of dots. If greater than 3, it is reduced to 3
 * @return void
 */
static void put_ellipsis_on_beginning(const char *orig, char *copy, size_t len) {
    size_t n_dots = min(3,len);
    memset(copy, '.', n_dots);
    int orig_len = strlen(orig);
    memcpy(copy + n_dots, orig + orig_len - len + n_dots, len - n_dots);
}

/**
 * @brief Draw elements on the given window
 * @param win_t *win : window to draw the elements on
 * @param size_t *fit_on_screen : counter of elements on the screen
 * @return int : 0 on success
 */
int draw_elements(win_t *win, size_t *fit_on_screen) {
    win_fill_rgb(win, (rgb_t) {.hex = 0xeeeeee});

    win_draw_sprite_scaled(win, &arrow_left_sprite, left_arrow.x, left_arrow.y, arrow_scale);
    win_draw_sprite_scaled(win, &arrow_right_sprite, right_arrow.x, right_arrow.y, arrow_scale);
    win_paste_rect(win, 0, TOP_BAR_HEIGHT - 2, win_width(win), 2, (rgb_t) {.hex = 0x555555});

    int16_t arrow_box_end = right_arrow.x + right_arrow.width + 10;
    win_paste_rect(win, arrow_box_end, 0, 2, TOP_BAR_HEIGHT, (rgb_t) {.hex = 0x555555});

    uint16_t cwd_scale = 2;
    int16_t cwd_begin = arrow_box_end + 10;
    win_draw_text(win, cwd->fullpath, black_char_sprites,
        cwd_begin, // x : after the arrows
        (TOP_BAR_HEIGHT - cwd_scale * white_char_sprites->height) / 2, // y : center on the top bar
        win_width(win) - cwd_begin,
        cwd_scale,
        put_ellipsis_on_beginning,
        false
    );

    int16_t square_size = 100, padding = 25;
    int16_t x = padding, y = TOP_BAR_HEIGHT + padding;
    *fit_on_screen = 0;

    vector_resize(&dir_elements, items.size);

    for (size_t i = 0; i < dir_elements.size; ++i, ++*fit_on_screen) {
        win_draw_rect(win,x,y,square_size,square_size, (argb_t) {.hex = 0x77666666});

        dir_element_t *el = &dir_elements.at[i];

        el->e_info = (element_t) {
            .width = square_size,
            .height = square_size,
            .x = x,
            .y = y,
        };

        //DEBUG_PRINTF2("fe_draw_dir_entry(x = %d, y = %d, square_size = %d)\n", x, y, square_size);
        fe_draw_dir_entry(win, items.at + i, x, y, square_size);

        if (el->selected)
            win_draw_rect(win, x, y, square_size, square_size, (argb_t) {.hex = 0x777777ff});

        x += square_size + padding;
        if (x > win_width(win) - square_size - padding) {
            y += square_size + padding;
            if (y > win_height(win))
                break;
            x = padding;
        }
    }

    return win_refresh(win);
}

/**
 * @brief Change directory
 * @param const char *path : path of the directory to change to
 * @param dir_node_t *cwd : current directory, works as the previous one to the new one (for example, when using "cd -" in Unix)
 * @return dir_node_t* : the "new" directory
 */
dir_node_t* change_dir(const char *path, dir_node_t *cwd) {
    if (path == NULL)
        return NULL;

    DEBUG_PRINTF2("chdir(\"%s\")\n", path);
    if (chdir(path)) {
        DEBUG_PERRORV("chdir");
        return NULL;
    }

    dir_node_t *node = malloc(sizeof(*node));
    if (node == NULL)
        return NULL;

    DEBUG_PRINTF2("getcwd\n");
    *node = (dir_node_t) {.previous = cwd};
    if (getcwd(node->fullpath, sizeof(node->fullpath)) == NULL) {
        DEBUG_PERRORV("getcwd");
        free(node);
        return NULL;
    }

    if (cwd != NULL) {
        free_dir_node_and_descendants(cwd->next);
        cwd->next = node;
    }
    return node;
}

/**
 * @brief Change all "selected" fields to false
 * @return void
 */
void unselect_all_entries() {
    for (size_t i = 0; i < dir_elements.size; ++i)
        dir_elements.at[i].selected = false;
}

/**
 * @brief Set current working directory
 * @param dir_node_t *node : directory to set to
 * @return bool : true if successful (for a change)
 */
bool set_cwd(dir_node_t *node) {
    if (node == NULL)
        return false;

    DEBUG_PRINTF2("\"%s\" -> \"%s\"\n", cwd->fullpath, node->fullpath);
    cwd = node;
    vector_clear(&items);
    if (chdir(cwd->fullpath)) {
        DEBUG_PERRORV("chdir");
        return false;
    }
    DEBUG_PRINTF2("load_dir_and_update_state(\"%s\", &items)\n", cwd->fullpath);
    if (load_dir_and_update_state(cwd->fullpath, &items))
        DEBUG_PERRORV("load_dir_and_update_state");
    return true;
}

/**
 * @brief Whether the mouse is currently over the element
 * @param int16_t x : x-position of the mouse
 * @param int16_t y : y-position of the mouse
 * @param const element_t *el : element to check if in hitbox
 * @return bool
 */
bool is_in_hitbox(int16_t x, int16_t y, const element_t *el) {
    return x >= el->x && x < el->x + el->width && y >= el->y && y < el->y + el->height;
}

/**
 * @brief Loads a directory and updates the contents, setting all entries as unselected
 * @param const char *path : directory to load
 * @param vector_dir_item_t *contents : contents to update
 * @return int : 0 on success
 */
int load_dir_and_update_state(const char *path, vector_dir_item_t *contents) {
    vector_clear(contents);
    if (load_dir(path, contents)) {
        DEBUG_PERRORV("load_dir");
        return -1;
    }
    vector_resize(&dir_elements, contents->size);
    unselect_all_entries();
    return 0;
}
