/**
 * @file directories.c
 * @brief Definition of "higher" functions to handle files and directories in the project
 * @author T17_G1
 * @date 27/05/2024
 */

#include "directories.h"
#include <auxiliary/ansi_colors.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <machine/limits.h>
#include <stdio.h>

/**
 * @brief Loads a directory and stores in result information about each item in that directory
 * @param const char *path : absolute/relative path to the directory
 * @param vector_dir_item_t *result : list of items in the directory
 * @return int : 0 on success, otherwise result is freed
 */
int (load_dir)(const char *path, vector_dir_item_t *result) {
    if (path == NULL || result == NULL)
        return -1;

    DIR *dir = opendir(path);
    if (dir == NULL)
        return -1;

    size_t initial_size = result->size;

    struct dirent *dirent;
    while ((dirent = readdir(dir)) != NULL) {
        dir_item_t *dentry = vector_extend(result);
        if (dentry == NULL) {
            result->size = initial_size;
            closedir(dir);
            return -1;
        }
        dentry->name_len = dirent->d_namlen;
        dentry->type = dirent->d_type;
        memcpy(dentry->name, dirent->d_name, dentry->name_len + 1);
    }
    closedir(dir);
    return 0;
}

/**
 * @brief Prints the content of a directory
 * @const vector_dir_item_t *list : list of items in the directory
 * @return int : 0 on success
 */
int (print_dir_items)(const vector_dir_item_t *list) {
    dir_item_t *end = list->at + list->size;
    const char *color;
    for (dir_item_t *itr = list->at; itr != end; ++itr) {
        switch (itr->type) {
            case ENTRY_DIR:
                color = ANSI_YELLOW;
                break;
            case ENTRY_LNK:
                color = ANSI_BLUE;
                break;
            default:
                color = ANSI_WHITE;
        }
        printf("%s%s\n", color, itr->name);
    }
    printf(ANSI_RESET "\n");
    return 0;
}

/**
 * @brief Release memory from a node and all of its descendants
 * @param dir_node_t *dir : directory whose memory should be freed
 * @return void
 */
void free_dir_node_and_descendants(dir_node_t *dir) {
    dir_node_t *node = dir;
    while (node != NULL) {
        dir_node_t *tmp = node;
        node = tmp->next;
        free(tmp);
    }
}
