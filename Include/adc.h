#ifndef CADC_H
#define CADC_H

#include "stm32f10x.h"
#include <stddef.h>
#include <assert.h>

void ADC_Enable(ADC_TypeDef *adc);

unsigned short ADC_Read_Wait(ADC_TypeDef *adc, char channel);

#endif
