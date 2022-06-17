#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "stm32f4xx_gpio.h"

/* LED */
#define LED_PIN			GPIO_Pin_4
#define LED_PORT		GPIOB
/* */

/* GSM */
#define GSM_USART					USART1
#define GSM_UART_GPIO_PORT			GPIOA
#define GSM_UART_TX_PIN 			GPIO_Pin_9
#define GSM_UART_RX_PIN 			GPIO_Pin_10
#define GSM_UART_TX_PinSource		GPIO_PinSource9
#define GSM_UART_RX_PinSource		GPIO_PinSource10
/* */

/* LOG */
#define LOG_USART 					USART2
#define LOG_UART_GPIO_PORT 			GPIOA
#define LOG_GPIO_AF					GPIO_AF_USART2
#define LOG_UART_TX_PIN 			GPIO_Pin_2
#define LOG_UART_TX_PinSource 		GPIO_PinSource2
/* */


#endif /* HARDWARE_H_ */
