#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

static void enable_clk(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
}


void hal_init(void)
{
	// clock
	enable_clk();

	// systick
	systick_init();

	// log
	log_init();

	// gsm power
	gsm_power_pin_init();

	// gsm uart
	gsm_uart_init();

	// led
	led_init();


//	button_init();
}
