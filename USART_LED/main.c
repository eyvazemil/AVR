#include "macros.h"
#include "USART.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT PORTB

int main(void) {
    uint8_t data = 0;

    // initialize USART
    USART_init();

    // set pins PB[0:5] to output mode
    DDRB = 0x3F;

    // event loop
    while(1) {
        // receive byte
        data = USART_receive();
        
        // check if the received number is greater than 31
        if(data - 48 >= 0 && data - 48 <= 9)
            LED_PORT = data - 48;
        else
            LED_PORT = (1 << 5);
        
        // transmit 1 meaning success
        USART_transmit(data);

        //_delay_ms(DELAY);
    }

    return 0;
}
