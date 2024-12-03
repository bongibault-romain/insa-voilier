#include "roues.h"
#include "gpio.h"
#include "timer.h"

static TIM_TypeDef * wheels_timer = NULL;

void Wheels_Init(TIM_TypeDef * timer) {
	wheels_timer = timer;

	Timer_Enable(timer, 35, 140);
	Timer_PWM_Set(timer, TIM_CHANNEL_1, 1);
	Timer_PWM_Enable(timer, TIM_CHANNEL_1, PWM_MODE_1);
	Timer_Start(timer);
}

void Wheels_Set_Rotation_Direction(bool direction) {
	GPIO_Set(GPIOB, 0, sens);
}

void Wheels_Rotate(unsigned short valeur){
	Timer_PWM_Set(wheels_timer, TIM_CHANNEL_1, (140*valeur)/100);
}

void Wheels_On_Receive(char value) {
	signed char valeur = value;
	
	bool sens = true;
	if (valeur < 0) {
		sens = false;
		valeur = -valeur;
	}
		
	Wheels_Set_Rotation_Direction(sens);
	Wheels_Rotate((short) valeur);
}