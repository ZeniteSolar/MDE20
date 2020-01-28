
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <avr/io.h>
#include "conf.h"
#include "machine.h"

void controller_init(void);

void controller(void);
void controller_proa(void);
void controller_popa(void);

void set_pwm_A_d(uint8_t);
void set_pwm_B_d(uint8_t);

#endif /* ifndef CONTROLLER_H */
