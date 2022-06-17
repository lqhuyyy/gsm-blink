#ifndef OTHER_H_
#define OTHER_H_

#include <stdint.h>

#define  LED_OFF 		1
#define LED_ON 			2

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

void blink_led(void);

uint8_t power_on(void);

#endif /* OTHER_H_ */
