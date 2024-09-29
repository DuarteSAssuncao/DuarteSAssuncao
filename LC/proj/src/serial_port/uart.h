/**
 * @file uart.h
 * @brief Macros used with the Serial Port
 * @author T17_G1
 * @date 24/05/2024
 */

#ifndef UART_H
#define UART_H

// IRQ lines
#define COM1_IRQ    4   /*!< IRQ of COM1 */
#define COM2_IRQ    3   /*!< IRQ of COM2 */

// Vectors
#define COM1_VECTOR 0x0C    /*!< Vector of COM1 */
#define COM2_VECTOR 0x0B    /*!< Vector of COM2 */

// UART (Universal Asynchronous Receiver / Transmitter) Registers
#define RBR         0x3F8   /*!< Receiver Buffer Register */
#define THR         0x3F8   /*!< Transmitter Holding Register */
#define IER         0x3F9   /*!< Interrupt Enable Register */
#define IIR         0x3FA   /*!< Interrupt Identification Register */
#define FCR         0x3FA   /*!< FIFO Control Register */
#define LCR         0x3FB   /*!< Line Control Register */
#define MCR         0x3FC   /*!< Modem Control Register */
#define LSR         0x3FD   /*!< Line Status Register */
#define MSR         0x3FE   /*!< Modem Status Register */
#define SR          0x3FF   /*!< Scratchpad Register */

// LCR (Line Control Register) Bits
#define BPC5        0x00    /*!< Five bits per char */
#define BPC6        0x01    /*!< Six bits per char */
#define BPC7        0x10    /*!< Seven bits per char */
#define BPC8        0x11    /*!< Eight bits per char */
#define SP1         0x00    /*!< One stop bit */
#define SP2         BIT(2)  /*!< Two stop bits */
#define NO_PAR      0x00                        /*!< No parity */
#define ODD_PAR     BIT(3)                      /*!< Odd parity */
#define EVEN_PAR    BIT(3) | BIT(4)             /*!< Even parity */
#define ONE_PAR     BIT(3) | BIT(5)             /*!< Always one */
#define ZERO_PAR    BIT(3) | BIT(4) | BIT(5)    /*!< Always 0 */
#define BREAK_CTRL  BIT(6)  /*!< Break control */
#define DLA         BIT(7)  /*!< Divisor Latch Access */
#define RBR_THR     0x00    /*!< RBR or THR */

// LSR (Line Status Register) Bits
#define LSR_RECEIVE BIT(0)  /*!< Receiver data */
#define OVERRUN     BIT(1)  /*!< Overrun error */
#define PARITY      BIT(2)  /*!< Parity error */
#define FRAMING     BIT(3)  /*!< Framing error */
#define BREAK_INT   BIT(4)  /*!< Break interrupt */
#define TRH_EMPTY   BIT(5)  /*!< Transmitter Holding Register Empty */
#define THR_TSR_EM  BIT(6)  /*!< Transmitter Empty Register */
#define FIFO_ERROR  BIT(7)  /*!< FIFO error */

// IER (Interrupt Enable Register) Bits
#define RDA_INT     BIT(0)  /*!< Received Data Available interrupt */
#define THRE_INT    BIT(1)  /*!< Transmitter Holding Register Empty interrupt */
#define RLS_INT     BIT(2)  /*!< Receiver Line Status interrupt */
#define MODEMS_INT  BIT(3)  /*!< MODEM Status interrupt */

// IIR (Interrupt Identification Register) Bits
#define NO_INT      BIT(0)              /*!< No interrupts */
#define RLS_INT_P   BIT(1) | BIT(2)     /*!< Receiver Line Status interrupt */
#define RDA_INT_P   BIT(2)              /*!< Received Data available */
#define CHR_TIMEOUT BIT(2) | BIT(3)     /*!< Character Timemout */
#define THRE_INT_P  BIT(1)              /*!< Transmitter Holding Register Empty */
#define MS_INT_P    0x00                /*!< MODEM Status */
#define FIFO_64B_ON BIT(5)              /*!< 64-byte FIFO enabled */
#define FCR_B0_SET  BIT(6) | BIT(7)     /*!< Bit 0 of FCR set */

// FCR (First-In-First-Out Control Register) Bits
#define ENABLE_FIFO BIT(0)              /*!< Enable both FIFOs */
#define CLR_RCVR    BIT(1)              /*!< Clear all bytes in RCVR FIFO */
#define CLR_XMIT    BIT(2)              /*!< Clear all bytes in the XMIT FIFO */
#define ENABLE_64FF BIT(5)              /*!< Enable 64 byte FIFO */
#define RCVR_1B     0x00                /*!< RCVR FIFO Trigger of one byte */
#define RCVR_4B     BIT(6)              /*!< RCVR FIFO Trigger of four bytes */
#define RCVR_8B     BIT(7)              /*!< RCVR FIFO Trigger of eight bytes */
#define RCVR_14B    BIT(6) | BIT(7)     /*!< RCVR FIFO Trigger of fourteen bytes */

// Command protocol
#define END_OF_TRANSMISSION 9   /*!< Stop connection between machines */
#define END_OF_MESSAGE      11  /*!< The current message is over */
#define CLEAR_OUTPUT        12  /*!< Clear the input buffer */
#define START_TRANSFER      13  /*!< Start the file transfer */
#define TRANSFER_ACK        14  /*!< Send another byte from a file */
#define BACKSPACE           15  /*!< Clear a character */

// Escape sequences
#define CLRSCR              "\033[1;1H\033[2J"  /*!< Clear the screen */
#define CLRLINE             "\33[2K\r"          /*!< Clear the line */

// Interrupt Handler
#define WAIT_ONE_SECOND tickdelay(micros_to_ticks(1000000))     /*!< Wait one second */

#endif
