#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include "dbg_vrb.h"
#include "../lib/bit_utils.h"
#ifdef USART_ON
#include "usart.h"
#endif

#ifndef PWM_TIMER_PRESCALER
#define PWM_TIMER_PRESCALER  4
#endif

void pwm_init(void);
void set_pwm_A_d(uint8_t d);
void set_pwm_B_d(uint8_t d);

#endif /* PWM_H */
