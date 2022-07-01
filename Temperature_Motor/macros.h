#ifndef MACROS_H
#define MACROS_H

#include <stdint.h>

#define DELAY 50

// LED
#define LED_PORT PORTB
#define LED PB2

// DC stepper motor
#define MOTOR_PORT PORTD
#define MOTOR_PORT_ORANGE PD4
#define MOTOR_PORT_YELLOW PD5
#define MOTOR_PORT_PINK PD6
#define MOTOR_PORT_BLUE PD7
#define MOTOR_NUM_STATES 8
#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0

// timers
#define TIMER1_SCALER 1
#define TIMER1_COUNTER 50000 // (((F_CPU / MOTOR_FREQUENCY) / MOTOR_FREQUENCY) / MOTOR_NUM_STATES)

// button
#define BUTTON_PORT PORTB
#define BUTTON_PIN PINB
#define BUTTON PB0
#define DEBOUNCE_DELAY 1000 // in microseconds

#endif // MACROS_H
