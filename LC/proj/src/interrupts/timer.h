/**
 * @file timer.h
 * @brief Declaration of functions to dea with the timer and its observers
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef LCOM_PROJ_TIMER_H
#define LCOM_PROJ_TIMER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initializes some internal timer variables so that you can properly use it.
 * @return 0 on success, non-zero otherwise. 
 */
int timer_init();

/**
 * @brief Adds a counter to the timer that will decrease for each tick until it reaches 0
 * @param int ticks : must contain amount of ticks to wait. To convert time, use timer_millis_to_ticks()
 * @param void *id : if not NULL, will be used as the identifier of this observer, so that you can interrupt/cancel it
 * @param void (*action)() : if not NULL, will be executed when the count reaches 0
 * @param bool repeat : if true, the counter will automatically restart after reaching 0, otherwise, the observer will be removed after reaching 0
 * @return int : 0 on success, non-zero otherwise
 */
int timer_add_observer(int ticks, void* id, void (*action)(), bool repeat);

/**
 * @brief Removes the observer with the given identifier
 * @param void *id : observer identifier
 * @return 0 on success, non-zero otherwise
 */
int timer_remove_observer(void* id);

/**
 * @brief Turns milliseconds to ticks in the timer
 * @param int millisecons : number of millisecons
 * @return int : the timer ticks needed to pass the specified amount of milliseconds
 * @warning This timer is not very precise, and may be off by multiple milliseconds
 */
int timer_millis_to_ticks(int milliseconds);

/**
 * @brief Get the frequency of the timer
 * @return The frequency (Hz) of the timer
 */
uint32_t timer_get_frequency();

#endif /* LCOM_PROJ_TIMER_H */
