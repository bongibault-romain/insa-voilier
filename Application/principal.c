
#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"

#include <stdio.h>
#include <stdbool.h>

unsigned short compteur = 0;

int main (void)
{
	GPIO_Enable(GPIOA);
	GPIO_Enable(GPIOB);
	GPIO_Enable(GPIOC);
	
	GPIO_Set_Config(GPIOA, 5, OUTPUT_2MHZ, O_GPO_PUSH_PULL);
	GPIO_Set_Config(GPIOC, 10, OUTPUT_2MHZ, O_GPO_PUSH_PULL);
	
	Timer_Enable(TIM2, 548, 65535);
	Timer_Start(TIM2);
	
	
	/* Tests for GPIO Driver */
	/*
	GPIO_Set_Config(GPIOB, 0, INPUT, I_FLOATING_INPUT);
	GPIO_Set_Config(GPIOB, 1, INPUT, I_ANALOG);
	GPIO_Set_Config(GPIOB, 2, INPUT, I_PULL_UP_PULL_DOWN);
	
	GPIO_Set_Config(GPIOB, 3, OUTPUT_2MHZ, O_GPO_OPEN_DRAIN);
	GPIO_Set_Config(GPIOB, 4, OUTPUT_2MHZ, O_GPO_PUSH_PULL);
	GPIO_Set_Config(GPIOB, 5, OUTPUT_2MHZ, O_ALTERNATE_GPO_OPEN_DRAIN);
	GPIO_Set_Config(GPIOB, 6, OUTPUT_2MHZ, O_ALTERNATE_GPO_PUSH_PULL);
	
	GPIO_Set_Config(GPIOB, 7, OUTPUT_10MHZ, O_GPO_OPEN_DRAIN);
	GPIO_Set_Config(GPIOB, 8, OUTPUT_10MHZ, O_GPO_PUSH_PULL);
	GPIO_Set_Config(GPIOB, 9, OUTPUT_10MHZ, O_ALTERNATE_GPO_OPEN_DRAIN);
	GPIO_Set_Config(GPIOB, 10, OUTPUT_10MHZ, O_ALTERNATE_GPO_PUSH_PULL);
	
	GPIO_Set_Config(GPIOB, 11, OUTPUT_50MHZ, O_GPO_OPEN_DRAIN);
	GPIO_Set_Config(GPIOB, 12, OUTPUT_50MHZ, O_GPO_PUSH_PULL);
	GPIO_Set_Config(GPIOB, 13, OUTPUT_50MHZ, O_ALTERNATE_GPO_OPEN_DRAIN);
	GPIO_Set_Config(GPIOB, 14, OUTPUT_50MHZ, O_ALTERNATE_GPO_PUSH_PULL);
	*/
	
	Timer_Active_IT(TIM2, 1, NULL);
	
	while (1)
	{
		GPIO_Set(GPIOA, 5, GPIO_Get(GPIOC, 13));
		GPIO_Set(GPIOC, 10, GPIO_Get(GPIOC, 8));
		compteur = TIM2->CNT;
	}
}
