#ifndef TIMERS_COUNTER_H
#define TIMERS_COUNTER_H

#include "macros.h"

#include <stdint.h>
#include <avr/io.h>

/**
 * @brief Initializes 8-bit timer in CTC mode with no PWM generation.
 * The compare value will be stored in OC0A register.
 * When TCNT0 == OC0A || TCNT0 == OC0B, an interrupt will occur on TIMER0_COMPA_vect or TIMER0_COMPB_vect accordingly.
 *
 * @param Compare value that will be stored in OC0A register.
 */
void timer0_init(uint8_t compare_val);

/**
 * @brief 16-bit counter.
 */
void timer1_init(uint8_t compare_val_high, uint8_t compare_val_low);

#endif // TIMERS_COUNTER_H
