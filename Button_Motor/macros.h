#ifndef MACROS_H
#define MACROS_H

#define DELAY 500
#define USART_RECEIVE_COMPLETE ((UCSR0A & (1 << RXC0)) != 0)
#define DELAY_DEBOUNCE 1000
#define BUTTON_PORT_ID 3 // in PORTD
#define BUZZER_PORT_ID 2 // in PORTD
#define BUZZER PORTD
#define LED_A_PORT PORTD
#define LED_B_PORT PORTB
#define LED_A 7 // in PORTD
#define LED_B 0 // in PORTB

#endif // MACROS_H
