#include "timer.h"

// Quatres variables pour stockers les callbacks que doivent appeler chaque interuption
void (*TIM1_UP_CALLBACK) (void) = NULL;
void (*TIM2_UP_CALLBACK) (void) = NULL;
void (*TIM3_UP_CALLBACK) (void) = NULL;
void (*TIM4_UP_CALLBACK) (void) = NULL;

void Timer_Enable(TIM_TypeDef *name, unsigned short psc, unsigned short arr) {
	if (name == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if (name == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if (name == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if (name == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	name->PSC = psc;
	name->ARR = arr;	
}

void Timer_Start(TIM_TypeDef *name) {
	name->CR1 |= TIM_CR1_CEN;
}

void Timer_Stop(TIM_TypeDef *name) {
	name->CR1 &= ~TIM_CR1_CEN;
}

void Timer_Active_IT(TIM_TypeDef *timer, uint32_t priority, void (*callback) (void)) {
	timer->DIER |= TIM_DIER_UIE; // Active interuption dans la carte
	
	if (timer == TIM1) {
		TIM1_UP_CALLBACK = callback;
		__NVIC_SetPriority(TIM1_UP_IRQn, priority);
		__NVIC_EnableIRQ(TIM1_UP_IRQn); // Enable interuption in cortex
	}
	
	if (timer == TIM2) {
		TIM2_UP_CALLBACK = callback;
		__NVIC_SetPriority(TIM2_IRQn, priority);
		__NVIC_EnableIRQ(TIM2_IRQn); // Enable interuption in cortex
	}
	
	if (timer == TIM3) {
		TIM3_UP_CALLBACK = callback;
		__NVIC_SetPriority(TIM3_IRQn, priority);
		__NVIC_EnableIRQ(TIM3_IRQn); // Enable interuption in cortex
	}
	
	if (timer == TIM4) {
		TIM4_UP_CALLBACK = callback;
		__NVIC_SetPriority(TIM4_IRQn, priority);
		__NVIC_EnableIRQ(TIM4_IRQn); // Enable interuption in cortex
	}
}

void TIM1_UP_IRQHandler() {
	if (TIM1->SR & TIM_SR_UIF) { // Si c'est une UPDATE Interuption
		if (TIM1_UP_CALLBACK != NULL) TIM1_UP_CALLBACK();
		
		TIM1->SR &= ~TIM_SR_UIF;
	}
}

void TIM2_IRQHandler() {
	if (TIM2->SR & TIM_SR_UIF) { // Si c'est une UPDATE Interuption
		if (TIM2_UP_CALLBACK != NULL) TIM2_UP_CALLBACK();
		
		TIM2->SR &= ~TIM_SR_UIF;
	}
	return;
}

void TIM3_IRQHandler() {
	if (TIM3->SR & TIM_SR_UIF) { // Si c'est une UPDATE Interuption
		if (TIM3_UP_CALLBACK != NULL) TIM3_UP_CALLBACK();
		
		TIM3->SR &= ~TIM_SR_UIF;
	}
}

void TIM4_IRQHandler() {
	if (TIM4->SR & TIM_SR_UIF) { // Si c'est une UPDATE Interuption
		if (TIM4_UP_CALLBACK != NULL) TIM4_UP_CALLBACK();
		
		TIM4->SR &= ~TIM_SR_UIF;
	}
}


