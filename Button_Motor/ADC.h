#ifndef ADC_H
#define ADC_H

#include "macros.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/**
 * @brief Initializes ADC module.
 * Conversion is done in single conversion mode with interrupt on ADC_vect when conversion is done.
 *
 * @param Pins where analog input should be coming in.
 */
void ADC_init(uint8_t analog_pins);

/**
 * @brief Sets ADSC bit to one in ADCSRA register.
 */
void ADC_start_conversion(void);

#endif // ADC_H
