/**
 * @file timer_i8254.h
 * @brief Declaration of functions related with i8254, more specifically Timer0
 * @author T17_G1
 * @date 26/05/2024
 */


#ifndef LCOM_PROJ_I8254_H
#define LCOM_PROJ_I8254_H

#include <lcom/lcf.h>
#include <auxiliary/extra_utils.h>

// Timer constants
#define TIMER_FREQ 1193182      /*!< @brief Maximum clock frequency */
#define TIMER0_DEFAULT_FREQ 60  /*!< @brief Default Minix3 timer frequency */
#define TIMER0_IRQ 0            /*!< @brief Timer 0 IRQ line */


// I/O port addresses
#define TIMER_0    0x40                 /*!< @brief Timer 0 count register */
#define TIMER_1    0x41                 /*!< @brief Timer 1 count register */
#define TIMER_2    0x42                 /*!< @brief Timer 2 count register */
#define TIMER_CTRL 0x43                 /*!< @brief Control register */
#define TIMER_PORT(n) (TIMER_0 + (n))   /*!< @brief Returns the port of a timer */
#define SPEAKER_CTRL 0x61               /*!< @brief Register for speaker control  */


// Timer selection: bits 7 and 6
#define TIMER_SEL0   0x00               /*!< @brief Control Word for Timer 0 */
#define TIMER_SEL1   BIT(6)             /*!< @brief Control Word for Timer 1 */
#define TIMER_SEL2   BIT(7)             /*!< @brief Control Word for Timer 2 */
#define TIMER_SEL(n) ((n) << 6)         /*!< @brief Select a timer */
#define TIMER_RB_CMD (BIT(7) | BIT(6))  /*!< @brief Read Back Command */


// Register selection: bits 5 and 4
#define TIMER_LSB     BIT(4)                    /*!< @brief Initialize Counter LSB only */
#define TIMER_MSB     BIT(5)                    /*!< @brief Initialize Counter MSB only */
#define TIMER_LSB_MSB (TIMER_LSB | TIMER_MSB)   /*!< @brief Initialize LSB and then MSB */


// Operating mode: bits 3, 2 and 1 
#define TIMER_SQR_WAVE (BIT(2) | BIT(1))                /*!< @brief Mode 3: square wave generator */
#define TIMER_RATE_GEN BIT(2)                           /*!< @brief Mode 2: rate generator */
#define TIMER_COUNTING_MODE (BIT(1) | BIT(2) | BIT(3))  /*!< @brief Mask for getting the counting mode */


// Counting mode: bit 0
#define TIMER_BCD 0x01  /*!< @brief Count in BCD */
#define TIMER_BIN 0x00  /*!< @brief Count in binary */


// READ-BACK COMMAND FORMAT
// Note: if TIMER_RB_DONT_READ_COUNT_ and TIMER_RB_DONT_READ_STATUS_ are both false, it reads status and then the count
#define TIMER_RB_DONT_READ_COUNT_  BIT(5)   /*!< @brief Won't read count if true */
#define TIMER_RB_DONT_READ_STATUS_ BIT(4)   /*!< @brief Won't read status if true */
#define TIMER_RB_SEL(n)  BIT((n) + 1)       /*!< @brief Sets a timer to read from */

#endif /* LCOM_PROJ_I8254_H */
