#ifndef BATTERY_H
#define BATTERY_H

#include "stm32f10x.h"

void Battery_Init(ADC_TypeDef * adc, char channel);

int Battery_Read(void);

#endif
