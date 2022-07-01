#include "timers_counters.h"

void timer1_CTC_init(uint8_t compare_val_high, uint8_t compare_val_low) {
    // set the compare value
    OCR1AH = compare_val_high;
    OCR1AL = compare_val_low;

    // set mask and control registers
    TIMSK1 = (1 << OCIE1A);
    TCCR1A = (1 << WGM11);
    TCCR1B = (1 << CS11) | (1 << CS10); // counting starts from here, as the clock is set with prescaler
}

void timer0_PWM_init(uint8_t compare_val) {
    // set the compare values
    OCR0A = compare_val;

    // set mask and control registers
    TIMSK0 = (1 << TOIE0);
    TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00); // compare value in OCR0A, CTC mode
    TCCR0B = (1 << CS02) | (1 << CS00); // counting starts from here, as the clock is set with prescaler
}
