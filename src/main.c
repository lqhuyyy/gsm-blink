#include <m_hal_init.h>
#include "string.h"

#include "m_log.h"
#include "m_sim.h"
#include "other.h"

int main(void) {
	hal_init();

	log_uart("test uart\n", strlen("test uart\n"));

//	sendCmdSim("AT+CICCID=?\r");

	while (1) {
//		process_data();
		blink_led();
	}
}
