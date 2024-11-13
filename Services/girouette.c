#include "girouette.h"

/* Initialisation des broches pour A, B, index 
** et du timer incremental
*/
void init_girouette(){
	
	GPIO_TypeDef * gpio = GPIOA;
	TIM_TypeDef * timer = TIM3;
	
	// phase A : A6
	GPIO_Set_Config(gpio, 6, INPUT, I_FLOATING_INPUT);
	
	// phase B : A7
	GPIO_Set_Config(gpio, 7, INPUT, I_FLOATING_INPUT);
	
	// phase index
	//GPIO_Set_Config(gpio, 2, INPUT, I_FLOATING_INPUT);
	
	// timer incremental (timer, PSC, ARR)
	// ARR max value : (360*4) turns on B including 360 turns on A
	Timer_Enable(timer, 0, 360*4);
	
	Timer_PWM_Enable(timer, 1, PWM_MODE_1); // pwm mode encode
	Timer_PWM_Enable(timer, 2, PWM_MODE_1);
	
	// set timer to encoder interface mode
	// from datasheet : SMS=011 if it is counting on both TI1 and TI2 edges.
	timer->SMCR &= ~TIM_SMCR_SMS;
	timer->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; // set to mode 3 : 011
	
	// non-inverting polarity for TI1, TI2
	timer->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
	
	// enable counter : CEN = 1
	timer->CR1 |= TIM_CR1_CEN;
}

void start_count(TIM_TypeDef *timer, GPIO_TypeDef gpio, char broche){
	Timer_Start(timer);
	
}
