
#include "stm32f10x.h"
#include "gpio.h"
#include <stdio.h>
#include <stdbool.h>

int main ( void )
{
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4); // 0x11100 -> 28
	
	GPIOA->CRL &= ~(0xF<<4);
	GPIOA->CRL |= (0x2<<4);
	
	GPIO_Set_Config(GPIOA, 5, OUTPUT_2MHZ, O_GPO_PUSH_PULL);
	GPIO_Set_Config(GPIOC, 10, OUTPUT_2MHZ, O_GPO_PUSH_PULL);
	
	while (1)
	{
		GPIO_Set(GPIOA, 5, GPIO_Get(GPIOC, 13));
		GPIO_Set(GPIOC, 10, GPIO_Get(GPIOC, 8));
	}
}
