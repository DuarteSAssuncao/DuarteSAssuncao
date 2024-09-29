/**
 * @file vbe.h
 * @brief Contains macros for interacting with the VBE (VESA BIOS Extension)
 * @note The source for most of the documentation: https://www.phatcode.net/res/221/files/vbe20.pdf
 * @author T17_G1
 * @date 27/05/2024
 */

#ifndef LCOM_LAB5_VBE_H
#define LCOM_LAB5_VBE_H

#define BIOS_GRAPHICS_INT 0x10  /*!< @brief Interrupt number for BIOS Graphics */
#define VBE_CALL 0x4F           /*!< @brief Used in BIOS call (int 0x10) to distinguish from basic video BIOS services (store this in register AH) */
#define VBE_CALL_AX 0x4F00      /*!< @brief Value to be put in the AX register for a VBE call, you should mask it with a specific function */

/* VBE FUNCTIONS */

/*
To work with these functions, you have to set these registers:
AH = VBE_CALL : this tells the BIOS you're doing a call to the VBE and not directly to the BIOS (or something)
AL = VBE_FUNC_NAME : specifies the function you are calling, e.g. VBE_FUNC_SETMODE

which, using the bitwise OR operator (in the C language, '|'), is the same as:
AX = VBE_CALL_AX | VBE_FUNC_NAME

Other parameters needed by functions are specified by their documentation.
If a function requires ES:DI as a pointer to a structure, you cannot use a C pointer, you need the physical
20-bit address of the structure you want to save to. If you have that, assign the registers to these values:
ES = PB2BASE(addr)
DI = PB2OFF(addr)
I am not sure, but if you want to get an address for this, I believe that you need to allocate to the first
1MB of the memory, which is reserved for the BIOS and such. If you are working in LCOM, just do something like this:
    mmap_t bios_mmap;
    if (lm_alloc(space_needed, &bios_mmap) == NULL) return 1;
    ES = PB2BASE(bios_mmap.phys);
    DI = PB2OFF(bios_mmap.phys);

After setting the registers correctly, call the BIOS_GRAPHICS_INT interrupt (int 0x10)
*/

/**
 * @param ES:DI Pointer to a vg_vbe_contr_info_t
 * @return AX: VBE Return Status
 */
#define VBE_FUNC_GET_CONTROLLER_INFO 0

/**
 * @param ES:DI Pointer to a vbe_mode_info_t
 * @param CX Mode number
 * @return AX: VBE Return Status
 */
#define VBE_FUNC_GET_MODE_INFO 1

/**
 * @param BX Desired Mode to set:
 *          D0-D8 = Mode number
 *          D9-D13 = Reserved (must be 0)
 *          D14 = 0 Use windowed frame buffer model
 *              = 1 Use linear/flat frame buffer model
 *          D15 = 0 Clear display memory
 *              = 1 Don't clear display memory
 * @return AX: VBE Return Status
 */
#define VBE_FUNC_SETMODE 2

/**
 * @return AX: VBE Return Status
 * @return BX:
 *          D0-D13 = Mode number
 *          D14 = 0 Use windowed frame buffer model
 *              = 1 Use linear/flat frame buffer model
 *          D15 = 0 Clear display memory
 *              = 1 Don't clear display memory
 */
#define VBE_FUNC_GETMODE 3
#define VBE_FUNC_SAVE_RESTORE_STATE 4
#define VBE_FUNC_DISPLAY_WINDOW_CONTROL 5
#define VBE_FUNC_SET_GET_LOGICAL_SCAN_LINE_LENGTH 6

/**
 * @param BH = 00h Reserved and must be 00h
 * @param BL = 00h Set Display Start
 *           = 01h Get Display Start
 *           = 80h Set Display Start during Vertical Retrace
 * @param CX = First Displayed Pixel In Scan Line (Set Display Start only)
 *           -> (in english) this is the index (not address nor memory offset)
 *           of the leftmost pixel to be displayed for each line
 * @param DX = First Displayed Scan Line (Set Display Start only)
 *           -> (in english) this is the line (index, not address nor memory)
 *           where the display will start
 * @return AX: VBE Return Status
 * @return BH: 00h Reserved and will be 0 (Get Display Start only)
 * @return CX: First Displayed Pixel In Scan Line (Get Display Start only)
 * @return DX: First Displayed Scan Line (Get Display Start only)
 * 
 */
#define VBE_FUNC_SET_GET_DISPLAY_START 7
#define VBE_FUNC_SET_GET_DAC_PALETTE_FORMAT 8
#define VBE_FUNC_SET_GET_PALETTE_DATA 9
#define VBE_FUNC_GET_PROTECTED_MODE_INTERFACE 10

#define VBE_LINEAR BIT(14) /**< @brief When setting/getting the VBE mode, this indicates if the screen is represented in memory as a linear buffer */

#endif /* LCOM_LAB5_VBE_H */
