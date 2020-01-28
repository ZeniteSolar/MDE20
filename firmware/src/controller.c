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

}
