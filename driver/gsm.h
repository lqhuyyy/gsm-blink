#ifndef GSM_H_
#define GSM_H_

#include "stm32f4xx.h"

uint8_t gsm_get_status(void);

void gsm_pull_up_pwr(void);

void gsm_pull_down_pwr(void);

#endif /* GSM_H_ */
