#ifndef BUTTON_H_
#define BUTTON_H_

#include "stm32f4xx_gpio.h"

#define _BTN_PIN	GPIO_Pin_0
#define _BTN_PORT	GPIOA

#define BTN_ON		0
#define BTN_OFF		!BTN_ON

void _button_init(void);
uint8_t get_btn_status(void);

#endif /* BUTTON_H_ */
