#ifndef SAILS_H
#define SAILS_H

#define SAILS_ARR 65535/26
#define SAILS_MAX 10
#define SAILS_MIN 20

#include "stm32f10x.h"
#include "timer.h"

void Sails_Enable(TIM_TypeDef * timer);

void Sails_Set(int theta);

#endif