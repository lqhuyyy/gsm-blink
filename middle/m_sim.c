#include <gsm.h>
#include <systick.h>
#include "m_sim.h"

#include "squeue.h"
#include "log.h"

static sq_t queue_data;

void sendCmdSim(char* cmd)
{
	gsm_send_str(cmd);
}

void process_data_receive(void)
{
	if(gsm_have_new_data() && sys_get_tick_ms() - gsm_get_old_ms_received() > 50)
	{
		char data_received[512];
		uint32_t data_len = gsm_get_new_data(data_received);
		sq_push(&queue_data, data_received);
		gsm_clear_uart_buffer();
		log_com3_ln(data_received, data_len);
	}

	if(!sq_is_empty(&queue_data)){

	}

}

uint8_t power_on(void) {
	static gsm_state_t state = PWR_GET_STATUS;
	static uint32_t old_tick_ms = 0;
	static uint32_t time_to_wait = 0;
	static uint8_t status = 0;

	if (sys_get_tick_ms() - old_tick_ms < time_to_wait)
		return 0;
	old_tick_ms = sys_get_tick_ms();

	switch (state) {
		case PWR_GET_STATUS:
			log_com3_ln("PWR_GET_STATUS", strlen("PWR_GET_STATUS"));
			status = gsm_get_status();
			if (status == GSM_POWER_ON) {
				/* reset power */
				state = PWR_OFF_STEP_1;
				time_to_wait = 0;
				status = 0;
			} else {
				/* power on */
				state = PWR_ON_STEP_1;
				time_to_wait = 0;
			}
			break;

		case PWR_ON_STEP_1:
			gsm_pull_down_pwr();
			time_to_wait = 1000;
			state = PWR_ON_STEP_2;
			log_com3_ln("PWR_ON_STEP_1\n", strlen("PWR_ON_STEP_1\n"));
			break;

		case PWR_ON_STEP_2:
			gsm_pull_up_pwr();
			time_to_wait = 5000;
			state = PWR_WAIT_STATUS_ON;
			log_com3_ln("PWR_ON_STEP_2\n", strlen("PWR_ON_STEP_2\n"));
			break;

		case PWR_WAIT_STATUS_ON:
			status = gsm_get_status();
			if (status == 1) {
				state = PWR_GET_STATUS;
				log_com3_ln("power on\n", strlen("power on\n"));
				return 1;
			}
			break;

		case PWR_OFF_STEP_1:
			gsm_pull_down_pwr();
			time_to_wait = 2500;
			state = PWR_OFF_STEP_2;
			log_com3_ln("power off 1\n", strlen("power off 1\n"));
			break;

		case PWR_OFF_STEP_2:
			gsm_pull_up_pwr();
			time_to_wait = 3000;
			state = PWR_WAIT_STATUS_OFF;
			log_com3_ln("power off 2\n", strlen("power off 2\n"));
			break;

		case PWR_WAIT_STATUS_OFF:
			time_to_wait = 50;
			if (gsm_get_status() == 0) {
				state = PWR_ON_STEP_1;
				log_com3_ln("power off\n", strlen("power off\n"));
			}
			break;

		default:
			break;
	}

	return 0;
}

void gsm_loop(void)
{
	static state_machine = GSM_POWER_ON;
	static uint8_t is_check_at = 0;

	switch (state_machine) {
		case GSM_POWER_ON:
			if (power_on() == 1) {
//				led_on();
				state_machine = GSM_SEND_CMD;
			}
			break;

		case GSM_SEND_CMD:
			if(!is_check_at){
				is_check_at = 1;
				sendCmdSim("AT+CICCID=?\r");
			}
			break;
	}

}
