#ifndef UART_H
#define UART_H

#include "stm32f10x.h"
#include <stddef.h>
#include <assert.h>

#define FREQ_USART_BAUD  	9600
#define FREQ_CLOCK_APB1		36000000u
#define FREQ_CLOCK_APB2 	72000000u

enum usart_mode {
	READ_ONLY,
	WRITE_ONLY,
	READ_WRITE
};

void USART_Enable(USART_TypeDef *usart, enum usart_mode mode);

void USART_Set_Read_Handler(USART_TypeDef *usart, void (*handler) (char read_value));

void USART_Send(USART_TypeDef *usart, char value);

#endif