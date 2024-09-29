/**
 * @file serial_port.c
 * @brief Implementation of functions to use with the Serial Port
 * @author T17_G1
 * @date 24/05/2024
 */

#include <lcom/lcf.h>
#include "serial_port.h"
#include "uart.h"
#include <interrupts/kbc_i8042.h>
#include <interrupts/keyboard.h>
#include <sys/stat.h>
#include "sp_util.h"

/**
 * @brief Standalone subscription function - used outside of the project
 * @param uint8_t irq_line : line to subscribe
 * @param uint8_t policies : subscription policies
 * @param uint8_t* bit : ID to subscribe the device
 * @return int : hook_id on success, 0 otherwise
 */
int (subscribe)(uint8_t irq_line, uint8_t policies, uint8_t* bit) {
    int hook_id = (int) *bit;
    if (!bit || !policies || sys_irqsetpolicy(irq_line, policies, &hook_id) != OK)
        return 0;
    return hook_id;
}

/**
 * @brief Standalone unsubscription function - used outside of the project
 * @param int* id : ID of the subscription
 * @return int : 0 on success
 */
int (unsubscribe)(int* id) {
    return !id || sys_irqrmpolicy(id);
}

/**
 * @brief A text chat between two devices (virtual machines or computers)
 * @param char* self : the name you give to yourself ('You' by default)
 * @param char* other : the name you give to the other person ('Other' by default)
 * @return void
 */
void (chat)(char* self, char* other) {
    uint8_t kbit = 1, sbit = 4;
    int serial_id = subscribe(COM1_IRQ, IRQ_REENABLE, &sbit);
    int keyboard_id = subscribe(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbit);
    
    uint32_t config = 0;
    sys_inb(IER, &config);
    sys_outb(IER, config | RDA_INT | THRE_INT | RLS_INT);
    
    sys_outb(LCR, BPC7 | SP1 | NO_PAR | RBR_THR); // Seven bits, one stop bit, no parity, RBR and THR

    sys_inb(FCR, &config);
    sys_outb(FCR, config & 0xFE); // Disable FIFOs

    int ipc_status = 0;
    message msg;

    char input[256] = {0}; // Where to keep receiving message
    char output[256] = {0}; // Where to keep sending message
    printf("\n%s > ", self);

    while (true) {
        while (driver_receive(ANY, &msg, &ipc_status));
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            if (msg.m_notify.interrupts & BIT(sbit)) {
                uint32_t in = 0;
                sys_inb(RBR, &in);
                char c = (char) in;
                switch (c) {
                    case END_OF_TRANSMISSION: { // The chat will be terminated on both sides
                        printf("%s", CLRLINE);
                        goto end;
                    }
                    case END_OF_MESSAGE: { // The other user has finished typing their current message
                        input[strlen(input)] = '\0';
                        if (strlen(input) > 1) {
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
            if (msg.m_notify.interrupts & BIT(kbit)) {
                uint32_t c = 0;
                sys_inb(KBC_OUT_BUF, &c);
                if (c & BIT(7)) // Breakcode
                    continue;
                char key = keycode_to_char(c);
                if (strlen(input) > 0)  // Prevent input increase when typing something
                    input[strlen(input) - 1] = '\0';
                switch (key) {
                    case '\n': {
                        if (!strcmp(output, "exit") || !strcmp(output, "quit")) { // Commands to quit the program
                            printf("\n");
                            sys_outb(THR, END_OF_TRANSMISSION);
                            goto end;
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
                        printf("%c", key);
                        strncat(output, &key, 1);
                        /* A character is sent each time it is appended to the message
                         * This way, there isn't a delay at the end to send the message in one go */
                        send_delay((uint8_t) key);
                        break;
                    }
                }
            }
        }
    }
    end:
    printf("\nEnd of Communication\n");
    send_delay(0x00); // Clear the Serial Port
    unsubscribe(&serial_id);
    unsubscribe(&keyboard_id);
}

/**
 * @brief Transfers a file through the serial port. Only small files advised
 * @param uint8_t stance : whether to receive (0) or to send (!= 0)
 * @param char* origin : file of origin (must exist)
 * @param char* dest : file of destination (must not exist)
 * @return void
 */
void (file_transfer)(uint8_t stance, char* origin, char* dest) {
    uint8_t sbit = 4;
    int serial_id = subscribe(COM1_IRQ, IRQ_REENABLE, &sbit);

    set_LCR(BPC8, SP1, NO_PAR, RBR_THR); // Eight bits, one stop bit, no parity, RBR and THR

    int ipc_status = 0;
    message msg;

    FILE* fp = fopen(origin, "r"); 
    if (!fp) { // Check if the origin file exists
        perror("Invalid file\n");
        goto end;
    }
    fseek(fp, 0L, SEEK_END);            // Go to the end of the file...
    unsigned long int size = ftell(fp); // ... and obtain the number of characters in it (file size)
    fclose(fp);
    unsigned long int progress = 0; // How many bytes have been transferred so far

    if (stance == 0) { // Receiver
        FILE* to = fopen(dest, "w");
        send_delay(START_TRANSFER);
        while (true) {
            while (driver_receive(ANY, &msg, &ipc_status));
            if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE && msg.m_notify.interrupts & BIT(sbit)) {
                uint32_t byte = 0;
                sys_inb(RBR, &byte);
                char chr = (char) byte;
                if (byte == END_OF_TRANSMISSION) // File is done transferring
                    break;
                fputc(chr, to); // Place char in the new file
                progress++; 
                printf("%sTransfer: %d / %d", CLRLINE, progress, size);
                tickdelay(micros_to_ticks(300)); // Prevent repeated read
            }
        }
        fclose(to);
    } else {
        uint8_t tries = 30;
        bool connection_established = false;
        while (tries > 0) { // Try to establish connection. Has thirty seconds to do so
            tickdelay(micros_to_ticks(1000000));
            uint32_t msg = 0;
            sys_inb(RBR, &msg);
            if (msg == START_TRANSFER) {
                connection_established = true;
                break;
            } else {
                tries--;
                printf("%sTrying to connect: %ds", CLRLINE, 30 - tries);
            }
        }
        if (connection_established) {
            printf("\nConnection established!\n");
            FILE* from = fopen(origin, "r");
            if (!from)
                perror("Invalid file\n");
            else {
                char c = fgetc(from); // Gets a character from the file
                while (c != EOF) {
                    send_delay((uint8_t) c);
                    progress++;
                    printf("%sTransfer: %d / %d", CLRLINE, progress, size);
                    c = fgetc(from);
                } 
                fclose(from);
            }
        } else
            printf("\nConnection not established. Exiting...\n");
        send_delay(END_OF_TRANSMISSION); // Signals the end of transfer
    }
    printf("\nFile done transfering!\n");
    end:
    unsubscribe(&serial_id);
}
