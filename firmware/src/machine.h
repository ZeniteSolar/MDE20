/**
 * @file machine.h
 *
 * @defgroup MACHINE State Machine Module
 *
 * @brief Implements the main state machine of the system.
 *
 */

#ifndef MACHINE_H
#define MACHINE_H 

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "controller.h"

#include "conf.h"

// Equations for mode 2 (CTC with TOP OCR2A)
// Note the resolution. For example.. at 150hz, ICR1 = PWM_TOP = 159, so it
#define MACHINE_TIMER_TOP ((F_CPU/(2*MACHINE_TIMER_PRESCALER))/(MACHINE_TIMER_FREQUENCY) -1)

#ifdef ADC_ON
#include "adc.h"
#endif
#ifdef USART_ON
#include "usart.h"
#endif
#include "dbg_vrb.h"
#ifdef CAN_ON
#include "can.h"
#include "can_app.h"
extern const uint8_t can_filter[];
#endif

typedef enum state_machine{
    STATE_INITIALIZING,
    STATE_IDLE,
    STATE_RUNNING,
    STATE_ERROR,
    STATE_RESET,
} state_machine_t;

typedef union system_flags{
    struct{
    };
    uint8_t   all__;
} system_flags_t;

typedef union error_flags{
    struct{
        uint8_t     no_canbus     :1;
    };
    uint8_t   all;
}error_flags_t;

typedef struct control
{
    uint8_t dt_A;
    uint8_t dt_B;
    uint8_t pot_proa;
    uint8_t pot_popa;
}control_t;
control_t control;

void read_potentiometer(void);

// machine checks
void reset_measurements(void);
void average_measurements(void);

// debug functions
void print_configurations(void);
void print_system_flags(void);
void print_error_flags(void);

// machine tasks
void task_initializing(void);
void task_idle(void);
void task_running(void);
void task_error(void);
void task_reset(void);
void task_waiting_reset(void);

// the machine itself
void set_machine_initial_state(void);
void machine_init(void);
void machine_run(void);
void set_state_error(void);
void set_state_initializing(void);
void set_state_idle(void);
void set_state_running(void);
void set_state_reset(void);
void set_state_waiting_reset(void);

//input functions
void read_potentiometers(void);

void buzzer(uint8_t buzzer_frequency, uint8_t buzzer_rhythm_on, uint8_t buzzer_rhythm_off);

// machine variables
volatile state_machine_t state_machine;
volatile system_flags_t system_flags;
volatile error_flags_t error_flags;
volatile control_t coltrol;
volatile uint16_t charge_count_error;
volatile uint8_t machine_clk;
volatile uint8_t machine_clk_divider;
volatile uint8_t total_errors;           // Contagem de ERROS
volatile uint8_t reset_clk;
volatile uint8_t led_clk_div;
volatile uint8_t can_app_checks_without_mde20_msg;

// ISRs
ISR(TIMER2_COMPA_vect);
ISR(PCINT2_vect);

#endif /* ifndef MACHINE_H */
