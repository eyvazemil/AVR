#include "interrupts.h"

// states of the DC stepper motor
typedef enum motor_states {
    MOTOR_STATE_ORANGE,
    MOTOR_STATE_ORANGE_YELLOW,
    MOTOR_STATE_YELLOW,
    MOTOR_STATE_YELLOW_PINK,
    MOTOR_STATE_PINK,
    MOTOR_STATE_PINK_BLUE,
    MOTOR_STATE_BLUE,
    MOTOR_STATE_BLUE_ORANGE
} MotorStates;

// stores the current state of the DC stepper motor
static volatile uint8_t motor_state = MOTOR_STATE_ORANGE;

// scaler for 16-bit timer
static volatile uint8_t timer1_scaler = 0;

ISR(TIMER1_COMPA_vect) {
    if(timer1_scaler == TIMER1_SCALER) {
        if(motor_state == MOTOR_STATE_ORANGE) {
            MOTOR_PORT = 0xFF & ~(1 << MOTOR_PORT_ORANGE);
            motor_state = MOTOR_STATE_ORANGE_YELLOW;
        } else if(motor_state == MOTOR_STATE_ORANGE_YELLOW) {
            MOTOR_PORT = 0xFF & ~(1 << MOTOR_PORT_ORANGE) & ~(1 << MOTOR_PORT_YELLOW);
            motor_state = MOTOR_STATE_YELLOW;
        } else if(motor_state == MOTOR_STATE_YELLOW) {
            MOTOR_PORT = 0xFF & ~(1 << MOTOR_PORT_YELLOW);
            motor_state = MOTOR_STATE_YELLOW_PINK;
        } else if(motor_state == MOTOR_STATE_YELLOW_PINK) {
            MOTOR_PORT = 0xFF & ~(1 << MOTOR_PORT_YELLOW) & ~(1 << MOTOR_PORT_PINK);
            motor_state = MOTOR_STATE_PINK;
        } else if(motor_state == MOTOR_STATE_PINK) {
            MOTOR_PORT = 0xFF & ~(1 << MOTOR_PORT_PINK);
            motor_state = MOTOR_STATE_PINK_BLUE;
        } else if(motor_state == MOTOR_STATE_PINK_BLUE) {
            MOTOR_PORT = 0xFF & ~(1 << MOTOR_PORT_PINK) & ~(1 << MOTOR_PORT_BLUE);
            motor_state = MOTOR_STATE_BLUE;
        } else if(motor_state == MOTOR_STATE_BLUE) {
            MOTOR_PORT = 0xFF & ~(1 << MOTOR_PORT_BLUE);
            motor_state = MOTOR_STATE_BLUE_ORANGE;
        } else if(motor_state == MOTOR_STATE_BLUE_ORANGE) {
            MOTOR_PORT = 0xFF & ~(1 << MOTOR_PORT_BLUE) & ~(1 << MOTOR_PORT_ORANGE);
            motor_state = MOTOR_STATE_ORANGE;
        }

        // reset the scaler
        timer1_scaler = 0;
    } else
        ++timer1_scaler;
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
