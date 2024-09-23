#ifndef GPIO_H
#define GPIO_H

#include "stm32f10x.h"

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

// See: Le manuel de référence STM32 (RM0008) 
// | 9.2.1 Port configuration register low (GPIOx_CRL) (x=A..G) 
// | 9.2.2 Port configuration register high (GPIOx_CRH) (x=A..G)

<<<<<<< HEAD
enum gpio_type {
	GPIO_A = 2,
	GPIO_B = 3,
	GPIO_C = 4,
	GPIO_D = 5
};

=======
>>>>>>> a3b4b952d10df0183022d0b2eab47d0d4fd2bcc4
enum gpio_mode {
	INPUT = 0,
	OUTPUT_10MHZ = 1,
	OUTPUT_2MHZ = 2,
	OUTPUT_50MHZ = 3
};

enum gpio_cnf {
	I_ANALOG = 0,
	I_FLOATING_INPUT = 1,
	I_PULL_UP_PULL_DOWN = 2,
	
	O_GPO_PUSH_PULL = 0,
	O_GPO_OPEN_DRAIN = 1,
	O_ALTERNATE_GPO_PUSH_PULL = 2,
	O_ALTERNATE_GPO_OPEN_DRAIN = 3,
};

void GPIO_Enable(GPIO_TypeDef *name);

void GPIO_Set_Config(GPIO_TypeDef *name, char port, enum gpio_mode mode, enum gpio_cnf config);
void GPIO_Reset_Config(GPIO_TypeDef *name, char port);

bool GPIO_Get(GPIO_TypeDef *name, char port);
void GPIO_Set(GPIO_TypeDef *name, char port, bool value);
void GPIO_Toggle(GPIO_TypeDef *name, char port);


#endif