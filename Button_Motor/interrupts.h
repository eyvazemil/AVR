#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "macros.h"
#include "ADC.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

typedef enum interruptType {
    INT_INT0   = 0b00010000,
    INT_INT1   = 0b00001000,
    INT_PCINTB = 0b00000100, // PCINT0
    INT_PCINTC = 0b00000010, // PCINT1
    INT_PCINTD = 0b00000001  // PCINT2
} InterruptType;

/**
 * @brief Initializes the required interrupts.
 * In case if incorrect InterruptType or incorrect pin was chosen, no interrupt will be enabled.
 *
 * @param The interrupts can be set as an OR operation of interrupts from InterruptType enum.
 * @param Particular pin of a pin-change interrputs: value of PCMSKx register, e.g.
        0 -- 0b00000001, 3 -- 0b00001000, 7 -- 0b10000000.
 *      For INT0 and INT1 this paramter should be set to one of the values, basically EICRA register value:
 *          * 0b00000000: The low level generates an interrupt request.
 *          * 0b00000001: Any logical change generates an interrupt request.
 *          * 0b00000010: The falling edge generates an interrupt request.
 *          * 0b00000011: The rising edge generates an interrupt request.
 */
void interrupts_init(InterruptType interrupt_type, uint8_t pin);

#endif // INTERRUPTS_H
