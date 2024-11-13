#include "accelerometre.h"

void init_accelerometre(){
	
	// initialisation du GPIO
	GPIO_Enable(GPIOC);
	
	// broche index zéro 
	GPIO_Set_Config(GPIOC, 0, OUTPUT_2MHZ, O_GPO_PUSH_PULL);
	// broche plaque A
	GPIO_Set_Config(GPIOC, 1, OUTPUT_2MHZ, O_GPO_PUSH_PULL);
	// broche plaque B
	GPIO_Set_Config(GPIOC, 2, OUTPUT_2MHZ, O_GPO_PUSH_PULL);
	
	// Timer enable 
	Timer_Enable(TIM2, 548, 65535);

}

