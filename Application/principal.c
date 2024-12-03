#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"
#include "adc.h"
#include "usart.h"
#include "roues.h"

#include "girouette.h"

#include <stdio.h>
#include <stdbool.h>

unsigned short adc_test = 0;
float value = 0;

void roue_handler(char value) {
	signed char valeur = value;
	
	bool sens = true;
	if (valeur < 0) {
		sens = false;
		valeur = -valeur;
	}
		
	sens_rotation(sens);
	rotation((short) valeur);
}

int main (void)
{
	GPIO_Enable(GPIOA);
	
	GPIO_Set_Config(GPIOA, 9, OUTPUT_2MHZ, O_ALTERNATE_GPO_PUSH_PULL);
	GPIO_Set_Config(GPIOA, 10, INPUT, I_FLOATING_INPUT);
	/*Timer_Enable(TIM1, 548, 65535);*/
	
	USART_Enable(USART1, READ_WRITE);
	USART_Set_Read_Handler(USART1, roue_handler);
	
	Wheels_Init();
	
	roue_handler(0);
	
	ADC_Enable(ADC1);
	*/
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

	GPIO_Enable(GPIOC);
	GPIO_Set_Config(GPIOC, 0, INPUT, I_ANALOG);
	ADC_Enable(ADC1);
	
	char message[64];
	
	setup_girouette();
	while (1)
	{
		unsigned short battery = ADC_Read_Wait(ADC1, 10);
		
		sprintf(message, "Batterie: %hu\n", battery);
		
		USART_Send_String(USART1, message);
		value = convert_to_degrees();
		
		//printf("%d\n", value);
	}
	
}

