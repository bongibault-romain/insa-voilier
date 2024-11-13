#ifndef GIROUETTE_H
#define GIROUETTE_H

#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"
#include "adc.h"

/* Initialisation des broches pour A, B, index 
** et du timer incremental
*/
void init_girouette();

void start_count(TIM_TypeDef *timer, GPIO_TypeDef gpio, char broche);


#endif