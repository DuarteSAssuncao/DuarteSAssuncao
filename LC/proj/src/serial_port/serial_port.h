/**
 * @file serial_port.h
 * @brief Declaraction of functions used with the Serial Port
 * @author T17_G1
 * @date 24/05/2024
 */

#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

/**
 * @brief Standalone subscription function - used outside of the project
 * @param uint8_t irq_line : line to subscribe
 * @param uint8_t policies : subscription policies
 * @param uint8_t* bit : ID to subscribe the device
 * @return int : hook_id on success, 0 otherwise
 */
int (subscribe)(uint8_t irq_line, uint8_t policies, uint8_t* bit);

/**
 * @brief Standalone unsubscription function - used outside of the project
 * @param int* id : ID of the subscription
 * @return int : 0 on success
 */
int (unsubscribe)(int* id);

/**
 * @brief A text chat between two devices (virtual machines or computers)
 * @param char* self : the name you give to yourself ('You' by default)
 * @param char* other : the name you give to the other person ('Other' by default)
 * @return void
 */
void (chat)(char* self, char* other);

/**
 * @brief Transfers a file through the serial port. Only small files advised
 * @param uint8_t stance : whether to receive (0) or to send (!= 0)
 * @param char* origin : file of origin (must exist)
 * @param char* dest : file of destination (must not exist)
 * @return void
 */
void (file_transfer)(uint8_t stance, char* origin, char* destination);

#endif
