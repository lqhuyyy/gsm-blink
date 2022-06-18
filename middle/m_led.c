#include "m_led.h"
#include "hal.h"
#include <string.h>

void blink_led(void) {
	static uint32_t state = 0;
	static uint32_t old_tick_ms = 0;
	static uint32_t time_to_wait = 0;

	if (sys_get_tick_ms() - old_tick_ms < time_to_wait)
		return;

	old_tick_ms = sys_get_tick_ms();

	switch (state) {
	case LED_OFF:
		led_off();
		state = LED_ON;
		time_to_wait = 500;
		break;
	case LED_ON:
		//
		led_on();
		state = LED_OFF;
		time_to_wait = 500;
		break;
	default:
		state = LED_ON;
		break;
	}

}

//void switch_led(){
//	static uint8_t is_on = 0;
//	if(is_on){
//		is_on = 1;
//		led_off();
//	} else {
//		is_on = 0;
//		led_on();
//	}
//}

void turn_led_on()
{
	led_on();
}

void turn_led_off()
{
	led_off();
}
