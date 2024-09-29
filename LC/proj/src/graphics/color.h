/**
 * @file color.h
 * @brief Declaration of color-related macros and a function to blend colors
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef LCOM_PROJ_COLOR_H
#define LCOM_PROJ_COLOR_H

#include <stdint.h>

/**
 * @brief An RGB color value. It has one unused byte to make it easier to transform into ARGB.
 */
typedef union rgb {
    struct {    // Do not change the order
        uint8_t b,g,r,unused;   /*!< Blue, green, red, unused */
    };
    uint32_t hex;
} rgb_t;

/**
 * @brief An ARGB color value.
 */
typedef union argb {
    struct {    // Do not change the order
        uint8_t b,g,r,a;    /*!< Blue, green, red, alpha */
    };
    uint32_t hex;
} argb_t;

/**
 * @brief Blend ARGB colors (alpha-red-green-blue)
 * @param argb_t fg : foreground color
 * @param argb_t bg : background color
 * @return argb_t : the new color
 */
argb_t argb_blend(argb_t fg, argb_t bg);

/** 
 * @brief Custom "format specifier" to use in functions like printf when you want to format an rgb_t value
 * */
#define f_rgb "RGB(%d,%d,%d)"

/**
 * @brief Expression to fill a f_rgb in functions like printf.
 * @example rgb_t color = {.v.r = 255, .v.g = 127, .v.b = 0};
 *          printf("color = " f_rgb "\n", f_rgb_arg(color)); // Output: "color = RGB(255,127,0)"
 */
#define f_rgb_arg(color) (color).v.r,(color).v.g,(color).v.b

/** 
 * @brief String literal to use in functions like printf when you want to format an argb_t value
 * */
#define f_argb "ARGB(%d,%d,%d,%d)"

/**
 * @brief Expression to fill a f_argb in functions like printf
 * @example argb_t color = {.v.a = 150, .v.r = 255, .v.g = 127, .v.b = 0};
 *          printf("color = " f_argb "\n", f_argb_arg(color)); // Output: "color = ARGB(150,255,127,0)"
 */
#define f_argb_arg(color) (color).v.a,(color).v.r,(color).v.g,(color).v.b

#endif /* LCOM_PROJ_COLOR_H */
