
#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"
#include "adc.h"
#include "roues.h"

#include <stdio.h>
#include <stdbool.h>

short value = 0;

int main (void)
{
	GPIO_Enable(GPIOA);
	
	unsigned short valeur = 50;
		
	//sens_rotation(valeur);
	GPIO_Set_Config(TIM2_CHANNEL_1_GPIO, TIM2_CHANNEL_1_PIN, OUTPUT_2MHZ, O_ALTERNATE_GPO_PUSH_PULL); //Plateau PWM
	Timer_Enable(TIM2, 548, 65535);
	Timer_PWM_Enable(TIM2, TIM_CHANNEL_1, PWM_MODE_2);
	Timer_PWM_Set(TIM2, TIM_CHANNEL_1, 65535/2);
	Timer_Start(TIM2);
	
	
	while (1)
	{
		
	}
	
}

