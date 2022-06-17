#ifndef _LOG_H_
#define _LOG_H_

#include "stm32f4xx.h"
#include "hardware.h"

void log_init(void);

void send_byte_uart2(uint8_t c);

void logUART(char* str, uint32_t size);

#endif
