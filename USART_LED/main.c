#include "macros.h"
#include "USART.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT PORTB

int main(void) {
    uint8_t data = 0, counter_cylon = 0, cylon_forward = 1;
    uint8_t flag_invalid_data = 1;

    // initialize USART
    USART_init();

    // set pins PB[0:5] to output mode
    DDRB = 0x3F;

    // event loop
    while(1) {
        // receive byte
        if(USART_RECEIVE_COMPLETE) {
            data = USART_receive_nonblocking();

            // check if the received number is greater than or equal to '0' ascii character
            if(data - 48 >= 0 && data - 48 <= 9) {
                LED_PORT = data - 48;
                counter_cylon = 0;
                cylon_forward = 1;
                flag_invalid_data = 0;
            } else
                flag_invalid_data = 1;

            // transmit the received byte
            USART_transmit(data);
        } else if(flag_invalid_data) {
            if(counter_cylon == 0)
                cylon_forward = 1;
            
            if(counter_cylon >= 5)
                cylon_forward = 0;

            LED_PORT = (1 << counter_cylon);
            
            if(cylon_forward)
                ++counter_cylon;
            else
                --counter_cylon;

            _delay_ms(DELAY);
        }
    }

    return 0;
}
