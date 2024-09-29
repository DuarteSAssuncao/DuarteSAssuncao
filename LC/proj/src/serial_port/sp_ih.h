/**
 * @file sp_ih.h
 * @brief Declaration of functions to be compatible with the project
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef SP_IH_H
#define SP_IH_H

#include <stdio.h>
#include "serial_port.h"

#define SLEEP       0   /*!< The serial port isn't being used at the moment */
#define CHAT        1   /*!< There is a chat between two machines */
#define SENDER      2   /*!< This machine is sending a file to another machine */
#define RECEIVER    3   /*!< This machine is receiving a file from another machine */

/*
 * 1. You need to set the stance (purpose of the serial port) before doing anything else. You can use SLEEP (default), CHAT, SENDER or RECEIVER with the function set_stance(uint8_t stance)
 * 2. If you want to send a file, use set_destination_file(FILE* file) first. Make sure it is valid (you opened the file successfully - if not, the function does nothing and returns 1)
 * 3. When calling serial_ih(), it in turn calls chat_ih() (if in CHAT) or receiver_ih() (if in RECEIVER). If it is SLEEP or SENDER it does nothing
 * 4. In order to send a character through the serial port, use send_char_sp(char c) - I don't know how to get a character from the keyboard
 * 5. I also don't know how to print the characters in the window, so (later) the commented printf() should be replaced with the corresponding draw function
 * 6. clean_sp() cleans all the variables, including the stance, so you'll need to set it again
 * 7. It still uses delays - it's better to leave this way instead of trying to change to registers reads with IRQ_EXCLUSIVE and wasting a lot of time
 */

/**
 * @brief General interrupt handler. Calls other functions
 * @return void
 */
void (serial_ih)();

/**
 * @brief Handles interruptions while in the chat
 * @param char c : character received from the Serial Port
 * @return void
 */
void (chat_ih)(char c);

/**
 * @brief If in CHAT, sends a character through the Serial Port
 * @return int : 0 on success
 */
int (send_char_sp)(char c);

/**
 * @brief Handles interruptions as a receiver
 * @param uint32_t byte : byte read from the serial port (in serial_ih)
 * @return void
 */
void (receiver_ih)(uint32_t byte);

/**
 * @brief Sends a file through the Serial Port. Sends one byte after receiving one interrupt (to not block Rakoon)
 * @param FILE* file : file to copy from
 * @return void
 */
int (sender_ih)(char c);

/**
 * @brief What will the serial port be used to
 * @param uint8_t stance : purpose of the Serial Port
 * @return void
 */
int (set_stance)(uint8_t stance);

/**
 * @brief What will be the destination file
 * @param FILE* file : the destination file
 * @return int : 0 on success
 */
int (set_destination_file)(FILE* file);

/**
 * @brief What is the origin file
 * @param FILE* file : the origin file
 * @return int : 0 on success
 */
int (set_origin_file)(FILE* file);

/**
 * @brief Cleans up all the static global values and sends 0x00 to the Serial Port
 * @return void
 */
void (clean_sp)();

/**
 * @brief Get the current stance
 * @return uint8_t : the current stance
 */
uint8_t (get_stance)();

bool is_locked();

#endif
