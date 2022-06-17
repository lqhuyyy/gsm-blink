#include <gsm.h>
#include <systick.h>
#include "m_sim.h"

#include "squeue.h"
#include "log.h"

static uint32_t old_ms_tick;
static sq_t queue_data;

void sendCmdSim(char* cmd)
{
	gsm_send_str(cmd);
}

void process_data(void)
{
	if(gsm_have_new_data() && sys_get_tick_ms() - gsm_get_old_ms_received() > 50)
	{
		char data_received[512];
		uint32_t data_len = gsm_get_new_data(data_received);
		sq_push(&queue_data, data_received);
		gsm_clear_uart_buffer();
		logUART(data_received, data_len);
	}

	if(!sq_is_empty(&queue_data)){

	}

}
