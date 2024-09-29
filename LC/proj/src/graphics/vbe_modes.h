/**
 * @file vbe_modes.h
 * @brief Macros to match with VBE modes
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_VBE_MODES_H
#define LCOM_VBE_MODES_H

/*
These modes are first defined by their colors and then by their resolution.
The color description is either:
    - INDEXED, where each pixel has a value whose color depends on a table/palette
    - 3 or 4 numbers separated by a '_', which correspond to the bits of each RGB channel and, if applicable, the alpha channel
*/

#define VBE_INDEXED_1024x768    0x105
#define VBE_5_5_5_640x480       0x110
#define VBE_8_8_8_800x600       0x115
#define VBE_5_6_5_1280x1024     0x11A
#define VBE_8_8_8_8_1152x864    0x14C

#endif /* LCOM_VBE_MODES_H */
