#ifndef TIMERS_COUNTER_H
#define TIMERS_COUNTER_H

#include "macros.h"

#include <stdint.h>
#include <avr/io.h>

/**
 * @brief Initializes 16-bit timer in CTC mode.
 * The compare value will be stored in OC0A register.
 * When TCNT1 == OCR1A, TIMER1_COMPA_vect interrupt will occur.
 *
 * @param Compare value that will be stored in OC0A register.
 */
void timer1_CTC_init(uint8_t compare_val_high, uint8_t compare_val_low);

/**
 * @brief Initializes 8-bit timer in fast PWM generation mode.
 * The compare value will be stored in OC0A register.
 * When TCNT0 == MAX, TIMER0_OVF_vect interrupt will occur.
 *
 * @param Compare value that will be stored in OC0A register.
 */
void timer0_PWM_init(uint8_t compare_val);

#endif // TIMERS_COUNTER_H
