#include "button.h"


void _button_init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Pin = _BTN_PIN;

	GPIO_Init(_BTN_PORT, &GPIO_InitStruct);

}

uint8_t get_btn_status(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
}
