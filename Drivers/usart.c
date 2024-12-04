#include "usart.h"

void (*USART1_CALLBACK) (char read_value) = NULL;
void (*USART2_CALLBACK) (char read_value) = NULL;
void (*USART3_CALLBACK) (char read_value) = NULL;

void USART_Enable(USART_TypeDef *usart, enum usart_mode mode) {
	if (usart == USART1) {
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // config clock
		__NVIC_EnableIRQ(USART1_IRQn); // enable clock
		usart->BRR = FREQ_CLOCK_APB2/FREQ_USART_BAUD; // fix the baud rate = nb de symboles par sec 
	}
	
	if (usart == USART2) {
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
		__NVIC_EnableIRQ(USART2_IRQn);
		usart->BRR = FREQ_CLOCK_APB1/FREQ_USART_BAUD;
	}
	
	if (usart == USART3) {
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		__NVIC_EnableIRQ(USART3_IRQn);
		usart->BRR = FREQ_CLOCK_APB1/FREQ_USART_BAUD;
	}
	
	usart->CR1 |= USART_CR1_UE; // usart enable
	usart->CR1 &= ~USART_CR1_M; // facultatif : message to 8 bytes
	
	if (mode == READ_ONLY || mode == READ_WRITE) { // mode read
		usart->CR1 |= USART_CR1_RE; // enable reception
	}
	
	if (mode == WRITE_ONLY || mode == READ_WRITE) { // mode write
		usart->CR1 |= USART_CR1_TE; // enable transmission
	}
	
	usart->CR1 |= USART_CR1_RXNEIE; // enable interrupts for reception
	usart->SR &= ~(USART_SR_TC); // transmission precedente a ete completee  
}

void USART_Set_Read_Handler(USART_TypeDef *usart, void (*handler) (char read_value)) {
	if (usart == USART1) {
		USART1_CALLBACK = handler; // interrupt handler
	}
	
	if (usart == USART2) {
		USART2_CALLBACK = handler;
	}
	
	if (usart == USART3) {
		USART3_CALLBACK = handler;
	}
}

void USART_Send(USART_TypeDef *usart, char value) { // send interrupt 
	while (!(usart->SR & USART_SR_TXE)) { }; // while previous transmission not finished
	
	usart->DR = value; // data register updated with value to send
	
	while (!(usart->SR & USART_SR_TC)); // while value not sent
	
	usart->SR &= ~(USART_SR_TC); // transmission not done
}

void USART_Send_String(USART_TypeDef *usart, const char *str) {
	int i = 0;
	
	while (str[i] != '\0') {
		USART_Send(usart, str[i]);
		i++;
	}
}

void USART1_IRQHandler(void) { // receive handler for usart1
	char value = USART1->DR;  
	USART1->SR &= ~USART_SR_RXNE;
	
	if (USART1_CALLBACK != NULL) {
		USART1_CALLBACK(value);
	}
}

void USART2_IRQHandler(void) { // receive handler for usart2
	char value = USART2->DR;
	USART2->SR &= ~USART_SR_RXNE;
	
	if (USART2_CALLBACK != NULL) {
		USART2_CALLBACK(value);
	}
}

void USART3_IRQHandler(void) { // receive handler for usart3
	char value = USART3->DR;
	USART3->SR &= ~USART_SR_RXNE;
	
	if (USART3_CALLBACK != NULL) {
		USART3_CALLBACK(value);
	}
}