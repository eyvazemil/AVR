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

// array with states
static volatile uint8_t arr_motor_states[8] = {
    MOTOR_STATE_ORANGE, 
    MOTOR_STATE_ORANGE_YELLOW,
    MOTOR_STATE_YELLOW,
    MOTOR_STATE_YELLOW_PINK,
    MOTOR_STATE_PINK,
    MOTOR_STATE_PINK_BLUE,
    MOTOR_STATE_BLUE,
    MOTOR_STATE_BLUE_ORANGE
};

// array with the ports of motor states
static volatile uint8_t arr_motor_ports[4] = {
    MOTOR_PORT_ORANGE,
    MOTOR_PORT_YELLOW,
    MOTOR_PORT_PINK,
    MOTOR_PORT_BLUE
};

// index of the current state of the DC stepper motor
static volatile uint8_t motor_state_id = 0;

// direction of the motor
static volatile uint8_t motor_direction = CLOCKWISE;

// scaler for 16-bit timer
static volatile uint8_t timer1_scaler = 0;

ISR(TIMER1_COMPA_vect) {
    if(timer1_scaler == TIMER1_SCALER) {
        MOTOR_PORT = 0xFF & ~(1 << arr_motor_ports[motor_state_id / 2]);

        // for a given even state, write the next state to the port too
        if(motor_state_id % 2) {
            if(motor_state_id == MOTOR_NUM_STATES - 1)
                MOTOR_PORT &= ~(1 << arr_motor_ports[0]); // if it is BLUE add ORANGE
            else
                MOTOR_PORT &= ~(1 << arr_motor_ports[motor_state_id / 2 + 1]);
        }

        if(motor_direction == COUNTERCLOCKWISE) {
            if(motor_state_id == MOTOR_NUM_STATES - 1)
                motor_state_id = 0;
            else
                ++motor_state_id;
        } else {
            if(motor_state_id == 0)
                motor_state_id = MOTOR_NUM_STATES - 1;
            else
                --motor_state_id;
        }

        // reset the scaler
        timer1_scaler = 0;
    } else
        ++timer1_scaler;
}

ISR(PCINT0_vect) {
    if(!(BUTTON_PIN & (1 << BUTTON))) { // grounded => pressed
        _delay_us(DEBOUNCE_DELAY); // debounce

        if(!(BUTTON_PIN & (1 << BUTTON))) { // still pressed => it was a real press
            if(motor_direction == CLOCKWISE)
                motor_direction = COUNTERCLOCKWISE;
            else
                motor_direction = CLOCKWISE;
        }
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
