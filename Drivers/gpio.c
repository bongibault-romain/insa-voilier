#include "gpio.h"

int __GPIO_Get_Number(GPIO_TypeDef *name) {
	if (name == GPIOA) return 2;
	if (name == GPIOB) return 3;
	if (name == GPIOC) return 4;
	if (name == GPIOD) return 5;
	if (name == GPIOE) return 6;
	if (name == GPIOF) return 7;
	if (name == GPIOG) return 8;
	
	return 0;
}

void GPIO_Enable(GPIO_TypeDef *name) {
	RCC->APB2ENR |= 1 << (__GPIO_Get_Number(name));
}

void GPIO_Set_Config(GPIO_TypeDef *name, char port, enum gpio_mode mode, enum gpio_cnf config) {
	/* 
	name : {GPIOA,GPIOB,GPIOC,GPIOD}
	
	port = num de pin : 0 a 15 
	
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
	
	assert(port >= 0 && port < 16);
	// Eviter un mode impossible
	assert(mode != INPUT || config != 3);
	
	// Faire le choix entre le LOW et le HIGH Register 
	 __IO uint32_t *portRegister = &(name->CRL);
	if (port >= 8) {
		portRegister = &(name->CRH);
		port = port - 8;
	}
	
	// Réinitialisation des 4 bits de configuration pour le port
	(*portRegister) &= ~(0b1111 << (4 * port));
	
	// Concatenation des bits de mode et de config
	// Puis application des bits dans la configuration
	(*portRegister) |= (mode + (config << 2)) << (4 * port);
}

void GPIO_Reset_Config(GPIO_TypeDef *name, char port) {
	GPIO_Set_Config(name, port, INPUT, I_FLOATING_INPUT);
}

bool GPIO_Get(GPIO_TypeDef *name, char port) {
	assert(port > 0 && port < 16);
	
	short value = (short) name->IDR;
	
	return (value & (1 << port)) != 0;
}

void GPIO_Set(GPIO_TypeDef *name, char port, bool value) {
	assert(port > 0 && port < 16);
	
	if (value) {
		name->ODR |= 1 << port;
	} else {
		name->ODR &= ~(1 << port);
	}
}

void GPIO_Toggle(GPIO_TypeDef *name, char port) {
	GPIO_Set(name, port, !GPIO_Get(name, port));
}