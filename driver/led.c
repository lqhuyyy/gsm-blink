#include "led.h"

void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = LED_PIN;

	GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

void led_on()
{
	GPIO_SetBits(LED_PORT, LED_PIN);
}

void led_off()
{
	GPIO_ResetBits(LED_PORT, LED_PIN);
}
