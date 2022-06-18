#include "string.h"

#include "m_hal_init.h"
#include "m_sim.h"
#include "m_button.h"
#include "m_log.h"


int main(void) {
	m_hal_init();

	log_com3_ln("test log", strlen("test log"));

	while (1) {
		process_data_receive();
//		blink_led();
		gsm_loop();
		handle_button_loop();

	}
}
