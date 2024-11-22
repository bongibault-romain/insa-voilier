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
		
	sens_rotation(true);
	rotation(valeur);
	
	
	while (1)
	{
		
	}
	
}

