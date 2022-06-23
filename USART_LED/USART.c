#include "USART.h"

void USART_init() {
    // set BAUD rate
    UBRR0H = (USART_BAUD_RATE >> 8);
    UBRR0L = USART_BAUD_RATE;

    #if USE_2X
        UCSR0A |= (1 << U2X0);
    #else
        UCSR0A &= ~(1 << U2X0);
    #endif

    // enable receive and transmit bits in USCRnB
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // set number of data bits to 8 and set number of stop bits to 2
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (1 << USBS0);
}

void USART_transmit(uint8_t data) {
    // busy wait until the UDR0 register is empty
    while(!(UCSR0A & (1 << UDRE0)));

    // put data into UDR0 register
    UDR0 = data;
}

uint8_t USART_receive(void) {
    // busy wait until receive buffer is empty(until all the data is copied into UDR0 register)
    while(!(UCSR0A & (1 << RXC0)));

    // return the received data
    return UDR0;
}
