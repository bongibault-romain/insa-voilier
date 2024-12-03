#include "configuration.h"

#include "gpio.h"

void Configure_GPIO(void) {
	GPIO_Enable(GPIOA);
	GPIO_Enable(GPIOB); 
	GPIO_Enable(GPIOC);

    // GPIO For USART1
	GPIO_Set_Config(GPIOA, 9, OUTPUT_2MHZ, O_ALTERNATE_GPO_PUSH_PULL);
	GPIO_Set_Config(GPIOA, 10, INPUT, I_FLOATING_INPUT);

    // GPIO For Wheels
	// Plateau Dir  
	GPIO_Set_Config(GPIOB, 0, OUTPUT_2MHZ, O_GPO_PUSH_PULL); 
    // Plateau PWM
	GPIO_Set_Config(TIM2_CHANNEL_1_GPIO, TIM2_CHANNEL_1_PIN, OUTPUT_2MHZ, O_ALTERNATE_GPO_PUSH_PULL);

    // GPIO For Battery
	GPIO_Set_Config(GPIOC, 0, INPUT, I_ANALOG);

    // GPIO For Girouette
	// phase A : A6
	GPIO_Set_Config(GPIOA, 6, INPUT, I_FLOATING_INPUT);
	
	// phase B : A7
	GPIO_Set_Config(GPIOA, 7, INPUT, I_FLOATING_INPUT);
	
	// phase index : B0
	GPIO_Set_Config(GPIOA, 0, INPUT, I_FLOATING_INPUT);
}