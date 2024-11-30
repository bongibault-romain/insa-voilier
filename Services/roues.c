#include "roues.h"
#include "gpio.h"
#include "timer.h"

void Wheels_Init(void) {
	// set GPIO
	GPIO_Enable(GPIOB); 
	GPIO_Enable(GPIOA);
	
	GPIO_Set_Config(GPIOB, 0, OUTPUT_2MHZ, O_GPO_PUSH_PULL); //Plateau Dir
	GPIO_Set_Config(TIM2_CHANNEL_1_GPIO, TIM2_CHANNEL_1_PIN, OUTPUT_2MHZ, O_ALTERNATE_GPO_PUSH_PULL); //Plateau PWM
	
	Timer_Enable(TIM2, 35, 140);
	Timer_PWM_Set(TIM2, TIM_CHANNEL_1, 1);
	Timer_PWM_Enable(TIM2, TIM_CHANNEL_1, PWM_MODE_1);
	Timer_Start(TIM2);
}

void sens_rotation(bool sens){
	// check if value + or - for direction
	GPIO_Set(GPIOB, 0, sens);
}

void rotation(unsigned short valeur){
	Timer_PWM_Set(TIM2, TIM_CHANNEL_1, (140*valeur)/100);
}

