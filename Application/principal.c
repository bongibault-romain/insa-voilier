#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"
#include "adc.h"
#include "usart.h"
#include "roues.h"
#include "girouette.h"
#include "configuration.h"
#include "battery.h"

#include <stdio.h>
#include <stdbool.h>

unsigned short adc_test = 0;
int value = 0;

int main (void)
{
	Configure_GPIO();
	
	USART_Enable(USART1, READ_WRITE);
	USART_Set_Read_Handler(USART1, Wheels_On_Receive);
	
	Wheels_Init(TIM2);
	Girouette_Enable(TIM3);
	Battery_Init(ADC1, 10);
			
	char message[64];
	
	while (1)
	{
		unsigned short battery = Battery_Read();
		
		sprintf(message, "Batterie: %hu\n", battery);
		
		USART_Send_String(USART1, message);
		value = Girouette_Get_Angle();
		
		//printf("%d\n", value);
	}
	
}

