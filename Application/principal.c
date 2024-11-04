
#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"
#include "adc.h"

#include <stdio.h>
#include <stdbool.h>
#include <time.h> 
void test1() {
	return;
}

int main (void)
{
	GPIO_Enable(GPIOB);
	int arr=65535;
	GPIO_Set_Config(TIM1_CHANNEL_1_GPIO, TIM1_CHANNEL_1_PIN, OUTPUT_2MHZ, O_ALTERNATE_GPO_PUSH_PULL); // GPIO_Set_Config(GPIO_TypeDef *name, char pin, enum gpio_mode mode, enum gpio_cnf config)
	
	Timer_Enable(TIM1, 548, arr); //Timer_Enable(TIM_TypeDef *timer, unsigned short psc, unsigned short arr)
	Timer_Start(TIM1); // Timer_Start(TIM_TypeDef *timer)
	
	
	Timer_PWM_Enable(TIM1, TIM_CHANNEL_1, PWM_MODE_1); //Timer_PWM_Enable(TIM_TypeDef * timer, char channel, char mode)
	Timer_PWM_Set(TIM1, TIM_CHANNEL_1, (arr+1)/11); // Timer_PWM_Set(TIM_TypeDef *timer, char channel, unsigned short value)
	
	
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
	int i = 0;
	while (1)
	{
		for (int i = 0; i < 2147483647;i++){}
		Timer_PWM_Set(TIM1, TIM_CHANNEL_1, (arr+1)/(10+i));
		i=(i+1)%10;
	}
		
}

