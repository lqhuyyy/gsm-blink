#include "m_button.h"
#include "m_led.h"
#include "systick.h"
#include "m_log.h"



btn_state_t handle_button_loop(void)
{
	static uint32_t old_tick_ms;
	static uint32_t time_to_wait = 0;
	static btn_state_t state_machine = 0;
	static uint32_t time_check_long_click = 0;

	if(sys_get_tick_ms() - old_tick_ms < time_to_wait){
		return state_machine;
	}

	old_tick_ms = sys_get_tick_ms();

	switch(state_machine){
		case NO_CLICK:
			if(get_btn_status() == BTN_ON){
				state_machine = PENDING_CLICK;
				time_to_wait = 50;
			}
			break;
		case CLICK:
			log_com3("CLICK\n", strlen("CLICK\n"));
			state_machine = NO_CLICK;
			break;
		case PENDING_CLICK:
			if(get_btn_status() == BTN_ON){
				state_machine = PENDING_LONG_CLICK;
				time_check_long_click = sys_get_tick_ms();
			}else{
				state_machine = CLICK;
			}
			break;
		case PENDING_LONG_CLICK:
			if(get_btn_status() == BTN_ON){
				if(sys_get_tick_ms() - time_check_long_click >= LONG_CLICK_THRESH_HOLD){
					state_machine = LONG_CLICK;
					time_check_long_click = 0;
				}
			}else{
				state_machine = CLICK;
				time_check_long_click = 0;
			}
			break;
		case LONG_CLICK:
			if(get_btn_status() == BTN_OFF){
				state_machine = NO_CLICK;
				log_com3("LONG CLICK\n", strlen("LONG CLICK\n"));
			}
			break;
	}

	return state_machine;
}

