/**
 * @file color.c
 * @brief Definition of a function to blend colors
 * @author T17_G1
 * @date 29/05/2024
 */

#include "color.h"

/**
 * @brief Blend ARGB colors (alpha-red-green-blue)
 * @param argb_t fg : foreground color
 * @param argb_t bg : background color
 * @return argb_t : the new color
 */
argb_t argb_blend(argb_t fg, argb_t bg) {
    float alpha_fg = fg.a / 255.0f;
    float alpha_bg = bg.a / 255.0f;

    float alpha_blended = alpha_fg + alpha_bg * (1 - alpha_fg);

    // prevent division by zero
    if (alpha_blended == 0.0f)
        return (argb_t) {.hex = 0};

    float aux = alpha_bg * (1 - alpha_fg);
    return (argb_t) {
        .a = (uint8_t) (alpha_blended * 255.0f),
        .r = (uint8_t) ((fg.r*alpha_fg  +  bg.r*aux)  /  alpha_blended),
        .g = (uint8_t) ((fg.g*alpha_fg  +  bg.g*aux)  /  alpha_blended),
        .b = (uint8_t) ((fg.b*alpha_fg  +  bg.b*aux)  /  alpha_blended),
    };
}
