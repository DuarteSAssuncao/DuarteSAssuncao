/**
 * @file app_rtc.c
 * @brief Definition of "higher" RTC functions used in the project
 * @author T17_G1
 * @date 27/05/2024
 */

#include "app_rtc.h"
#include <lab6/rtc.h>

#define DEBUG
//#define DEBUG2
#include <auxiliary/debug.h>
#include "shared.h"

//! Current date
extern date_t date;

//! Whether to update the clock
bool update_clock;

/**
 * @brief Test function for the Real Time Clock
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */ 
int_ret_t (rtc_test_handler)() {
    uint8_t cause = rtc_get_int_cause();

    if (cause & RTC_PERIODIC) {
        printf("Periodic interrupt\n");
    }

    if (cause & RTC_ALARM) {
        printf("Alarm interrupt\n");
    }

    if (cause & RTC_UPDATE) {
        TRY(rtc_get_date(&date),        != 0, "error", INT_EXIT,);
        printf("%d/%02d/%02d, %02d:%02d:%02d\n", 2000 + date.year, date.month, date.day, date.hour, date.min, date.sec);
    }

    return INT_CONTINUE;
}

/**
 * @brief Handler of the Real Time Clock in the project
 * @return int_ret_t : see macros for interrupt return values in interrupts/interrupts.h
 */ 
int_ret_t (rtc_handler)() {
    uint8_t cause = rtc_get_int_cause();

    if (cause & RTC_ALARM) {
        DEBUG_PRINTF2("RTC alarm\n");
        if (rtc_get_date(&date)) {
            DEBUG_PERRORV("rtc_get_date");
            return INT_CONTINUE;
        }
        update_screen = update_clock = true;
        return INT_CONTINUE;
    }

    return INT_CONTINUE;
}
