#ifndef M_SIM_H_
#define M_SIM_H_

#include "gsm.h"

#define GSM_POWER_ON    1
#define GSM_POWER_OFF   !GSM_POWER_ON
#define GSM_SEND_CMD	2

typedef enum {
	PWR_GET_STATUS = 0,
	PWR_ON,
	PWR_OFF,
	PWR_ON_STEP_1,
	PWR_ON_STEP_2,
	PWR_WAIT_STATUS_ON,
	PWR_OFF_STEP_1,
	PWR_OFF_STEP_2,
	PWR_WAIT_STATUS_OFF
} gsm_state_t;

void sendCmdSim(char* cmd);

void process_data_receive(void);

void gsm_loop(void);


#endif /* M_SIM_H_ */
