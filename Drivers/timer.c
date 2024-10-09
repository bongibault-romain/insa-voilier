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
	name->CR1 |= TIM_CR1_CEN;
}

void Timer_Stop(TIM_TypeDef *name) {
	name->CR1 &= ~TIM_CR1_CEN;
}

void Timer_Active_IT(TIM_TypeDef *timer, uint32_t priority) {
	timer->DIER |= TIM_DIER_UIE; // Active interuption dans la carte
	
	if (timer == TIM1) {
		__NVIC_SetPriority(TIM1_UP_IRQn, priority);
		__NVIC_EnableIRQ(TIM2_IRQn); // Enable interuption in cortex
	}
	
	if (timer == TIM2) {
		__NVIC_SetPriority(TIM2_IRQn, priority);
		__NVIC_EnableIRQ(TIM2_IRQn); // Enable interuption in cortex
	}
	
	
	if (timer == TIM3) {
		__NVIC_SetPriority(TIM3_IRQn, priority);
		__NVIC_EnableIRQ(TIM3_IRQn); // Enable interuption in cortex
	}
	
	if (timer == TIM4) {
		__NVIC_SetPriority(TIM4_IRQn, priority);
		__NVIC_EnableIRQ(TIM4_IRQn); // Enable interuption in cortex
	}
}

void TIM1_UP_IRQHandler() {
	
}

void TIM2_IRQHandler() {
	TIM2->SR &= ~0b1;
	return;
}

void TIM3_IRQHander() {

}

void TIM4_IRQHandler() {

}




void MyTimer_PWM(TIM_TypeDef * Timer, char Channel){
		Timer->CCER |= 1;
	
}




