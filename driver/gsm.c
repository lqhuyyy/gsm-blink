#include <gsm.h>
#include <systick.h>
#include "log.h"
#include "string.h"
#include "stm32f4xx_rcc.h"

static uint32_t old_ms_received;
static uint32_t _have_new_data = 0;

char data_received[512];
uint32_t data_len;

void USART1_IRQHandler(void) {
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
		// push data to buffer
		char c = USART_ReceiveData(USART1);
		data_received[data_len] = c;
		data_len++;

		// set timeout
		_have_new_data = 1;
		old_ms_received = sys_get_tick_ms();
	}
}

void gsm_uart_init(void) {
	// Lien ket PA9 PA10 voi TX, RX cua UART1
	GPIO_PinAFConfig(GSM_GPIO_PORT, GSM_UART_TX_PinSource, GPIO_AF_USART1);
	GPIO_PinAFConfig(GSM_GPIO_PORT, GSM_UART_RX_PinSource, GPIO_AF_USART1);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin = GSM_UART_TX_PIN | GSM_UART_RX_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GSM_GPIO_PORT, &GPIO_InitStruct);

	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(GSM_USART, &USART_InitStruct);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); // Thiet lap nhom uu tien cho ngat la 1
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; // Kenh ngat la USART1_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // Muc uu tien ngat bang 0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // Thiet lap SubPriority cua ngat bang 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // Xac lap kenh ngat
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(GSM_USART, USART_IT_RXNE, ENABLE);
	USART_Cmd(GSM_USART, ENABLE);

	memset(data_received, 0, sizeof(data_received));
	data_len = 0;
}

void gsm_power_pin_init(void)
{
	// PWRKEY
	GPIO_InitTypeDef GPIO_InitStruct8;
	GPIO_InitStruct8.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct8.GPIO_Pin = GSM_PWR_PIN;
	GPIO_Init(GSM_GPIO_PORT, &GPIO_InitStruct8);

	// STATUS
	GPIO_InitTypeDef GPIO_InitStruct12;
	GPIO_InitStruct12.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct12.GPIO_Pin = GSM_STATUS_PIN;
	GPIO_InitStruct12.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GSM_GPIO_PORT, &GPIO_InitStruct12);
}

uint8_t gsm_get_status(void)
{
	return GPIO_ReadInputDataBit(GSM_GPIO_PORT, GSM_STATUS_PIN);
}

void gsm_pull_down_pwr(void)
{
	GPIO_SetBits(GSM_GPIO_PORT, GSM_PWR_PIN);
}

void gsm_pull_up_pwr(void)
{
	GPIO_ResetBits(GSM_GPIO_PORT, GSM_PWR_PIN);
}

void gsm_send_byte(uint8_t data) {
	USART_SendData(USART1, data);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void gsm_send_str(char* cmd) {

	uint32_t size = strlen(cmd);


	uint32_t i;
	for (i = 0; i < size; i++) {
		send_byte_uart2(cmd[i]);
		gsm_send_byte(cmd[i]);
	}
}

uint32_t gsm_have_new_data(void)
{
	return _have_new_data;
}

uint32_t gsm_get_old_ms_received(void)
{
	return old_ms_received;
}

uint32_t gsm_get_new_data(char *out_buff)
{
	if(_have_new_data) {
		memcpy(out_buff, data_received, data_len);
		_have_new_data = 0;
		return data_len;
	}

	return 0;
}

void gsm_clear_uart_buffer(void)
{
	memset(data_received, 0, sizeof(data_received));
	data_len = 0;
}

