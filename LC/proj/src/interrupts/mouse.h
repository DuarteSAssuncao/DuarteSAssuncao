/**
 * @file mouse.h
 * @brief Declaration of functions related with mouse packets
 * @author T17_G1
 * @date 26/05/2024
 */

#ifndef LCOM_PROJ_MOUSE_H
#define LCOM_PROJ_MOUSE_H

#include <lcom/lab4.h>

typedef struct packet mouse_packet_t;

/**
 * @brief Whether the mouse is ready to send another packet
 * @return bool : true if the three bytes have already been sent
 */
bool mouse_packet_ready();

/**
 * @brief Get the current packet
 * @param mouse_packet_t *packet : pointer to mouse packet to hold the current packet values
 * @return int : 0 on success
 */
int mouse_get_packet(mouse_packet_t *packet);

#endif /* LCOM_PROJ_MOUSE_H */
