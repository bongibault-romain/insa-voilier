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
int value_firmin = 0;
int battery = 1145;

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
	
	int i = 0;
	
	while (1)
	{
		battery = Battery_Read();
		
		if (i == 1000000) {		
			float voltage = ((float) (battery * 12)) / 1145;
			if (battery <= 1049) {
				sprintf(message, "La batterie est morte. (%.2f V)\n", voltage);
			} else {
				sprintf(message, "La batterie est pas morte. (%.2f V)\n", voltage);
			}
			
			USART_Send_String(USART1, message);
			i = 0;
		}

		value = Girouette_Get_Angle();
		value_firmin = Angle_Giro_To_Angle_Sails(value);
		Sails_Set(value_firmin);
		
		//printf("%d\n", value);
		i++;
	}
	
}
