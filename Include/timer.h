#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"

void Timer_Enable(TIM_TypeDef *name, unsigned short psc, unsigned short arr);

void Timer_Start(TIM_TypeDef *name);
void Timer_Stop(TIM_TypeDef *name);

#endif