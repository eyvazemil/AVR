/**
 * @brief Button is connected to PD5 and LED is connected to PD4.
 */

#include "macros.h"
#include "interrupts.h"
#include "timers_counters.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void) {
    // set PD3 to input, PD2 and PD7 to output modes
    DDRD = (1 << BUZZER_PORT_ID) | (1 << LED_A);

    // set PB[0:1] to output modes
    DDRB = (1 << LED_B);

    // set pull up resistor on PORTD[7]
    PORTD = (1 << BUTTON_PORT_ID);

    // set interrupt on PORTD[3], which is a button
    interrupts_init(INT_PCINTD, 0b00001000);

    // explicitly set enable the interrupts(will be needed for timer/counter module)
    sei();

    // initialize timers for LEDs
    timer1_init(255, 255);

    // event loop
    while(1) {
        
    }

    return 0;
}
