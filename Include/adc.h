#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"
#include <stddef.h>
#include <assert.h>

void ADC_Enable(ADC_TypeDef *adc);

short ADC_Read_Wait(ADC_TypeDef *adc);

#endif