#include "girouette.h"

int count_interrupt = 0;

void detect_zero_handler(){
		TIM3->CNT = 0;
}

void EXTI0_IRQHandler(void){
	if(EXTI->PR & EXTI_PR_PR0){
		EXTI->PR |= EXTI_PR_PR0; // reset pr flag
		detect_zero_handler();
		count_interrupt ++;
	}
}

/* Initialisation des broches pour A, B, index 
** et du timer incremental
*/
void setup_girouette(){
	
	GPIO_TypeDef * gpio = GPIOA;
	TIM_TypeDef * timer = TIM3;
	
	// phase A : A6
	GPIO_Set_Config(gpio, 6, INPUT, I_FLOATING_INPUT);
	
	// phase B : A7
	GPIO_Set_Config(gpio, 7, INPUT, I_FLOATING_INPUT);
	
	// phase index : B0
	GPIO_Set_Config(GPIOB, 0, INPUT, I_FLOATING_INPUT);
	
	// timer incremental (timer, PSC, ARR)
	// ARR max value : (360*4) turns on B including 360 turns on A and 360 = 0
	Timer_Enable(timer, 0, ((360*4)-1));
	
	// phase A : config Channel 1 CC1S to Input
	timer->CCMR1 &= ~TIM_CCMR1_CC1S;
	timer->CCMR1 |= TIM_CCMR1_CC1S;
	
	// phase A : flag CC1E enabled
	timer->CCER &= ~TIM_CCER_CC1E;
	timer->CCER |= TIM_CCER_CC1E;
	
	// phase B : config Channel 2 CC2S to Input
	timer->CCMR1 &= ~TIM_CCMR1_CC2S;
	timer->CCMR1 |= TIM_CCMR1_CC2S;
	
	// phase B : flag CC2E enabled
	timer->CCER &= ~TIM_CCER_CC2E;
	timer->CCER |= TIM_CCER_CC2E;
	
	// set timer to encoder interface mode
	// from datasheet : SMS=011 if it is counting on both TI1 and TI2 edges.
	timer->SMCR &= ~TIM_SMCR_SMS; // reset
	timer->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1; // set to mode 3 : 011
	
	// non-inverting polarity for TI1, TI2
	timer->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);
	
	// enable counter : CEN = 1
	timer->CR1 |= TIM_CR1_CEN; 
	
	// enable external interrupt 
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB; // chosen b0
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->RTSR |= EXTI_RTSR_TR0; // authorise interruption on front montant
	
	// activate external interrupt 
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 10);
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	Timer_Start(timer);
}

float convert_to_degrees(){
	return (TIM3->CNT/4);
}
