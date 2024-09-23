#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"

enum timer_name {
	IOPA = RCC_APB2ENR_IOPAEN,
	IOPB = RCC_APB2ENR_IOPBEN,
	IOPC = RCC_APB2ENR_IOPCEN,
	IOPD = RCC_APB2ENR_IOPDEN
};

void Timer_Enable(enum timer_name name);

#endif