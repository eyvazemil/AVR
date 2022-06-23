/**
 * @brief The program will receive/transmit ASCII numbers that will be converted to integers.
 * In case if USART module didn't receive anything or the received data is not a valid ASCII representation of a number, 
 *      LEDs will light up in cylon fashion.
 * When USART module receives data and it is a valid ASCII representation of a number, that number is displayed on 7 segment display.
 * PORTD[6:7] will be connected to A and B segments of the display correspondingly.
 * PORTB[0:5] will be connected to [C-G] and DP segments of the display correspondingly.
 */

#include "macros.h"
#include "USART.h"

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define SEGMENT_A 6 // from PORTD
#define SEGMENT_B 7 // from PORTD
#define SEGMENT_C 0 // from PORTB
#define SEGMENT_D 1 // from PORTB
#define SEGMENT_E 2 // from PORTB
#define SEGMENT_F 3 // from PORTB
#define SEGMENT_G 4 // from PORTB
#define SEGMENT_DP 5 // from PORTB


int main(void) {
    uint8_t data = 0, counter_cylon = 0, cylon_forward = 1;
    uint8_t flag_invalid_data = 1;

    // initialize USART
    USART_init();

    // set pins PB[0:5] to output mode
    DDRB = 0x3F;

    // set pins PD[6:7] to output mode
    DDRD = 0xC0;

    // event loop
    while(1) {
        // receive byte
        if(USART_RECEIVE_COMPLETE) {
            data = USART_receive_nonblocking();

            // check if the received number is greater than or equal to '0' ascii character
            if(data - 48 >= 0 && data - 48 <= 9) {
                if(data - 48 == 0) {
                    PORTD = (1 << SEGMENT_A) | (1 << SEGMENT_B);
                    PORTB = (1 << SEGMENT_C) | (1 << SEGMENT_D) | (1 << SEGMENT_E) | (1 << SEGMENT_F);
                } else if(data - 48 == 1) {
                    PORTD = (1 << SEGMENT_B);
                    PORTB = (1 << SEGMENT_C);
                } else if(data - 48 == 2) {
                    PORTD = (1 << SEGMENT_A) | (1 << SEGMENT_B);
                    PORTB = (1 << SEGMENT_D) | (1 << SEGMENT_E) | (1 << SEGMENT_G);
                } else if(data - 48 == 3) {
                    PORTD = (1 << SEGMENT_A) | (1 << SEGMENT_B);
                    PORTB = (1 << SEGMENT_C) | (1 << SEGMENT_D) | (1 << SEGMENT_G);
                } else if(data - 48 == 4) {
                    PORTD = (1 << SEGMENT_B);
                    PORTB = (1 << SEGMENT_C) | (1 << SEGMENT_F) | (1 << SEGMENT_G);
                } else if(data - 48 == 5) {
                    PORTD = (1 << SEGMENT_A);
                    PORTB = (1 << SEGMENT_C) | (1 << SEGMENT_D) | (1 << SEGMENT_F) | (1 << SEGMENT_G);
                } else if(data - 48 == 6) {
                    PORTD = (1 << SEGMENT_A);
                    PORTB = (1 << SEGMENT_C) | (1 << SEGMENT_D) | (1 << SEGMENT_E) | (1 << SEGMENT_F) | (1 << SEGMENT_G);
                } else if(data - 48 == 7) {
                    PORTD = (1 << SEGMENT_A) | (1 << SEGMENT_B);
                    PORTB = (1 << SEGMENT_C);
                } else if(data - 48 == 8) {
                    PORTD = (1 << SEGMENT_A) | (1 << SEGMENT_B);
                    PORTB = (1 << SEGMENT_C) | (1 << SEGMENT_D) | (1 << SEGMENT_E) | (1 << SEGMENT_F) | (1 << SEGMENT_G);
                } else if(data - 48 == 9) {
                    PORTD = (1 << SEGMENT_A) | (1 << SEGMENT_B);
                    PORTB = (1 << SEGMENT_C) | (1 << SEGMENT_F) | (1 << SEGMENT_G);
                }

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
            
            if(counter_cylon >= 7)
                cylon_forward = 0;

            if(counter_cylon < 2) {
                PORTD = (0x40 << counter_cylon);
                PORTB = 0;
            } else {
                PORTD = 0;
                PORTB = (1 << (counter_cylon - 2));
            }
            
            if(cylon_forward)
                ++counter_cylon;
            else
                --counter_cylon;

            _delay_ms(DELAY);
        }
    }

    return 0;
}
