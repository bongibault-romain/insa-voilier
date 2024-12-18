#ifndef GIROUETTE_H
#define GIROUETTE_H

#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"
#include "adc.h"

void detect_zero_handler(void);

/* Initialisation des broches pour A, B, index 
** et du timer incremental
*/
void Girouette_Enable(TIM_TypeDef * timer);

int Girouette_Get_Angle(void);

#endif
