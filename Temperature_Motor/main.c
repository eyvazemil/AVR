#include "macros.h"
#include "timers_counters.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void) {

    // set DDRD register for motor
    DDRD = (1 << MOTOR_PORT_ORANGE) | (1 << MOTOR_PORT_YELLOW) |
        (1 << MOTOR_PORT_PINK) | (1 << MOTOR_PORT_BLUE);

    // enable all interrupts
    sei();

    // initialize a 16-bit timer for changing states of DC stepper motor states
    timer1_CTC_init((uint8_t) (TIMER1_COUNTER >> 8), (uint8_t) TIMER1_COUNTER);

    // event loop
    while(1) {

    }

    return 0;
}