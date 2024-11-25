
#include "timer.h"


#include "ecoute.h"
#include "gpio.h"


#define ARR 65535/26
#define MAX 10
#define MIN 20

//MAX = le plus tendu = 90°

void ecoute_enable(){
	GPIO_Enable(GPIOA);
	GPIO_Set_Config(TIM1_CHANNEL_1_GPIO, TIM1_CHANNEL_1_PIN, OUTPUT_2MHZ, O_ALTERNATE_GPO_PUSH_PULL);
	Timer_Enable(TIM1, 548, ARR);
	Timer_Start(TIM1);
	Timer_PWM_Enable(TIM1, TIM_CHANNEL_1, PWM_MODE_1);
	
	
}
//int teta
void ecoute_set(int theta){
	Timer_PWM_Set(TIM1, TIM_CHANNEL_1, (65535/26)/(MIN - (MIN-MAX)*theta/90));
}