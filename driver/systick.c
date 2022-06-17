#include <systick.h>

static uint32_t tick_ms;

void systick_init(void)
{
	RCC_DeInit();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
}


void SysTick_Handler(void){
	tick_ms++;
}

uint32_t sys_get_tick_ms(void)
{
	return tick_ms;
}

