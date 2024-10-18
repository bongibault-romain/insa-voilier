#include "gpio.h"

void GPIO_Enable(GPIO_TypeDef *name) {
	if (name == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	if (name == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	if (name == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	if (name == GPIOD) RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
}

void GPIO_Set_Config(GPIO_TypeDef *name, char pin, enum gpio_mode mode, enum gpio_cnf config) {
	/* 
	name : {GPIOA,GPIOB,GPIOC,GPIOD}
	
	pin = num de pin : 0 a 15 
	
	mode = type custom : {INPUT = 0,
	OUTPUT_10MHZ = 1,
	OUTPUT_2MHZ = 2,
	OUTPUT_50MHZ = 3
	}
	
	config = type custom : {
	I_ANALOG = 0,
	I_FLOATING_INPUT = 1,
	I_PULL_UP_PULL_DOWN = 2,
	
	O_GPO_PUSH_PULL = 0,
	O_GPO_OPEN_DRAIN = 1,
	O_ALTERNATE_GPO_PUSH_PULL = 2,
	O_ALTERNATE_GPO_OPEN_DRAIN = 3,
	}	
	*/
	
	assert(pin >= 0 && pin < 16);
	// Eviter un mode impossible
	assert(mode != INPUT || config != 3);
	
	// Faire le choix entre le LOW et le HIGH Register 
	 __IO uint32_t *pinRegister = &(name->CRL);
	if (pin >= 8) {
		pinRegister = &(name->CRH);
		pin = pin - 8;
	}
	
	// Réinitialisation des 4 bits de configuration pour le pin
	(*pinRegister) &= ~(0b1111 << (4 * pin));
	
	// Concatenation des bits de mode et de config
	// Puis application des bits dans la configuration
	(*pinRegister) |= (mode + (config << 2)) << (4 * pin);
}

void GPIO_Reset_Config(GPIO_TypeDef *name, char pin) {
	GPIO_Set_Config(name, pin, INPUT, I_FLOATING_INPUT);
}

bool GPIO_Get(GPIO_TypeDef *name, char pin) {
	assert(pin > 0 && pin < 16);
	
	short value = (short) name->IDR;
	
	return (value & (1 << pin)) != 0;
}

void GPIO_Set(GPIO_TypeDef *name, char pin, bool value) {
	assert(pin > 0 && pin < 16);
	
	if (value) {
		name->ODR |= 1 << pin;
	} else {
		name->ODR &= ~(1 << pin);
	}
}

void GPIO_Toggle(GPIO_TypeDef *name, char pin) {
	GPIO_Set(name, pin, !GPIO_Get(name, pin));
}