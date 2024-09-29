/**
 * @file directories.h
 * @brief Declaration of "higher" functions to handle files and directories in the project
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_PROJ_DIRECTORIES_H
#define LCOM_PROJ_DIRECTORIES_H

#include <dirent.h>
#include <sys/syslimits.h>
#include <auxiliary/vector.h> // dir_item_list_t
#include <sys/stat.h>
#include <stdint.h>

/**
 * @brief Types of directory items. Equal to the ones stored in a struct dirent
 * Source: <dirent.h>
 */
typedef enum entry_type {
    ENTRY_UNKNOWN = 0,
    ENTRY_FIFO = 1,
    ENTRY_CHR = 2,
    ENTRY_DIR = 4,
    ENTRY_BLK = 6,
    ENTRY_REG = 8,
    ENTRY_LNK = 10,
    ENTRY_SOCK = 12,
    ENTRY_WHT = 14,
} entry_type_t;

/**
 * @brief Contains information about an item (file, directory, etc.) from a directory
 */
typedef struct dir_item {
    entry_type_t type;
    char name[NAME_MAX + 1];
    uint16_t name_len;
} dir_item_t;

/**
 * @brief A dinamic array of directory items
 */
typedef vector(dir_item_t) vector_dir_item_t;

/**
 * @brief Used for linked lists to allow going to previous/next dir
 */
typedef struct dir_node {
    char fullpath[PATH_MAX]; // directory path
    struct dir_node *previous, *next;
} dir_node_t;

/**
 * @brief Loads a directory and stores in result information about each item in that directory
 * @param const char *path : absolute/relative path to the directory
 * @param vector_dir_item_t *result : list of items in the directory
 * @return int : 0 on success, otherwise result is freed
 */
int (load_dir)(const char *path, vector_dir_item_t *result);

/**
 * @brief Prints the content of a directory
 * @const vector_dir_item_t *list : list of items in the directory
 * @return int : 0 on success
 */
int (print_dir_items)(const vector_dir_item_t *list);

/**
 * @brief Release memory from a node and all of its descendants
 * @param dir_node_t *dir : directory whose memory should be freed
 * @return void
 */
void (free_dir_node_and_descendants)(dir_node_t *dir);

#endif /* LCOM_PROJ_DIRECTORIES_H */
