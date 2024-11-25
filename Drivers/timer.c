#include "timer.h"

// Quatres variables pour stockers les callbacks que doivent appeler chaque interuption
void (*TIM1_UP_CALLBACK) (void) = NULL;
void (*TIM2_UP_CALLBACK) (void) = NULL;
void (*TIM3_UP_CALLBACK) (void) = NULL;
void (*TIM4_UP_CALLBACK) (void) = NULL;

void Timer_Enable(TIM_TypeDef *timer, unsigned short psc, unsigned short arr) {
	if (timer == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if (timer == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if (timer == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if (timer == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	timer->PSC = psc;
	timer->ARR = arr;	
}

void Timer_Start(TIM_TypeDef *timer) {
	timer->CR1 |= TIM_CR1_CEN;
}

void Timer_Stop(TIM_TypeDef *timer) {
	timer->CR1 &= ~TIM_CR1_CEN;
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

void Timer_PWM_Enable(TIM_TypeDef * timer, char channel, char mode) {
	assert(channel == TIM_CHANNEL_1 || channel == TIM_CHANNEL_2 || channel == TIM_CHANNEL_3 || channel == TIM_CHANNEL_4);
	assert(mode == PWM_MODE_1 || mode == PWM_MODE_2);
	
	if (timer == TIM1) {
		timer->BDTR |= TIM_BDTR_MOE;
	}
	
	if (channel == TIM_CHANNEL_1) {
		timer->CCER |= TIM_CCER_CC1E; 

	
	Timer_PWM_Set(TIM2, TIM_CHANNEL_1, 0);		
		if (mode == PWM_MODE_1) timer->CCMR1 &= ~TIM_CCMR1_OC1M_0; // On met le bit le plus à droite à 0 pour mettre la PWM en mode 1
	}
	
	if (channel == TIM_CHANNEL_2) {
		timer->CCER |= TIM_CCER_CC2E;
		timer->CCMR1 |= TIM_CCMR1_OC2M;
		
		if (mode == PWM_MODE_1) timer->CCMR1 &= ~TIM_CCMR1_OC2M_0;
	}
	
	if (channel == TIM_CHANNEL_3) {
		timer->CCER |= TIM_CCER_CC3E;
		timer->CCMR2 |= TIM_CCMR2_OC3M;
		
		if (mode == PWM_MODE_1) timer->CCMR2 &= ~TIM_CCMR2_OC3M_0;
	}
	
	if (channel == TIM_CHANNEL_4) { 
		timer->CCER |= TIM_CCER_CC4E;
		timer->CCMR2 |= TIM_CCMR2_OC4M;
		
		if (mode == PWM_MODE_1) timer->CCMR2 &= ~TIM_CCMR2_OC4M_0;
	}
}

void Timer_PWM_Set(TIM_TypeDef *timer, char channel, unsigned short value) {
	if (channel == TIM_CHANNEL_1) timer->CCR1 = value;
	if (channel == TIM_CHANNEL_2) timer->CCR2 = value;
	if (channel == TIM_CHANNEL_3) timer->CCR3 = value;
	if (channel == TIM_CHANNEL_4) timer->CCR4 = value;
}
