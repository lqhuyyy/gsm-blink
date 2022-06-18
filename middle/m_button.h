#ifndef M_BUTTON_H_
#define M_BUTTON_H_

#include "button.h"
#include "systick.h"

typedef enum {
	NO_CLICK = 0,
	PENDING_CLICK,
	CLICK,
	PENDING_LONG_CLICK,
	LONG_CLICK
} btn_state_t;

#define LONG_CLICK_THRESH_HOLD 		1000

btn_state_t handle_button_loop(void);

#endif /* M_BUTTON_H_ */
