/**
 * @file pwm.c
 */
 #include "pwm.h"

 void pwm_init(void)
{


  DDRD |= (1 << PD5) | (1 << PD6);

  // MODE 2 -> CTC with TOP on OCR1
  TCCR0A  =   (1 << WGM01) | (0 << WGM00)         // mode 2
          | (1 << COM0B1) | (0 << COM0B0)
          | (1 << COM0A1) | (0 << COM0A0);

  TCCR0B  =
#if PWM_TIMER_PRESCALER ==     1
              (0 << CS02) | (0 << CS01) | (1 << CS00) // Prescaler N=1
#elif PWM_TIMER_PRESCALER ==   8
              (0 << CS02) | (1 << CS01) | (0 << CS00) // Prescaler N=8
#elif PWM_TIMER_PRESCALER ==   32
              (0 << CS02) | (1 << CS01) | (1 << CS00) // Prescaler N=32
#elif PWM_TIMER_PRESCALER ==   64
              (1 << CS02) | (0 << CS01) | (0 << CS00) // Prescaler N=64
#elif PWM_TIMER_PRESCALER ==   128
              (1 << CS02) | (0 << CS01) | (1 << CS00) // Prescaler N=128
#elif PWM_TIMER_PRESCALER ==   256
              (1 << CS02) | (1 << CS01) | (0 << CS00) // Prescaler N=256
#elif PWM_TIMER_PRESCALER ==   1024
              (1 << CS02) | (1 << CS01) | (1 << CS00) // Prescaler N=1024
#else
              0
#endif
              | (0 << WGM02);      // mode 2


          ICR1 = 200;
          OCR0A = 10;
          OCR0B = 10;
}

void set_pwm_A_d(uint8_t d)
{
  OCR0A = d;
}

void set_pwm_B_d(uint8_t d)
{
  OCR0B = d;
}
