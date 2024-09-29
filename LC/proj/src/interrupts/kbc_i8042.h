/**
 * @file kbc_i8042.h
 * @brief Declaration of functions used with the KBC
 * @author T17_G1
 * @date 24/05/2024
 */

#ifndef LCOM_PROJ_I8042_H
#define LCOM_PROJ_I8042_H

#include <lcom/lcf.h>

/**
 * @defgroup i8042 i8042
 * 
 * Macros for programming with the i8042 Keyboard/Mouse Controller.
 */

#define KEYBOARD_IRQ 1  /*!< @brief Keyboard Controller IRQ line */
#define MOUSE_IRQ 12    /*!< @brief Mouse IRQ line */


// KBC PORTS
#define KBC_OUT_BUF 0x60        /*!< @brief Port for keyboard incoming scancodes */
#define KBC_STAT_REG 0x64       /*!< @brief Port for keyboard status register */
#define KBC_IN_CMD KBC_STAT_REG /*!< @brief Port for sending KBC commands */
#define KBC_IN_ARGS KBC_OUT_BUF /*!< @brief Port for sending KBC command arguments */

// STATUS REGISTER
#define KBC_ST_PARITY_ERR  BIT(7) /*!< @brief (KBC status register flag) Parity error - invalid data */
#define KBC_ST_TIMEOUT     BIT(6) /*!< @brief (KBC status register flag) Timeout error - invalid data */
#define KBC_ST_AUX         BIT(5) /*!< @brief (KBC status register flag) Mouse data */
#define KBC_ST_INH         BIT(4) /*!< @brief (KBC status register flag) Inhibit flag: 0 if keyboard is inhibited */
#define KBC_ST_A2          BIT(3) /*!< @brief (KBC status register flag) A2 input line */
#define KBC_ST_SYS         BIT(2) /*!< @brief (KBC status register flag) System flag */
#define KBC_ST_IBF         BIT(1) /*!< @brief (KBC status register flag) Input buffer full - don't write to it */
#define KBC_ST_OBF         BIT(0) /*!< @brief (KBC status register flag) Output buffer full - ready to read */

#define KBC_ST_INVALID (KBC_ST_PARITY_ERR | KBC_ST_TIMEOUT) /*!< @brief If true, don't read from the KBC_OUT_BUF */


// KEYBOARD COMMANDS
#define KBC_CMD_READ 0x20   /*!< @brief Read the current Command Byte */
#define KBC_CMD_WRITE 0x60  /*!< @brief Write a new Command Byte */
#define KBC_CHECK 0xAA      /*!< @brief Returns KBC_OK if ok, KBC_ERR on error */
#define KBD_CHECK 0xAB      /*!< @brief Returns KBD_OK if ok */
#define KBD_DISABLE 0xAD    /*!< @brief Disable KBD */
#define KBD_ENABLE 0xAE     /*!< @brief Enable KBD */

// MOUSE COMMANDS
#define KBC_MOUSE_WRITE 0xD4    /*!< @brief Informs the KBC that we will send a command to the mouse (passed in KBC_IN_ARGS) */
#define KBC_MOUSE_DISABLE 0xA7  /*!< @brief Disable the mouse through the KBC */
#define KBC_MOUSE_ENABLE 0xA8   /*!< @brief Enable the mouse through the KBC */
#define KBC_MOUSE_CHECK 0xA9    /*!< @brief Returns KBC_MOUSE_OK if ok */

// KBC RETURN VALUES
#define KBC_OK 0x55         /*!< @brief Operation successfully completed */
#define KBC_ERR 0xFC        /*!< @brief There was an error with the KBC */
#define KBD_OK 0            /*!< @brief The KBD is OK */
#define KBC_MOUSE_OK 0      /*!< @brief The mouse is OK */


// KBC COMMAND BYTE
#define KBC_CMD_DIS2 BIT(5)     /*!< @brief Disable mouse interface */
#define KBC_CMD_DIS BIT(4)      /*!< @brief Disable keyboard interface */
#define KBC_CMD_INT2 BIT(1)     /*!< @brief Enable interrupts on OBF from mouse */
#define KBC_CMD_INT BIT(0)      /*!< @brief Enable interrupts on OBF from keyboard */
#define KBC_OK 0x55             /*!< @brief The KBC is OK */
#define KBC_ERR 0xFC            /*!< @brief There is an error in the KBC */
#define KEYBOARD_OK 0           /*!< @brief The keyboard is OK */
#define KBC_MOUSE_OK 0          /*!< @brief The mouse is OK */

// KBC MISC
#define KBC_DELAY_MICROSECONDS 20000    /*!< @brief Delay of 20ms */
#define KBC_ATTEMPTS 10                 /*!< @brief How many times to loop before failure */

/**
 * @brief Write a command to the KBC
 * @param uint8_t byte : byte to write
 * @return int : 0 on success, non-zero otherwise
 */
int (kbc_write_cmd)(uint8_t byte);

/**
 * @brief Write an argument to the KBC
 * @param uint8_t byte : byte to write
 * @return int : 0 on success, non-zero otherwise
 */
int (kbc_write_arg)(uint8_t byte);


// MOUSE COMMANDS
#define MOUSE_RESET 0xFF                    /*!< @brief Reset the mouse */
#define MOUSE_RESEND 0xFE                   /*!< @brief Resend previous byte/packet in case of serial communications errors */
#define MOUSE_SETDEFAULT 0xF6               /*!< @brief Set default values */
#define MOUSE_DISABLE_DATA_REPORTING 0xF5   /*!< @brief Disable data reporting on the mouse */
#define MOUSE_ENABLE_DATA_REPORTING 0xF4    /*!< @brief Enable data reporting on the mouse */
#define MOUSE_SET_SAMPLING_RATE 0xF3        /*!< @brief Sets state sampling rate */
#define MOUSE_SET_REMOTE_MODE 0xF0          /*!< @brief Changes the mode to remote */
#define MOUSE_READ_PACKET 0xEB              /*!< @brief Send a data packet request */
#define MOUSE_SET_STREAM_MODE 0xEA          /*!< @brief Changes the mode to stream */
#define MOUSE_GET_CONFIG 0xE9               /*!< @brief Signal to get the current configuration */
#define MOUSE_SET_RESOLUTION 0xE8           /*!< @brief Sets the resolution of the mouse */
#define MOUSE_SET_SCALING_2_1 0xE7          /*!< @brief Acceleration mode */
#define MOUSE_SET_SCALING_1_1 0xE6          /*!< @brief Linear mode */

// MOUSE RESPONSE
#define MOUSE_ACK 0xFA                      /*!< @brief Acknowledgement byte sent by the mouse */

// MOUSE FIRST BYTE BITS
#define MOUSE_Y_OVFL BIT(7)         /*!< @brief If the x-displacement cannot be interpreted with 9 bits */
#define MOUSE_X_OVFL BIT(6)         /*!< @brief If the y-displacement cannot be interpreted with 9 bits */
#define MOUSE_Y_SIGN BIT(5)         /*!< @brief The most significant bit of the 9-bit value of deltaY */
#define MOUSE_X_SIGN BIT(4)         /*!< @brief The most significant bit of the 9-bit value of deltaX */
#define MOUSE_IDFK BIT(3)           /*!< @brief On the first byte, this bit is always one */
#define MOUSE_MIDDLE_CLICK BIT(2)   /*!< @brief 1 if middle click */
#define MOUSE_RIGHT_CLICK BIT(1)    /*!< @brief 1 if right click */
#define MOUSE_LEFT_CLICK BIT(0)     /*!< @brief 1 if left click */

/**
 * @brief Write a command to the mouse through the KBC
 * @param uint8_t byte : byte to write
 * @return int : 0 on success, non-zero otherwise
 */
int (kbc_mouse_write)(uint8_t byte);

#endif /* LCOM_PROJ_I8042_H */
