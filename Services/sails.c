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
	Timer_PWM_Set(sails_timer, TIM_CHANNEL_1, (unsigned short) ((65535/26)/(SAILS_MIN - (SAILS_MIN-SAILS_MAX)*theta/90)));
}

int Angle_Giro_To_Angle_Sails (int theta_girouette){
	int theta = 0;
	if (theta_girouette > 45){
		theta = ((90/135)*theta_girouette) - 30;
	}
	return theta;
}
