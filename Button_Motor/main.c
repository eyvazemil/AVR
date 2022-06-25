/**
 * @brief Button is connected to PD5 and LED is connected to PD4.
 */

#include "macros.h"
#include "interrupts.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUTTON_PORT_ID 7
#define BUZZER_PORT_ID 6
#define BUZZER PORTD

uint8_t flag_button_pressed = 0;

int main(void) {
    // set PD7 to input and PD6 to output modes
    DDRD = (1 << BUZZER_PORT_ID);

    // set pull up resistor on PORTD[7]
    PORTD = (1 << BUTTON_PORT_ID);

    // set interrupt on PORTD[7], which is a button
    interrupts_init(INT_PCINTD, 0b10000000);

    // event loop
    while(1) {
        
    }

    return 0;
}

ISR(PCINT2_vect) {
    if(!(PIND & (1 << BUTTON_PORT_ID))) { // button was pressed
        _delay_us(DELAY_DEBOUNCE); // debounce

        // button is still pressed and LED hasn't already been on
        if(!(PIND & (1 << BUTTON_PORT_ID)) && !flag_button_pressed) {
                BUZZER |= (1 << BUZZER_PORT_ID);
                flag_button_pressed = 1;
        } else if(flag_button_pressed) { // button simply bounced and wan't pressed
            BUZZER &= ~(1 << BUZZER_PORT_ID); // turn the LED off
            flag_button_pressed = 0;
        }
    } else if(flag_button_pressed) {
        BUZZER &= ~(1 << BUZZER_PORT_ID);
        flag_button_pressed = 0;
    }
}
