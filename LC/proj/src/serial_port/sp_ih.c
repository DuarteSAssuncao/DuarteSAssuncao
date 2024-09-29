/**
 * @file sp_ih.c
 * @brief Definition of functions related to the serial port to be compatible with the project
 * @author T17_G1
 * @date 29/05/2024
 */

#include <lcom/lcf.h>
#include "sp_ih.h"
#include "uart.h"
#include <stdbool.h>
#include <stdlib.h>
#include "sp_util.h"

#define DEBUG
#define DEBUG2
#include <auxiliary/debug.h>

//! Receiving input from the other machine
static char input[256] = {0};

//! What the user is typing
static char output[256] = {0};

//! Whether the stance is unchangeable
static bool locked = false;

//! What the serial port is being used for
static uint8_t stance = SLEEP;

//! File to copy from
static FILE* from = NULL;

//! File to copy to
static FILE* to = NULL;

//! How much has the file been transfered
static size_t size = 0;

//! How much has the file been transfered
static size_t progress = 0;

/**
 * @brief General interrupt handler. Calls other functions
 * @return void
 */
void (serial_ih)() {
    uint32_t c = 0;
    sys_inb(RBR, &c);
    if (stance == CHAT) {
        chat_ih((char) c);
        locked = true;
    } else {
        if (c == TRANSFER_ACK && !locked) {
            set_stance(SENDER);
            locked = true;
        }
        if (stance == SENDER && c == TRANSFER_ACK)
            sender_ih((char) c);
        else if (stance == RECEIVER)
            receiver_ih((char) c);
    }
}

/**
 * @brief Handles interruptions while in the chat
 * @param char c : character received from the Serial Port
 * @return void
 */
void (chat_ih)(char c) {
    char* self = "2B", *other = "9S";
    switch (c) {
        case END_OF_TRANSMISSION: { // The chat will be terminated on both sides
            printf("%s", CLRLINE);
            clean_sp();
            return;
        }
        case END_OF_MESSAGE: { // The other user has finished typing their current message
            input[strlen(input)] = '\0';
            if (strlen(input) >= 1) {
                printf("%s%s > %s", CLRLINE, other, input); // Clear current line and display the message
                if (input[strlen(input)-1] != '\n')
                    printf("\n");

                printf("%s > %s", self, output); // Display the message you were typing
            }
            memset(input, 0, sizeof(input)); // Reset the receiving message
            break;
        }
        case CLEAR_OUTPUT: { // Reset the receiving message (the other user typed 'clear')
            memset(input, 0, sizeof(input));
            break;
        }
        case BACKSPACE: { // Remove the last character if not null
            if (strlen(input) > 0)
                input[strlen(input) - 1] = '\0';
            break;
        }
        default: { // Append the received character to the message
            strncat(input, &c, 1);
            break;
        }
    }
    tickdelay(micros_to_ticks(300)); // Prevent repeated read
}

/**
 * @brief If in CHAT, sends a character through the Serial Port
 * @return int : 0 on success
 */
int (send_char_sp)(char c) {
    char* self = "2B";
    if (stance == CHAT) {
        switch (c) {
            case '\n': {
                if (!strcmp(output, "exit") || !strcmp(output, "quit")) { // Commands to quit the program
                    printf("\n");
                    sys_outb(THR, END_OF_TRANSMISSION);
                    clean_sp();
                    return 0;
                } else if (!strcmp(output, "clear")) { // Command to clear the screen (just like in Unix)
                    printf(CLRSCR);
                    send_delay(CLEAR_OUTPUT);
                    memset(output, 0, sizeof(output));
                    printf("%s > ", self);
                    break;
                } else { // Tell the other user you are done typing
                    send_delay(END_OF_MESSAGE);
                    memset(output, 0, sizeof(output));
                    printf("\n%s > ", self);
                }
                break;
            }
            case '\b': { // Tell the other user to clear a character if not null
                if (strlen(output) > 0) {
                    printf("\b \b"); // Go back one character, replace it with a space, then go backwards again
                    output[strlen(output) - 1] = '\0';
                }
                sys_outb(THR, BACKSPACE);
                break;
            }
            default: { // Append the character to your message
                printf("%c", c);
                strncat(output, &c, 1);
                /* A character is sent each time it is appended to the message
                 * This way, there isn't a delay at the end to send the message in one go */
                send_delay((uint8_t) c);
                break;
            }
        }
    }
    return 1;
}


/**
 * @brief Handles interruptions as a receiver
 * @param uint32_t byte : byte read from the serial port (in serial_ih)
 * @return void
 */
void (receiver_ih)(uint32_t byte) {
    DEBUG_PRINTF2("function start\n");
    if (to) {
        char chr = (char) byte;
        if (byte == END_OF_TRANSMISSION) { // File is done transferring
            DEBUG_SUCCESSV("File received successfully!\n");
            clean_sp();
            return;
        } else if (byte == TRANSFER_ACK) {
            DEBUG_PRINTF2("Waiting for next character...\n");
            return;
        }
        fputc(chr, to); // Place char in the new file
        progress++; 
        //DEBUG_PRINTF2("%d (%c)\n", (int) chr, chr);
        DEBUG_PRINTF2("%sTransfer: %d / %d", CLRLINE, progress, size);
        send_delay(TRANSFER_ACK);
    }
}

/**
 * @brief Sends a file through the Serial Port. Sends one byte after receiving one interrupt (to not block Rakoon)
 * @param FILE* file : file to copy from
 * @return void
 */
int (sender_ih)(char c) {
    if (from && c == TRANSFER_ACK) {
        char chr = fgetc(from); // Gets a character from the file
        if (chr != EOF) {
            send_delay((uint8_t) chr);
            progress++;
            printf("%sTransfer: %d / %d", CLRLINE, progress, size);
        } else {
            send_delay(END_OF_TRANSMISSION);
            // Something to print
            clean_sp();
        }
        return 0;
    }
    return 1;
}

/**
 * @brief What will the serial port be used to. Can't be changed if it is locked
 * @param uint8_t stance : purpose of the Serial Port
 * @return int : 0 on success
 */
int (set_stance)(uint8_t st) {
    DEBUG_PRINTF2("function start\n");
    if (!locked && st <= 3) {
        stance = st;
        locked = true;
        set_LCR(BPC8, SP1, NO_PAR, RBR_THR); // Eight bits, one stop bit, no parity, RBR and THR
        if (from) {
            fseek(from, 0L, SEEK_END);            // Go to the end of the file...
            size = ftell(from); // ... and obtain the number of characters in it (file size)
            progress = 0;
            fseek(from, 0L, SEEK_SET); 
        }
        if (stance == RECEIVER)
            send_delay(TRANSFER_ACK);
        else if (stance == CHAT) {
            memset(output, 0, sizeof(output));
            memset(input, 0, sizeof(input));
            printf("\n\n2B > ");
        }
        return 0;
    }
    return 1;
}

/**
 * @brief What will be the destination file
 * @param FILE* file : the destination file
 * @return int : 0 on success
 */
int (set_destination_file)(FILE* file) {
    if (file) {
        to = file;
        return 0;
    }
    return 1;
}

/**
 * @brief What is the origin file
 * @param FILE* file : the origin file
 * @return int : 0 on success
 */
int (set_origin_file)(FILE* file) {
    if (file) {
        from = file;
        return 0;
    }
    return 1;
}

/**
 * @brief Cleans up all the static global values
 * @return void
 */
void (clean_sp)() {
    printf("\nCleaning up\n");
    if (from)
        fclose(from);
    from = NULL;
    if (to)
        fclose(to);
    to = NULL;
    size = 0;
    progress = 0;
    locked = false;
    stance = SLEEP;
    memset(output, 0, sizeof(output));
    memset(input, 0, sizeof(input));
}

/**
 * @brief Get the current stance
 * @return uint8_t : the current stance
 */
uint8_t (get_stance)() {
    return stance;
}

bool is_locked() {
    return locked;
}
