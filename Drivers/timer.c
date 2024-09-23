#include "timer.h"

int __Timer_Get_Number(TIM_TypeDef *name) {
	if (name == TIM1) return 11;
	if (name == TIM2) return 0;
	if (name == TIM3) return 1;
	if (name == TIM4) return 2;
	
	return 0;
}

void Timer_Enable(TIM_TypeDef *name) {
	if (name == TIM1) {
		RCC->APB2ENR |= 1 << (__Timer_Get_Number(name));
	} else {
		RCC->APB1ENR |= 1 << (__Timer_Get_Number(name));
	}
}