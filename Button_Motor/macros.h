#ifndef MACROS_H
#define MACROS_H

#define DELAY 500
#define USART_RECEIVE_COMPLETE ((UCSR0A & (1 << RXC0)) != 0)
#define DELAY_DEBOUNCE 1000
#define BUTTON_PORT_ID PD3
#define BUZZER_PORT_ID PD2
#define MOTOR_PORT_ID PB1
#define BUZZER PORTD
#define LED_A_PORT PORTD
#define LED_B_PORT PORTB
#define LED_A PD7
#define LED_B PB0

// SERVO motor
#define MOTOR_PULSES 20000
#define MOTOR_PULSE_MIN 1000 // 5% of 20000(16-bit timer)
#define MOTOR_PULSE_MAX 4000 // 10% of 20000(16-bit timer)
#define MOTOR_PULSE_MID ((MOTOR_PULSE_MAX - MOTOR_PULSE_MIN) / 2 + MOTOR_PULSE_MIN) // 7.5% of 20000(16-bit timer)

#endif // MACROS_H
