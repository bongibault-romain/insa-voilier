#include "gpio.h"

void GPIO_Set_Config(GPIO_TypeDef *name, int port, enum gpio_mode mode, enum gpio_cnf config) {
	assert(port >= 0 && port < 16);
	
	 __IO uint32_t *portRegister = &(name->CRL);
	
	if (port >= 8) {
		portRegister = &(name->CRH);
		port = port - 8;
	}
	
	(*portRegister) &= ~(15 << (4 * port));
	(*portRegister) |= (mode + (config << 2)) << (4 * port);
}

void GPIO_Reset_Config(GPIO_TypeDef *name, int port) {
	GPIO_Set_Config(name, port, INPUT, I_FLOATING_INPUT);
}

bool GPIO_Get(GPIO_TypeDef *name, int port) {
	assert(port > 0 && port < 16);
	
	short value = (short) name->IDR;
	
	return (value & (1 << port)) != 0;
}

void GPIO_Set(GPIO_TypeDef *name, int port, bool value) {
	assert(port > 0 && port < 16);
	
	if (value) {
		name->ODR |= 1 << port;
	} else {
		name->ODR &= ~(1 << port);
	}
}