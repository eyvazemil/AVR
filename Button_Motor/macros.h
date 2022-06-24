#ifndef MACROS_H
#define MACROS_H

#define DELAY 500
#define USART_RECEIVE_COMPLETE ((UCSR0A & (1 << RXC0)) != 0)
#define DELAY_DEBOUNCE 1000

#endif // MACROS_H
