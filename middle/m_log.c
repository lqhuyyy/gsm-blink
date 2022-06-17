#include "m_log.h"

unsigned char static m_init = 0;

void log_uart(char* str, uint32_t size)
{
	logUART(str, size);
}
