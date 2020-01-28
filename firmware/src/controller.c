#include "controller.h"

/**
 * @brief inicializa o CONTROLLER, configurado para conversão engatilhada com o timer0.
 */
void controller_init(void)
{
    // configuracao do CONTROLLER
    //clr_bit(PORTC,CONTROLLER0);
    //clr_bit(PORTC,CONTROLLER1);

}

void set_pwm_A_d(uint8_t d)
{

}
void set_pwm_B_d(uint8_t d)
{

}

inline uint32_t map(uint32_t  x, 
                    uint32_t  in_min, 
                    uint32_t  in_max, 
                    uint32_t  out_min, 
                    uint32_t  out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

inline void controller(void)
{
#ifdef PROA
    controller_proa();
#else
    controller_popa();
#endif
}

inline void controller_proa(void)
{

}

inline void controller_popa(void)
{
    uint8_t ang_dir = control.pot_proa;
    if(error_flags.no_canbus) ang_dir = 128;

	//ajustes
	int16_t inzero = 2; // ajuste do intervalo de zero, estabilidade na direção
	int16_t potini = 85; // ajuste de potencia inicial do pwm, ajusta a potencia e velocidade do motor
	int16_t potfin = 90; // ajuste de potencia final do pwm, ajusta a potencia e velocidade do motor

	uint8_t sensormotor = control.pot_popa;
	//Serial.print("motor = ");
	//Serial.println(sensormotor);
	//delay(5);
    //
	int16_t potmotor = sensormotor - ang_dir;

    if (potmotor > inzero){
        //Serial.print("positivo = ");
        //Serial.println(potmotor);
        if (potmotor > potfin) potmotor = potfin;
        potmotor = map(potmotor, 0, potfin, potini, 255);

        set_pwm_A_d(0);
        set_pwm_B_d(potmotor);
	}else if (potmotor < - inzero){
        //Serial.print("negativo = ");
        potmotor = potmotor * (-1);
        //Serial.println(potmotor);
        //
        if (potmotor > potfin) potmotor = potfin;
        potmotor = map(potmotor, 0, potfin, potini, 255);

        set_pwm_B_d(0);
        set_pwm_A_d(potmotor);
    }else{
        set_pwm_A_d(0);
        set_pwm_B_d(0);
	}

}
