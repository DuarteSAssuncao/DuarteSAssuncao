/**
 * @file extra_utils.h
 * @brief Some extra utility functions
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_PROJ_EXTRA_UTILS_H
#define LCOM_PROJ_EXTRA_UTILS_H

#include <stdint.h>

//! Tells VSCode to shut up
#ifndef u32_t
    #define u8_t uint8_t
    #define u16_t uint16_t
    #define u32_t uint32_t
    #define u64_t uint64_t
#endif

//! Min and max functions
#ifndef min
    #define min(a,b) (((a) < (b)) ? (a) : (b))
    #define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

/**
 * @brief BIT_RANGE auxiliary macro (only works if lsb <= msb)
 */
#define BIT_RANGE_LSB_MSB(lsb,msb) ((UINT64_MAX >> (63 - (msb))) & (UINT64_MAX << (lsb)))

/**
 * @brief Calculates a mask with bits [a,b] active (e.g. BIT_RANGE(1,3) = 0b00...001110)
 * @details Supports up to 64 bit masks and it doesn't matter whether A is smaller, equal, or greater than B
 */
#define BIT_RANGE(A,B) (A <= B ? BIT_RANGE_LSB_MSB((A),(B)) : BIT_RANGE_LSB_MSB((B),(A)))

#endif /* LCOM_PROJ_EXTRA_UTILS_H */
