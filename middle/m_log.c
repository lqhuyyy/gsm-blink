#include "m_log.h"

unsigned char static m_init = 0;

void log_com3_ln(char* str, uint32_t size)
{
	sprintf(str, "%s\n", str);
	logUART(str, size + 1);
}

void log_com3(char* str, uint32_t size)
{
	logUART(str, size);
}
