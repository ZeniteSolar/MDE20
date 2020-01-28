#include "can_app.h"

/**
 * @brief Prints a can message via usart
 */
inline void can_app_print_msg(can_t *msg)
{
#ifdef USART_ON
    usart_send_string("ID: ");
    usart_send_uint16(msg->id);
    usart_send_string(". D: ");

    for(uint8_t i = 0; i < msg->length; i++){
      usart_send_uint16(msg->data[i]);
      usart_send_char(' ');
    }

    usart_send_string(". ERR: ");
    can_error_register_t err = can_read_error_register();
    usart_send_uint16(err.rx);
    usart_send_char(' ');
    usart_send_uint16(err.tx);
    usart_send_char('\n');
#endif
}

/**
* @brief Manages the canbus application protocol
*/
inline void can_app_task(void)
{
    check_can();

    if(can_app_send_state_clk_div++ >= CAN_APP_SEND_STATE_CLK_DIV){
        can_app_send_state();
        can_app_send_state_clk_div = 0;
    }

    if(can_app_send_pot_clk_div++ >= CAN_APP_SEND_POT_CLK_DIV){
        can_app_send_pot();
        can_app_send_pot_clk_div = 0;
    }

}

inline void can_app_send_state(void)
{
    can_t msg;
    msg.id                                  = CAN_MSG_MIC19_STATE_ID;
    msg.length                              = CAN_MSG_GENERIC_STATE_LENGTH;
    msg.flags.rtr = 0;

    msg.data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE]  = CAN_SIGNATURE_SELF;
    msg.data[CAN_MSG_GENERIC_STATE_STATE_BYTE]      = (uint8_t) state_machine;
    msg.data[CAN_MSG_GENERIC_STATE_ERROR_BYTE]      = error_flags.all;

    can_send_message(&msg);

    VERBOSE_MSG_CAN_APP(usart_send_string("state msg was send.\n"));
    VERBOSE_MSG_CAN_APP(can_app_print_msg(&msg));
}

inline void can_app_send_pot(void)
{
    can_t msg;
    msg.id                                  = CAN_MSG_MIC19_MOTOR_ID;
    msg.length                              = CAN_MSG_MIC19_MOTOR_LENGTH;
    msg.flags.rtr = 0;

    msg.data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE]  = CAN_SIGNATURE_SELF;
#ifdef PROA
    msg.data[CAN_MSG_MDE20_CONTROL_POT_BYTE]        = control.pot_proa;
#else
    msg.data[CAN_MSG_MDE20_CONTROL_POT_BYTE]        = control.pot_popa;
#endif

    can_send_message(&msg);

    VERBOSE_MSG_CAN_APP(usart_send_string("pot msg was send.\n"));
    VERBOSE_MSG_CAN_APP(can_app_print_msg(&msg));
}

inline void can_app_extractor_mde20_proa_pot(can_t *msg)
{
    if(msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MDE20_PROA){
        can_app_checks_without_mde20_msg = 0;

        control.pot_proa = msg->data[CAN_MSG_MDE20_CONTROL_POT_BYTE];
    }
}

 
/**
 * @brief redirects a specific message extractor to a given message
 * @param *msg pointer to the message to be extracted
 */
inline void can_app_msg_extractors_switch(can_t *msg)
{
    if(msg->data[CAN_MSG_GENERIC_STATE_SIGNATURE_BYTE] == CAN_SIGNATURE_MDE20_PROA){

        error_flags.no_canbus = can_app_checks_without_mde20_msg = 0;

        switch(msg->id){
            
            case CAN_MSG_MDE20_CONTROL_ID:
                VERBOSE_MSG_CAN_APP(usart_send_string("got a MDE msg: "));
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                can_app_extractor_mde20_proa_pot(msg);
            default:
#ifdef USART_ON
                VERBOSE_MSG_CAN_APP(usart_send_string("got a unknown msg:\n "));
#endif
                VERBOSE_MSG_CAN_APP(can_app_print_msg(msg));
                break;
        }    
    }
}

/**
 * @brief Manages to receive and extract specific messages from canbus
 */
inline void check_can(void)
{
    // If no messages is received from mde20 
    // CAN_APP_CHECKS_WITHOUT_MIC19_MSG cycles, than it go to a specific error state. 
    VERBOSE_MSG_CAN_APP(usart_send_string("checks: "));
    VERBOSE_MSG_CAN_APP(usart_send_uint16(can_app_checks_without_mde20_msg));
#ifdef CAN_DEPENDENT
     if(can_app_checks_without_mde20_msg++ >= CAN_APP_CHECKS_WITHOUT_MIC19_MSG){
#ifdef USART_ON
         VERBOSE_MSG_CAN_APP(usart_send_string("Error: too many cycles withtou message.\n"));
#endif
         can_app_checks_without_mde20_msg = 0;
         error_flags.no_canbus = 1;
         //set_state_error();
     }
#endif
    
    if(can_check_message()){
        can_t msg;
        if(can_get_message(&msg)){
            can_app_msg_extractors_switch(&msg);
        }
    }
}

