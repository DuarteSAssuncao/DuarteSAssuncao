/**
 * @file mouse.c
 * @brief Definition of functions related to the mouse
 * @author T17_G1
 * @date 26/05/2024
 */

#include <lcom/lcf.h>

#include "mouse.h"
#include "kbc_i8042.h"
#include <auxiliary/extra_utils.h>

#define DEBUG
#include <auxiliary/debug.h>

//! Packet with the bytes sent by the mouse
static struct packet packet_;

//! Number of bytes sent so far in the current packet
static uint8_t n_bytes = 0;

/**
 * @brief Mouse Interrupt Handler
 * @return void
 */
void (mouse_ih)() {
  if (n_bytes > 2)
    n_bytes = 0;
  
  uint8_t kbc_status;
  if (util_sys_inb(KBC_STAT_REG, &kbc_status)) return;
  if (kbc_status & KBC_ST_INVALID) return; /* invalid data */
  if (!(kbc_status & KBC_ST_AUX)) return; /* not mouse data */
  if (util_sys_inb(KBC_OUT_BUF, packet_.bytes + n_bytes)) return;
  
  switch (n_bytes) {
    case 0:
      if (!(packet_.bytes[0] & MOUSE_IDFK)) {
        DEBUG_WARNV("MOUSE_SYNC_BIT was not set on first byte! Skipping byte...\n");
        return;
      }
      packet_.y_ov = packet_.bytes[0] & MOUSE_Y_OVFL;
      packet_.x_ov = packet_.bytes[0] & MOUSE_X_OVFL;
      packet_.mb = packet_.bytes[0] & MOUSE_MIDDLE_CLICK;
      packet_.rb = packet_.bytes[0] & MOUSE_RIGHT_CLICK;
      packet_.lb = packet_.bytes[0] & MOUSE_LEFT_CLICK;
      packet_.delta_x = (packet_.bytes[0] & MOUSE_X_SIGN) ? 0xff00 : 0;
      packet_.delta_y = (packet_.bytes[0] & MOUSE_Y_SIGN) ? 0xff00 : 0;
      break;
    case 1:
      packet_.delta_x |= packet_.bytes[1];
      break;
    case 2:
      packet_.delta_y |= packet_.bytes[2];
      break;
    default:
      DEBUG_PRINTF("%s: n_bytes = %d\n", __func__, n_bytes);
      n_bytes = 0;
      return;
  }

  ++n_bytes;
}

/**
 * @brief Whether the mouse is ready to send another packet
 * @return bool : true if the three bytes have already been sent
 */
bool mouse_packet_ready() {
  return n_bytes == 3;
}

/**
 * @brief Get the current packet
 * @param mouse_packet_t *packet : pointer to mouse packet to hold the current packet values
 * @return int : 0 on success
 */
int mouse_get_packet(mouse_packet_t *packet) {
  if (!mouse_packet_ready() || packet == NULL)
    return 1;
  *packet = packet_;
  return 0;
}
