#include <lcom/lcf.h>
#include "sp_util.h"
#include "uart.h"

/**
 * @brief Sets the configuration of the LCR (Line Control Register)
 * @param uint8_t bits_per_char : how many bits should be sent at each time (5 - 8)
 * @param uint8_t stop_bits : how many stops bits should each byte have (1 - 2)
 * @param uint8_t parity : how should the parity be treated
 * @param uint8_t dlab : divisor latch
 * @return int : OK if successful, something else otherwise
 */
int (set_LCR)(uint8_t bits_per_char, uint8_t stop_bits, uint8_t parity, uint8_t dlab) {
    return sys_outb(LCR, (uint32_t) (bits_per_char | stop_bits | parity | dlab));
}

/**
 * @brief Send a byte through the Serial Port with a 0.4ms delay
 * @brief As subscribing with IRQ_EXCLUSIVE prevents interruptions, this circumvents it
 * @param uint8_t char : byte to send (representing a character)
 * @return void
 */
void (send_delay)(uint8_t chr) {
    sys_outb(THR, chr);
    tickdelay(micros_to_ticks(400));
}
