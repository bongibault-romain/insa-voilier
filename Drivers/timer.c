#include "timer.h"

void Timer_Enable(TIM_TypeDef *name, unsigned short psc, unsigned short arr) {
	if (name == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if (name == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if (name == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if (name == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	name->PSC = psc;
	name->ARR = arr;	
}


void Timer_Start(TIM_TypeDef *name) {
	name->CR1 |= 1;
}

void Timer_Stop(TIM_TypeDef *name) {
	name->CR1 &= ~(1);
}