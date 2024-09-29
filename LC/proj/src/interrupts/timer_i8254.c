/**
 * @file timer_i8254.c
 * @brief Definition of functions related with i8254, more specifically Timer0
 * @author T17_G1
 * @date 26/05/2024
 */

#include <lcom/lcf.h>
#include <lcom/timer.h>
#include "timer_i8254.h"
#include <auxiliary/extra_utils.h>
#include <auxiliary/vector.h>

#define DEBUG
//#define DEBUG2
#include <auxiliary/debug.h>

//! Timer Observer
typedef struct timer_observer {
  void* id;             /*!< identifier */
  const int ticks;      /*!< total amount of ticks */
  int ticks_left;       /*!< decrements for each interrupt until it reaches 0 */
  void (*action)();     /*!< if not NULL, will be executed when ticks_left reaches 0 */
  bool repeat;          /*!< If true, will restart the counter when ticks_left reaches 0 */
} timer_observer_t;

//! A pseudo-vector of timer observers
static vector(timer_observer_t) observers;

//! Frequency of the timer
static uint32_t frequency;

/**
 * @brief Initializes the timer and its observers
 * @return int : 0 on success, -1 otherwise
 */
int timer_init() {
  frequency = 60;
  if (timer_set_frequency(0, 60))
    return -1;
  if (vector_init(&observers))
    return -1;
  return 0;
}

/**
 * @brief Change the frequency of the timer
 * @param uint8_t timer : which timer whose frequency shall be changed
 * @param uint32_t freq : the frequency to set to the given timer
 * @return int : 0 on success
 * @note This also changes (unintentionally) the rate at which time passes in Minix
 */
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (freq == 0 || timer > 2 || freq > TIMER_FREQ)
    return EINVAL;
  
  uint32_t count = TIMER_FREQ / freq;
  
  if (count > UINT16_MAX) // overflow (for a 1193182Hz clock and uint16 counters, the minimum frequency should be 19Hz)
    return ERANGE;
  
  uint8_t lsb = count, msb = count >> 8, config;

  DEBUG_PRINTF("count = 0x%04x msb = 0x%02x lsb = 0x%02x\n", count, msb, lsb);

  int retv;
  if (
    (retv = timer_get_conf(timer, &config)) ||
    (retv = sys_outb(TIMER_CTRL, (config & (TIMER_COUNTING_MODE | TIMER_BCD)) | TIMER_LSB_MSB | TIMER_SEL(timer))) ||
    (retv = sys_outb(TIMER_0, lsb)) ||
    (retv = sys_outb(TIMER_0, msb))
  ) return retv;

  return 0;
}

/**
 * @brief Handles the time
 * @return void
 */
void (timer_int_handler)() {
  for (size_t i = 0; i < observers.size; ++i) {
    timer_observer_t *observer = observers.at + i;
    DEBUG_PRINTF2("Checking observer %p (current counter: %d)...\n", observer->id, observer->ticks_left);
    if (--observer->ticks_left <= 0) {
      DEBUG_INFOV("Finished count for observer %p!\n", observer->id);
      if (observer->action != NULL)
        observer->action();

      if (observer->repeat) {
        DEBUG_INFOV("Restarting observer...\n");
        observer->ticks_left = observer->ticks;
      }
      else {
        DEBUG_INFOV("Removing observer...\n");
        vector_remove(&observers, i--);
      }
    }
  }
}

/**
 * @brief Get the current configuration of the given timer
 * @param uint8_t timer : timer to get the configuration of
 * @param uint8_t *st : pointer to byte to hold the obtained value
 * @return int : 0 on success
 */
int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (st == NULL || timer > 2)
    return EINVAL;
  
  int retv = sys_outb(TIMER_CTRL, TIMER_RB_CMD | TIMER_RB_DONT_READ_COUNT_ | TIMER_RB_SEL(timer));
  if (retv)
    return retv;
  return util_sys_inb(TIMER_PORT(timer), st);
}

/**
 * @brief Adds a counter to the timer that will decrease for each tick until it reaches 0
 * @param int ticks : must contain amount of ticks to wait. To convert time, use timer_millis_to_ticks()
 * @param void *id : if not NULL, will be used as the identifier of this observer, so that you can interrupt/cancel it
 * @param void (*action)() : if not NULL, will be executed when the count reaches 0
 * @param bool repeat : if true, the counter will automatically restart after reaching 0, otherwise, the observer will be removed after reaching 0
 * @return int : 0 on success, non-zero otherwise
 */
int timer_add_observer(int ticks, void* id, void (*action)(), bool repeat) {
  timer_observer_t *new_observer = vector_extend(&observers);
  if (new_observer == NULL)
    return -1;

  *new_observer = (timer_observer_t) {
    .id = id,
    .ticks = ticks,
    .ticks_left = ticks,
    .action = action,
    .repeat = repeat,
  };
  return 0;
}

/**
 * @brief Removes the observer with the given identifier
 * @param void *id : observer identifier
 * @return 0 on success, non-zero otherwise
 */
int timer_remove_observer(void* id) {
  if (id == NULL) return -1;
  DEBUG_INFOV("Removing observer %p...\n", id);
  for (size_t i = 0; i < observers.size; ++i) {
    if (observers.at[i].id == id) {
      vector_remove(&observers, i);
      return 0;
    }
  }
  return -1;
}

/**
 * @brief Turns milliseconds to ticks in the timer
 * @param int millisecons : number of millisecons
 * @return int : the timer ticks needed to pass the specified amount of milliseconds
 * @warning This timer is not very precise, and may be off by multiple milliseconds
 */
int timer_millis_to_ticks(int milliseconds) {
  if (milliseconds > INT_MAX / (int) frequency / 1000) return -1;
  return (milliseconds * frequency) / 1000;
}

/**
 * @brief Get the frequency of the timer
 * @return The frequency (Hz) of the timer
 */
uint32_t timer_get_frequency() {
  return frequency;
}
