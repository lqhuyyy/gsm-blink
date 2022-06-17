#include "log.h"


void log_init(void)
{
	// Lien ket PA2 PA3 voi TX cua UART2
	GPIO_PinAFConfig(LOG_UART_GPIO_PORT, LOG_UART_TX_PinSource, LOG_GPIO_AF);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin = LOG_UART_TX_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(LOG_UART_GPIO_PORT, &GPIO_InitStruct);

	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_Mode = USART_Mode_Tx;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(LOG_USART, &USART_InitStruct);

	USART_Cmd(LOG_USART, ENABLE);
}

void send_byte_uart2(uint8_t c)
{
	USART_SendData(LOG_USART, c);
	while(USART_GetFlagStatus(LOG_USART, USART_FLAG_TXE) == RESET);
}

void logUART(char* str, uint32_t size)
{
	uint32_t i;
	for(i = 0; i < size; i++){
		send_byte_uart2(str[i]);
	}
}

