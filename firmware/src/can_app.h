/**
 * @file can_app.h
 *
 * @defgroup CANAPP    Application Module for canbus
 *
 * @brief The application layer module for canbus
 *
 */

#ifndef CAN_APP_H
#define CAN_APP_H 

#include "conf.h"
#include "dbg_vrb.h"
#include "../lib/bit_utils.h"
#include "can.h"
#include "can_ids.h"
#include "machine.h"
#include "usart.h"

void can_app_print_msg(can_t *msg);
void can_app_task(void);
void can_app_send_state(void);
void can_app_send_pot(void);
void can_app_extractor_mde20_proa_pot(can_t *msg);
void can_app_msg_extractors_switch(can_t *msg);
void check_can(void);

#define CAN_APP_SEND_STATE_CLK_DIV  CAN_APP_SEND_STATE_FREQ
#define CAN_APP_SEND_POT_CLK_DIV  CAN_APP_SEND_POT_FREQ

uint32_t can_app_send_state_clk_div;
uint32_t can_app_send_pot_clk_div;

#endif /* ifndef CAN_APP_H */
