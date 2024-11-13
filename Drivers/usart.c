#include "usart.h"

void (*USART1_CALLBACK) (char read_value) = NULL;
void (*USART2_CALLBACK) (char read_value) = NULL;
void (*USART3_CALLBACK) (char read_value) = NULL;

void USART_Enable(USART_TypeDef *usart, enum usart_mode mode) {
	if (usart == USART1) {
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		__NVIC_EnableIRQ(USART1_IRQn);
	}
	
	if (usart == USART2) {
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		__NVIC_EnableIRQ(USART2_IRQn);
	}
	
	if (usart == USART3) {
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		__NVIC_EnableIRQ(USART3_IRQn);
	}
	
	usart->BRR = 0x1D4C;
	usart->CR1 |= USART_CR1_UE;
	usart->CR1 &= ~USART_CR1_M;
	
	if (mode == READ_ONLY || mode == READ_WRITE) {
		usart->CR1 |= USART_CR1_TE;
	}
	
	if (mode == WRITE_ONLY || mode == READ_WRITE) {
		usart->CR1 |= USART_CR1_RE;
	}
	
	usart->CR1 |= USART_CR1_RXNEIE;
	usart->SR &= ~(USART_SR_TC);
}

void USART_Set_Read_Handler(USART_TypeDef *usart, void (*handler) (char read_value)) {
	if (usart == USART1) {
		USART1_CALLBACK = handler;
	}
	
	if (usart == USART2) {
		USART2_CALLBACK = handler;
	}
	
	if (usart == USART3) {
		USART3_CALLBACK = handler;
	}
}

void USART_Send(USART_TypeDef *usart, char value) {
	while (usart->SR & USART_SR_RXNE) { };
	
	usart->DR = value;
	
	while (!(usart->SR & USART_SR_TC));
	
	usart->SR &= ~(USART_SR_TC);
}

void USART1_IRQHandler(void) {
	char value = USART1->DR;
	USART1->SR &= ~USART_SR_RXNE;
	
	if (USART1_CALLBACK != NULL) {
		USART1_CALLBACK(value);
	}
}

void USART2_IRQHandler(void) {
	char value = USART2->DR;
	USART2->SR &= ~USART_SR_RXNE;
	
	if (USART1_CALLBACK != NULL) {
		USART1_CALLBACK(value);
	}
}

void USART3_IRQHandler(void) {
	char value = USART3->DR;
	USART3->SR &= ~USART_SR_RXNE;
	
	if (USART1_CALLBACK != NULL) {
		USART1_CALLBACK(value);
	}
}