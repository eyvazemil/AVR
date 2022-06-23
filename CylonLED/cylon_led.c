#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT PORTB
#define DELAY 2500

int main(void) {
    uint8_t counter = 1;

    // set the PB[0:7] pins to output mode
    DDRB = 0xFF;

    // set the initial value of PB0 to 1
    LED_PORT = 0x01;
    _delay_ms(DELAY);

    while(1) {
        while(counter < 6) {
            LED_PORT <<= 1;
            _delay_ms(DELAY);
            ++counter;
        }

        while(counter > 1) {
            LED_PORT >>= 1;
            _delay_ms(DELAY);
            --counter;
        }
    }

    return 0;
}
