#ifndef USART_H
#define USART_H

#include "macros.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>

#define USART_BAUD_RATE (((F_CPU / 16) / BAUD) - 1)

/**
 * @brief USART initialization.
 * Receive and transmit will be enabled.
 * The number of stop bits will be 2.
 * No parity. 
 */
void USART_init();

/**
 * @brief Transmits 8 bit data via usart transmitter.
 *
 * @param 8 bit data to be transmitted.
 */
void USART_transmit(uint8_t data);

/**
 * @brief Receives 8 bit data via usart receiver.
 * Nonblocking -- not waiting for a receive complete flag.
 *
 * @return 8 bit received data.
 */
uint8_t USART_receive_nonblocking(void);

/**
 * @brief Receives 8 bit data via usart receiver.
 * Blocking -- waiting for a receive complete flag.
 *
 * @return 8 bit received data.
 */
uint8_t USART_receive_blocking(void);

#endif // USART_H
