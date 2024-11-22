#include "roues.h"
#include "gpio.h"
#include "timer.h"

void sens_rotation(bool sens){
	
	// set GPIO
	GPIO_Enable(GPIOB); 
	GPIO_Set_Config(GPIOB, 0, OUTPUT_2MHZ, O_GPO_PUSH_PULL); //Plateau Dir
	
	// check if value + or - for direction
	if (sens==true) {
		GPIO_Set(GPIOB, 0, true);
	}
	else{
		GPIO_Set(GPIOB, 0, false);
	}
	
};

void rotation(unsigned short valeur){
	
	GPIO_Enable(GPIOA);
	GPIO_Set_Config(TIM2_CHANNEL_1_GPIO, TIM2_CHANNEL_1_PIN, OUTPUT_2MHZ, O_ALTERNATE_GPO_PUSH_PULL); //Plateau PWM
	Timer_Enable(TIM2, 35, 140);
	Timer_PWM_Enable(TIM2, TIM_CHANNEL_1, PWM_MODE_2);
	Timer_PWM_Set(TIM2, TIM_CHANNEL_1, (140*valeur)/100);
	Timer_Start(TIM2);
	
}

