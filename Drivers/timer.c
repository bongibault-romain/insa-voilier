#include "timer.h"

void Timer_Enable(enum timer_name name) {
	RCC->APB2ENR |= name;
}