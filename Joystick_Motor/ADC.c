#include "ADC.h"

void ADC_init(uint8_t analog_pins) {
    //if(analog_pins > PC5)
    //    return;

    // set ADMUX register
    ADMUX = (1 << REFS0) | analog_pins; // AVCC voltage with analog_pins value for MUX[3:0]

    // set ADCSRA register interrupt and clock frequency prescaler bits to 64
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // set DIDR0 register to disable all other pins that are not used
    DIDR0 = (1 << ADC0D);

    // make the first conversion
    ADC_start_conversion();
}

void ADC_start_conversion(void) {
    ADCSRA |= (1 << ADSC);
}
