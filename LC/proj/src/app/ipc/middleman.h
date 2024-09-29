/**
 * @file middleman.h
 * @brief Declaration of functions to monitor connections
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef PROJ_MIDDLEMAN_H
#define PROJ_MIDDLEMAN_H

/**
 * @brief Initializes the middleman
 * @return int : 0 on success
 */
int rakoon_middleman_init();

/**
 * @brief Starts the middleman
 * @return int : 0 on success
 */
int rakoon_middleman_start();

/**
 * @brief Cleans up the middleman
 * @return void
 */
void rakoon_middleman_cleanup();

#endif
