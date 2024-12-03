#include "sails.h"
#include "stm32f10x.h"

static TIM_TypeDef * sails_timer = NULL;
//SAILS_MAX = le plus tendu = 90�

void Sails_Enable(TIM_TypeDef * timer) {
    sails_timer = timer;
	Timer_Enable(timer, 548, SAILS_ARR);
	Timer_Start(timer);
	Timer_PWM_Enable(timer, TIM_CHANNEL_1, PWM_MODE_1);
}
//int teta
void Sails_Set(int theta){
	Timer_PWM_Set(sails_timer, TIM_CHANNEL_1, (65535/26)/(SAILS_MIN - (SAILS_MIN-SAILS_MAX)*theta/90));
}