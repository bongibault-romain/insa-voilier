
#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"
#include "adc.h"

#include <stdio.h>
#include <stdbool.h>

short value = 0;

void test1() {
	return;
}

int main (void)
{
	GPIO_Enable(GPIOA);
	GPIO_Enable(GPIOB);
	GPIO_Enable(GPIOC);
	
	float valeur = 50.0;
		// set GPIO
	GPIO_Set_Config(GPIOB, 0, OUTPUT_2MHZ, O_GPO_PUSH_PULL); //Plateau Dir
	
	// check if value + or - for direction
//	if (valeur<0) {
//		GPIO_Set(GPIOB, 0, true);
//	}
//	else{
//		GPIO_Set(GPIOB, 0, false);
//	}
	
	GPIO_Set_Config(TIM2_CHANNEL_1_GPIO, TIM2_CHANNEL_1_PIN, OUTPUT_2MHZ, O_ALTERNATE_GPO_PUSH_PULL); //Plateau PWM
	
	Timer_Enable(TIM2, 548, 65535);
	Timer_Start(TIM2);
	Timer_PWM_Enable(TIM2, TIM_CHANNEL_1, PWM_MODE_2);
	
		Timer_PWM_Set(TIM2, TIM_CHANNEL_1, valeur);
	
	
	while (1)
	{
	}
	
}

