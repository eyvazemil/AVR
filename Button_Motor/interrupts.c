#include "interrupts.h"
#include "ADC.h"
#include "macros.h"

// should be volatile, so that compiler doesn't optimize it into a constant
static volatile uint8_t flag_button_pressed = 0;
static volatile uint8_t flag_LED_set = 0;
static volatile uint8_t flag_motor_MAX_pulse = 1;

void interrupts_init(InterruptType interrupt_type, uint8_t pin) {
    uint8_t flag_valid_interrupt = 0;

    // get the interrupts that should be enabled
    if(interrupt_type & (1 << 4) && pin <= 3) { // INT0 with valid trigger value
        EICRA |= pin; // External Interrupt Control Register A
        EIMSK |= (1 << INT0); // External Interrupt Mask Register
        flag_valid_interrupt = 1;
    }

    if(interrupt_type & (1 << 3) && pin <= 3) { // INT1 with valid trigger value
        EICRA |= (pin << ISC10); // external interrupt control register A
        EIMSK |= (1 << INT1); // External Interrupt Mask Register
        flag_valid_interrupt = 1;
    }

    if(interrupt_type & (1 << 2)) { // PCINT0
        PCICR |= (1 << PCIE0); // Pin Change Interrupt Control Register
        PCMSK0 = pin; // Pin Change Mask Register 0
        flag_valid_interrupt = 1;
    }

    if(interrupt_type & (1 << 1)) { // PCINT1
        PCICR |= (1 << PCIE1); // Pin Change Interrupt Control Register
        PCMSK1 = pin; // Pin Change Mask Register 1
        flag_valid_interrupt = 1;
    }

    if(interrupt_type & (1 << 0)) { // PCINT2
        PCICR |= (1 << PCIE2); // Pin Change Interrupt Control Register
        PCMSK2 = pin; // Pin Change Mask Register 2
        flag_valid_interrupt = 1;
    }

    // if interrupts passed were valid, set global interrupt enable
    if(flag_valid_interrupt)
        sei();
}

ISR(PCINT2_vect) {
    if(!(PIND & (1 << BUTTON_PORT_ID))) { // button was pressed
        _delay_us(DELAY_DEBOUNCE); // debounce

        // button is still pressed and LED hasn't already been on
        if(!(PIND & (1 << BUTTON_PORT_ID)) && !flag_button_pressed) {
                BUZZER |= (1 << BUZZER_PORT_ID);
                flag_button_pressed = 1;
        } else if(flag_button_pressed) { // button simply bounced and wan't pressed
            BUZZER &= ~(1 << BUZZER_PORT_ID); // turn the LED off
            flag_button_pressed = 0;
        }
    } else if(flag_button_pressed) {
        BUZZER &= ~(1 << BUZZER_PORT_ID);
        flag_button_pressed = 0;
    }
}

ISR(TIMER1_COMPA_vect) {
    if(!flag_LED_set) {
        LED_A_PORT |= (1 << LED_A);
        LED_B_PORT &= ~(1 << LED_B);
        flag_LED_set = 1;
    } else if(flag_LED_set) {
        LED_A_PORT &= ~(1 << LED_A);
        LED_B_PORT |= (1 << LED_B);
        flag_LED_set = 0;
    }
}

ISR(TIMER1_OVF_vect) {
    /*if(motor_position >= MOTOR_PULSE_MAX)
        flag_motor_MAX_pulse = 1;
    else if(motor_position <= MOTOR_PULSE_MIN)
        flag_motor_MAX_pulse = 0;

    if(flag_motor_MAX_pulse)
        motor_position -= 100;
    else
        motor_position += 100;

    OCR1A = motor_position;*/
}

ISR(ADC_vect) { // ADC conversion done
    uint8_t ADC_lower = ADCL; // lower bits of ADC conversion result
    uint8_t ADC_higher = ADCH; // higher bits of ADC conversion result

    // calculate the scaler between SERVO motor rotations and joystick values
    uint8_t scaler = (MOTOR_PULSE_MAX - MOTOR_PULSE_MIN) / (JOYSTICK_MAX - JOYSTICK_MIN) + 1;

    // set the rotation value of SERVO motor
    OCR1A = ((unsigned int) (ADC_higher << 8) | ADC_lower) * scaler;

    // make another conversion
    ADC_start_conversion();
}
