/**
 * @brief Button is connected to PD5 and LED is connected to PD4.
 */

#include "macros.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PORT_ID 5
#define LED_PORT_ID 4
#define LED PORTD


int main(void) {
    uint8_t flag_button_pressed = 0;

    // set PD5 to input and PD4 to output modes
    DDRD = (1 << LED_PORT_ID);

    // set pull up resistor on PORTD[5]
    PORTD = (1 << BUTTON_PORT_ID);

    // event loop
    while(1) {
        if(!(PIND & (1 << BUTTON_PORT_ID))) { // button was pressed
            _delay_us(DELAY_DEBOUNCE); // debounce

            // button is still pressed and LED hasn't already been on
            if(!(PIND & (1 << BUTTON_PORT_ID)) && !flag_button_pressed) {
                    LED |= (1 << LED_PORT_ID);
                    flag_button_pressed = 1;
            } else if(flag_button_pressed) { // button simply bounced and wan't pressed
                LED &= ~(1 << LED_PORT_ID); // turn the LED off
                flag_button_pressed = 0;
            }
        } else if(flag_button_pressed) {
            LED &= ~(1 << LED_PORT_ID);
            flag_button_pressed = 0;
        }
    }

    return 0;
}
