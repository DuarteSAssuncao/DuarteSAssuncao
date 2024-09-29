/**
 * @file app_rtc.c
 * @brief Declaration of "higher" RTC functions used in the project
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_PROJ_APP_RTC_H
#define LCOM_PROJ_APP_RTC_H

#include <interrupts/interrupts.h>

/**
 * @brief Test function for the Real Time Clock
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */ 
int_ret_t rtc_test_handler();

/**
 * @brief Handler of the Real Time Clock in the project
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */ 
int_ret_t (rtc_handler)();

#endif /* LCOM_PROJ_APP_RTC_H */
