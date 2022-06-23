#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // set the pin PB0 ready for output
    DDRB = 0b00000011;
    
    // event loop
    while (1) {
        PORTB = 0b00000001; // set the value of the ouput pin PB0 to high voltage
        _delay_ms(3000); // delay
        
        PORTB = 0b00000010; // set the value of the ouput pin PB0 to low voltage
        _delay_ms(3000); // delay
    }

    return (0);
}
