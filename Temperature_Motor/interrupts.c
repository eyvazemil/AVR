#include "interrupts.h"

// array with the ports of motor states
static volatile uint8_t arr_motor_states_ports[8] = {
    0xFF & ~(1 << MOTOR_PORT_ORANGE),
    0xFF & ~(1 << MOTOR_PORT_ORANGE) & ~(1 << MOTOR_PORT_YELLOW),
    0xFF & ~(1 << MOTOR_PORT_YELLOW),
    0xFF & ~(1 << MOTOR_PORT_YELLOW) & ~(1 << MOTOR_PORT_PINK),
    0xFF & ~(1 << MOTOR_PORT_PINK),
    0xFF & ~(1 << MOTOR_PORT_PINK) & ~(1 << MOTOR_PORT_BLUE),
    0xFF & ~(1 << MOTOR_PORT_BLUE),
    0xFF & ~(1 << MOTOR_PORT_BLUE) & ~(1 << MOTOR_PORT_ORANGE)
};

// index of the current state of the DC stepper motor
static volatile uint8_t motor_state_id = 0;

// direction of the motor
static volatile uint8_t motor_direction = CLOCKWISE;

// scaler for 16-bit timer
static volatile uint8_t timer1_scaler = 0;

ISR(TIMER1_COMPA_vect) {
    if(timer1_scaler == TIMER1_SCALER) {
        MOTOR_PORT = arr_motor_states_ports[motor_state_id];

        if(motor_direction == COUNTERCLOCKWISE)
            ++motor_state_id;
        else
            --motor_state_id;

        // stay in the range of 8 states
        motor_state_id &= 0b00000111;

        // reset the scaler
        timer1_scaler = 0;
    } else
        ++timer1_scaler;
}

ISR(PCINT0_vect) {
    if(!(BUTTON_PIN & (1 << BUTTON))) { // grounded => pressed
        _delay_us(DEBOUNCE_DELAY); // debounce

        if(!(BUTTON_PIN & (1 << BUTTON))) // still pressed => it was a real press
            motor_direction ^= 0b00000001;
    }

    LED_PORT ^= (1 << LED);
}

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
