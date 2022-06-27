#include "timers_counters.h"

void timer0_init(uint8_t compare_val) {
    // set the compare values
    OCR0A = compare_val;

    // set mask and control registers
    TIMSK0 = (1 << OCIE0A); // enable interrupt for TCNT0 == OCR0A
    TCCR0A = (1 << COM0A0) | (1 << WGM01); // compare value in OCR0A, CTC mode
    TCCR0B = (1 << CS02) | (1 << CS00); // counting starts from here, as the clock is set with prescaler
}

void timer1_init(uint8_t compare_val_high, uint8_t compare_val_low) {
    // set the compare values
    OCR1AH = compare_val_high;
    OCR1AL = compare_val_low;

    // set mask and control registers
    TIMSK1 = (1 << OCIE1A); // enable interrupt for TCNT0 == OCR0A
    TCCR1A = (1 << COM0A1) | (1 << WGM11); // compare value in OCR0A, CTC mode
    TCCR1B = (1 << CS12) | (1 << CS10); // counting starts from here, as the clock is set with prescaler
}
