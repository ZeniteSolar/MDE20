/**
 * @file conf.h
 *
 * @defgroup CONF Configurations 
 *
 * @brief General configuration of the system.
 *
 */

#ifndef CONF_H
//#define CONF_H

#ifndef F_CPU
#define F_CPU 16000000UL    //define a frequencia do microcontrolador - 16MHz
#endif /* ifndef F_CPU */


// CONFIGURACOES DE COMPILACAO
#define DEBUG_ON
#define VERBOSE_ON
//#define VERBOSE_ON_CAN_APP
#define VERBOSE_ON_MACHINE
//#define VERBOSE_ON_ADC
#define VERBOSE_ON_INIT
#define VERBOSE_ON_ERROR

#define PROA
//#define POPA

#define CAN_SIGNATURE_MDE20_PROA        80
#define CAN_SIGNATURE_MDE20_POPA        81
#define CAN_MSG_MDE20_CONTROL_POT_BYTE  2
#define CAN_MSG_MDE20_CONTROL_ID        82

#ifdef PROA
#define CAN_SIGNATURE_SELF              CAN_SIGNATURE_MDE20_PROA
#endif
#ifdef POPA
#define CAN_SIGNATURE_SELF              CAN_SIGNATURE_MDE20_POPA
#endif


// MODULES ACTIVATION
#define USART_ON
//#define CAN_ON
//#define CAN_DEPENDENT
#define ADC_ON
#define MACHINE_ON
#define LED_ON
//#define BUZZER_ON
#define WATCHDOG_ON
//#define SLEEP_ON	
//#define CHECK_MCS_ON

//PINS UPDATE FILTER CONFIGURATION
#define BOAT_ON_TO_UPDATE 10
#define MOTOR_ON_TO_UPDATE 10
#define DEAD_MEN_TO_UPDATE 10
#define EMERGENCY_ON_TO_UPDATE 10

#ifdef POPA
#define PWM_A           PD6
#define PWM_B           PD5
#define PWM_PORT        PORTD
#define PWM_DDR         DDRD
#endif

#ifdef ADC_ON
#define ADC_8BITS
// ADC CONFIGURATION
// note that changing ADC_FREQUENCY may cause problems with avg_sum_samples
#define ADC_FREQUENCY                       1000 // 20000
#define ADC_TIMER_PRESCALER                 64
#define ADC_AVG_SIZE_10                     1024
#define ADC_AVG_SIZE_2                      10

//#define FAKE_ADC_ON
#ifdef FAKE_ADC_ON
#define FAKE_ADC                            1
#endif // FAKE_ADC_ON

#endif //ADC_ON


#ifdef MACHINE_ON
// The machine frequency may not be superior of ADC_FREQUENCY/ADC_AVG_SIZE_10
#define MACHINE_TIMER_FREQUENCY             120           //<! machine timer frequency in Hz
#define MACHINE_TIMER_PRESCALER             1024          //<! machine timer prescaler
#define MACHINE_CLK_DIVIDER_VALUE           ((uint64_t)(uint32_t)MACHINE_TIMER_FREQUENCY*(uint32_t)ADC_AVG_SIZE_10)/(ADC_FREQUENCY)           //<! machine_run clock divider
#define MACHINE_FREQUENCY                   (MACHINE_TIMER_FREQUENCY)/(MACHINE_CLK_DIVIDER_VALUE)

#endif // MACHINE_ON

#define 	POT			            ADC0

#ifdef LED_ON
#define     LED_PORT                PORTD
#define     LED_PIN                 PIND
#define     LED_DDR                 DDRD
#define     LED1                    PD6
#define     cpl_led(y)              cpl_bit(LED_PORT, y)
#define     set_led(y)              set_bit(LED_PORT, y)
#define     clr_led(y)              clr_bit(LED_PORT, y)
#else
#define     cpl_led()               
#define     set_led()               
#define     clr_led()               
#endif // LED_ON

#define     BUZZER_PORT             PORTD
#define     BUZZER_PIN              PIND
#define     BUZZER_DDR              DDRD
#define     BUZZER                  PD4
#ifdef BUZZER_ON
#define     cpl_buzzer()            cpl_bit(BUZZER_PORT, BUZZER)
#define     set_buzzer()            set_bit(BUZZER_PORT, BUZZER)
#define     clr_buzzer()            clr_bit(BUZZER_PORT, BUZZER)
#else
#define     cpl_buzzer()            
#define     set_buzzer()            
#define     clr_buzzer()            
#endif

#define CAN_APP_SEND_STATE_FREQ     40//36000     //<! state msg frequency in Hz
#define CAN_APP_SEND_POT_FREQ     4//36000     //<! motor msg frequency in Hz

#ifdef CAN_ON
#define SPI_ON

// CANBUS DEFINITONS
// ----------------------------------------------------------------------------
/* Global settings for building the can-lib and application program.
 *
 * The following two #defines must be set identically for the can-lib and
 * your application program. They control the underlying CAN struct. If the
 * settings disagree, the underlying CAN struct will be broken, with
 * unpredictable results.
 * If can.h detects that any of the #defines is not defined, it will set them
 * to the default values shown here, so it is in your own interest to have a
 * consistent setting. Ommiting the #defines in both can-lib and application
 * program will apply the defaults in a consistent way too.
 *
 * Select if you want to use 29 bit identifiers.
 */
#define	SUPPORT_EXTENDED_CANID	0

/* Select if you want to use timestamps.
 * Timestamps are sourced from a register internal to the AT90CAN.
 * Selecting them on any other controller will have no effect, they will
 * be 0 all the time.
 */
#define	SUPPORT_TIMESTAMPS		0
#endif // CAN_ON

#endif /* ifndef CONF_H */
