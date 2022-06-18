#ifndef GSM_H_
#define GSM_H_

#include "stm32f4xx.h"

uint8_t gsm_get_status(void);

void gsm_clear_uart_buffer(void);

uint32_t gsm_get_new_data(char *out_buff);

uint32_t gsm_get_old_ms_received(void);

uint32_t gsm_have_new_data(void);

void gsm_send_str(char* cmd);

void gsm_pull_up_pwr(void);

void gsm_pull_down_pwr(void);

#endif /* GSM_H_ */
