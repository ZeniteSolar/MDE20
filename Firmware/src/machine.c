#include "machine.h"


/**
 * @brief 
 */
void machine_init(void)
{
	//clr_bit(PRR0, PRTIM2);                          // Activates clock

    // MODE 2 -> CTC with TOP on OCR1
    TCCR2A  =    (1 << WGM21) | (0 << WGM20)        // mode 2
              | (0 << COM2B1) | (0 << COM2B0)       // do nothing
              | (0 << COM2A1) | (0 << COM2A0);      // do nothing

    TCCR2B =
#if MACHINE_TIMER_PRESCALER ==     1
                (0 << CS22) | (0 << CS21) | (1 << CS20) // Prescaler N=1
#elif MACHINE_TIMER_PRESCALER ==   8
                (0 << CS22) | (1 << CS21) | (0 << CS20) // Prescaler N=8
#elif MACHINE_TIMER_PRESCALER ==   32
                (0 << CS22) | (1 << CS21) | (1 << CS20) // Prescaler N=32
#elif MACHINE_TIMER_PRESCALER ==   64
                (1 << CS22) | (0 << CS21) | (0 << CS20) // Prescaler N=64
#elif MACHINE_TIMER_PRESCALER ==   128
                (1 << CS22) | (0 << CS21) | (1 << CS20) // Prescaler N=128
#elif MACHINE_TIMER_PRESCALER ==   256
                (1 << CS22) | (1 << CS21) | (0 << CS20) // Prescaler N=256
#elif MACHINE_TIMER_PRESCALER ==   1024
                (1 << CS22) | (1 << CS21) | (1 << CS20) // Prescaler N=1024
#else
                0
#endif
                | (0 << WGM22);      // mode 2

    OCR2A = MACHINE_TIMER_TOP;                       // OCR2A = TOP = fcpu/(N*2*f) -1

    TIMSK2 |=   (1 << OCIE2A);                      // Activates interruption

    set_machine_initial_state();
    set_state_initializing();
} 

/**
 * @brief set machine initial state
 */
inline void set_machine_initial_state(void)
{
    error_flags.all = 0;
    machine_clk = machine_clk_divider = led_clk_div = 0;
}

/**
 * @brief set error state
 */
inline void set_state_error(void)
{
    VERBOSE_MSG_MACHINE(usart_send_string("\n>>>STATE ERROR\n"));
    state_machine = STATE_ERROR;
}

/**
* @brief set initializing state
*/ 
inline void set_state_initializing(void)
{
    VERBOSE_MSG_MACHINE(usart_send_string("\n>>>INITIALIZING STATE\n"));
    state_machine = STATE_INITIALIZING;
}

/**
* @brief set idle state
*/ 
inline void set_state_idle(void)
{
    VERBOSE_MSG_MACHINE(usart_send_string("\n>>>IDLE STATE\n"));
    state_machine = STATE_IDLE;
 }

/**
* @brief set running state
*/ 
inline void set_state_running(void)
{
    VERBOSE_MSG_MACHINE(usart_send_string("\n>>>RUNNING STATE\n"));
    state_machine = STATE_RUNNING;
 }

/**
 * @brief set reset state
 */
inline void set_state_reset(void)
{
    VERBOSE_MSG_MACHINE(usart_send_string("\n>>>RESET STATE\n"));
    state_machine = STATE_RESET;
}



/**
 * @breif prints the configurations and definitions
 */
inline void print_configurations(void)
{    
    VERBOSE_MSG_MACHINE(usart_send_string("CONFIGURATIONS:\n"));
    
    VERBOSE_MSG_MACHINE(usart_send_string("\nadc_f: "));
    VERBOSE_MSG_MACHINE(usart_send_uint16( ADC_FREQUENCY ));
    VERBOSE_MSG_MACHINE(usart_send_char(','));
    VERBOSE_MSG_MACHINE(usart_send_uint16( ADC_AVG_SIZE_10 ));
    VERBOSE_MSG_MACHINE(usart_send_string("\nmachine_f: "));
    VERBOSE_MSG_MACHINE(usart_send_uint16( MACHINE_FREQUENCY ));

    VERBOSE_MSG_MACHINE(usart_send_char('\n'));
}

/**
* @brief prints the system flags
*/
inline void print_system_flags(void)
{
    //VERBOSE_MSG_MACHINE(usart_send_string(" EN "));
    //VERBOSE_MSG_MACHINE(usart_send_char(48+system_flags.enable));
}

/**
* @brief prints the error flags
*/

inline void print_error_flags(void)
{
    //VERBOSE_MSG_MACHINE(usart_send_string(" errFl: "));
    //VERBOSE_MSG_MACHINE(usart_send_char(48+error_flags.no_canbus));
}
 


inline void task_initializing(void)
{
#ifdef LED_ON
    set_led(LED1);
#endif

    set_machine_initial_state();

    VERBOSE_MSG_INIT(usart_send_string("System initialized without errors.\n"));
    set_state_idle();
} 


inline void acumulate_potentiometers(void)
{

    if(control.motor_PWM_target.samples <= ADC_AVG_VARIABLE_OVERFLOW_PROTECTION){     //variable overflow protection (2^32)/255 = 16843009
    control.motor_PWM_target.sum += adc.channel[MOTOR_PWM_POT].avg;
    control.motor_PWM_target.samples ++;
    }
    else    VERBOSE_MSG_MACHINE(usart_send_string("ADC_AVG_VARIABLE_OVERFLOW_PROTECTION"));

    if(control.motor_RAMP_target.samples <= ADC_AVG_VARIABLE_OVERFLOW_PROTECTION){     //variable overflow protection (2^32)/255 = 16843009
    control.motor_RAMP_target.sum += adc.channel[MOTOR_RAMP_POT].avg;
    control.motor_RAMP_target.samples ++;
    }
    else    VERBOSE_MSG_MACHINE(usart_send_string("ADC_AVG_VARIABLE_OVERFLOW_PROTECTION"));

    if(control.MCC_POWER_target.samples <= ADC_AVG_VARIABLE_OVERFLOW_PROTECTION){     //variable overflow protection (2^32)/255 = 16843009
    control.MCC_POWER_target.sum += adc.channel[MCC_POWER_POT].avg;
    control.MCC_POWER_target.samples ++;
    }
    else    VERBOSE_MSG_MACHINE(usart_send_string("ADC_AVG_VARIABLE_OVERFLOW_PROTECTION"));
}

inline void average_potentiometers(void)
{
    control.motor_PWM_target.avg = 
    control.motor_PWM_target.sum / control.motor_PWM_target.samples;
    control.motor_PWM_target.sum = control.motor_PWM_target.samples = 0;

    control.motor_RAMP_target.avg = 
    control.motor_RAMP_target.sum / control.motor_RAMP_target.samples;
    control.motor_RAMP_target.sum = control.motor_RAMP_target.samples = 0;

    control.MCC_POWER_target.avg = 
    control.MCC_POWER_target.sum / control.MCC_POWER_target.samples;
    control.MCC_POWER_target.sum = control.MCC_POWER_target.samples = 0;


}

inline void read_boat_on(void)
{

    static uint8_t count_boat_on_state = 0;
    static uint8_t count_boat_off_state = 0;

    //BOAT SWITCH
    if (!tst_bit(CTRL_SWITCHES_PIN,BOAT_ON_SWITCH)){
        if (++count_boat_on_state >= BOAT_ON_TO_UPDATE){
            count_boat_off_state = 0;
            system_flags.boat_on = 1;
        }
    }
    else{
        if (++count_boat_off_state >= BOAT_ON_TO_UPDATE){
            count_boat_on_state = 0;
            system_flags.boat_on = 0;
        }
    }
    //END OF BOAT SWITCH


}

inline void reset_switches(void)
{
    system_flags.motor_on = 0;
    system_flags.dead_men_switch = 0;
    system_flags.MCC_on = 0;
}


inline void read_pump_switches(void)
{

    if (tst_bit(PUMPS_SWITCHES_PIN, PUMP1_ON_SWITCH))
        system_flags.pump1_on = 0;
    else
        system_flags.pump1_on = 1;

    if (tst_bit(PUMPS_SWITCHES_PIN, PUMP2_ON_SWITCH))
        system_flags.pump2_on = 0;
    else
        system_flags.pump2_on = 1;

    if (tst_bit(PUMPS_SWITCHES_PIN, PUMP3_ON_SWITCH))
        system_flags.pump3_on = 0;
    else
        system_flags.pump3_on = 1;

}

inline void read_switches(void)
{
    static uint8_t clk_div_switch_msg = 0;
    static uint8_t count_motor_on_state = 0;
    static uint8_t count_motor_off_state = 0;
    static uint8_t count_DMS_on_state = 0;
    static uint8_t count_DMS_off_state = 0;


    //TEST DIGITAL PINS AND FILTER THEM

    //MOTOR SWITCH
    if (!tst_bit(CTRL_SWITCHES_PIN,MOTOR_ON_SWITCH)){
        if (++count_motor_on_state >= MOTOR_ON_TO_UPDATE){
            count_motor_off_state = 0;
            system_flags.motor_on = 1;
        }
    }
    else{
        if (++count_motor_off_state >= MOTOR_ON_TO_UPDATE){
            count_motor_on_state = 0;
            system_flags.motor_on = 0;
        }
    }
    //END OF MOTOR SWITCH

    //DEAD MEN SWITCH
    if (!tst_bit(DMS_PIN,DMS)){
        if (++count_DMS_on_state >= DEAD_MEN_TO_UPDATE){
            count_DMS_off_state = 0;
            system_flags.dead_men_switch = 1;
        }
    }   
    else{
        if (++count_DMS_off_state >= DEAD_MEN_TO_UPDATE){
            count_DMS_on_state = 0;
            system_flags.dead_men_switch = 0;
        }
    }
    //END OF DEAD MEN SWITCH

    if (!tst_bit(CTRL_SWITCHES_PIN, MCC_ON_SWITCH))
        system_flags.MCC_on = 1;
    else
        system_flags.MCC_on = 0;


    if (++clk_div_switch_msg >= 10)
    {
        clk_div_switch_msg = 0;
    VERBOSE_MSG_MACHINE(usart_send_string("reading switches:... \n"));
    VERBOSE_MSG_MACHINE(usart_send_string("system_flags:"));
    VERBOSE_MSG_MACHINE(usart_send_uint16(system_flags.all__));
    VERBOSE_MSG_MACHINE(usart_send_string("OK! \n"));
    }

}

/**
 * @brief waits for commands while checking the system
 */
inline void task_idle(void)
{
#ifdef LED_ON
    if(led_clk_div++ >= 30){
        cpl_led(LED1);
        led_clk_div = 0;
    }        
#endif

    reset_switches();

    read_boat_on();

    read_pump_switches();

    if (system_flags.boat_on)
        set_state_running();

}


/**
 * @brief running task checks the system and apply the control action to pwm.
 */
inline void task_running(void)
{

    read_boat_on();

    read_switches();

    read_pump_switches();

    acumulate_potentiometers();    

#ifdef LED_ON
    if(led_clk_div++ >= 2){
        cpl_led(LED1);
        led_clk_div = 0;
    }
#endif // LED_ON

    if(!system_flags.boat_on)
        set_state_idle();


}


/**
 * @brief error task checks the system and tries to medicine it.
 */
inline void task_error(void)
{
#ifdef LED_ON
    if(led_clk_div++ >= 5){
        set_led(LED1);
        led_clk_div = 0;
    }
#endif
    set_state_initializing();

    total_errors++;         // incrementa a contagem de erros
    VERBOSE_MSG_ERROR(usart_send_string("The error code is: "));
    VERBOSE_MSG_ERROR(usart_send_uint16(error_flags.all));
    VERBOSE_MSG_ERROR(usart_send_char('\n'));


    if(!error_flags.all)
        VERBOSE_MSG_ERROR(usart_send_string("\t - Oh no, it was some unknown error.\n"));
 
    VERBOSE_MSG_ERROR(usart_send_string("The error level is: "));
    VERBOSE_MSG_ERROR(usart_send_uint16(total_errors));
    VERBOSE_MSG_ERROR(usart_send_char('\n'));
    
    if(total_errors < 2){
        VERBOSE_MSG_ERROR(usart_send_string("I will reset the machine state.\n"));
    }
    if(total_errors >= 20){
        VERBOSE_MSG_ERROR(usart_send_string("The watchdog will reset the whole system.\n"));
        set_state_reset();
    }

        
#ifdef LED_ON
    cpl_led(LED1);
#endif



}

                    
/**
 * @brief reset error task just freezes the processor and waits for watchdog
 */
inline void task_reset(void)
{   
#ifndef WATCHDOG_ON
    //wdt_init();
#endif

    cli();  // disable interrupts

    VERBOSE_MSG_ERROR(usart_send_string("WAITING FOR A RESET!\n"));
    for(;;);
}

void print_infos(void)
{
    static uint8_t i = 0;

    switch(i++){
        case 0:
            //print_system_flags();
            break;
        case 1:
            //print_error_flags();
            break;
        case 2:
            //print_control_others(); 
        default:
            //VERBOSE_MSG_MACHINE(usart_send_char('\n'));
            i = 0;
            break;
    }
}



/**
 * @brief this is the machine state itself.
 */
inline void machine_run(void)
{
    //print_infos();
    

    if(machine_clk){
        machine_clk = 0;
    #ifdef ADC_ON
        if(adc.ready){
            adc.ready = 0;


            if(error_flags.all){
                print_system_flags();
                print_error_flags();
                print_infos();
                set_state_error();
            }



            switch(state_machine){
                case STATE_INITIALIZING:
                    task_initializing();

                    break;
                case STATE_IDLE:
                    task_idle();
                    #ifdef CAN_ON
                        can_app_task();
                    #endif /* CAN_ON */   
                    break;
                case STATE_RUNNING:
                    task_running();
                    #ifdef CAN_ON
                        can_app_task();
                    #endif /* CAN_ON */   

                    break;
                case STATE_ERROR:
                    task_error();

                case STATE_RESET:
                default:
                    task_reset();
                    break;
            }
        } 
    #endif /* ADC_ON */
    }
}

/**
* @brief ISR para ações de controle
*/
ISR(TIMER2_COMPA_vect)
{
    if(machine_clk_divider++ == MACHINE_CLK_DIVIDER_VALUE){
        /*if(machine_clk){
            for(;;){
                pwm_reset();
                VERBOSE_MSG_ERROR(if(machine_clk) usart_send_string("\nERROR: CLOCK CONFLICT!!!\n"));
            }
        }*/
        machine_clk = 1;
        machine_clk_divider = 0;
    }
}

