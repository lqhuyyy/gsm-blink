#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f4xx_it.h"

void systick_init(void);

uint32_t sys_get_tick_ms(void);

#endif /* SYSTICK_H_ */
