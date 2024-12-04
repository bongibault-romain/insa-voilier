#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"
#include "adc.h"
#include "usart.h"
#include "roues.h"
#include "girouette.h"
#include "configuration.h"
#include "battery.h"
#include "sails.h"

#include <stdio.h>
#include <stdbool.h>

int value = 0;

int main (void)
{
	Configure_GPIO();
	
	Wheels_Init(TIM2);
	Sails_Enable(TIM1);
	Girouette_Enable(TIM3);
	Battery_Init(ADC1, 10);
	
	USART_Enable(USART1, READ_WRITE);
	USART_Set_Read_Handler(USART1, Wheels_On_Receive);
			
	char message[64];
	
	while (1)
	{
		// unsigned short battery = Battery_Read();
		
		// sprintf(message, "Batterie: %hu\n", battery);
		
		// USART_Send_String(USART1, message);

		value = Girouette_Get_Angle();
		Sails_Set(value);
		
		//printf("%d\n", value);
	}
	
}
