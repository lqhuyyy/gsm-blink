#include <m_hal_init.h>
#include "string.h"

#include "m_log.h"
#include "m_sim.h"
#include "other.h"

int main(void) {
	static uint8_t check_at = 0;
	static state_machine = GSM_POWER_ON;
	static uint8_t is_check_at = 0;

	hal_init();

	log_com3("test uart\n", strlen("test uart\n"));

	while (1) {
		process_data();
		blink_led();

		switch (state_machine) {
		case GSM_POWER_ON:
			if (power_on() == 1) {
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
}
