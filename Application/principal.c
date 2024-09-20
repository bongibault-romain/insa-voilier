#include "stm32f10x.h"
#include <stdio.h>
#include <stdbool.h>

void Set_LED2(bool state) {
	if (state) {
		// On met le bit n°5 à 1 pour allumer la LED2
		GPIOA->ODR |= 0x1 << 5;
	} else {
		// On met le bit n°5 à 0 pour eteindre la LED2
		GPIOA->ODR &= ~(0x1 << 5);
	}
}

void Init_LED2() {
	GPIOA->CRL = 0x44244424; // Config à faire dans Keil > Peripherals/GPIO
}

bool Get_Button_B1() {
	// Quand le bouton est pressé, le bit prend la valeur 0 et 1 dans le cas contraire.
	return (GPIOC->IDR & 0x2000) == 0;  // 2 ** 13
}

int main ( void )
{
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4); // 0x11100 -> 28
	
	GPIOA->CRL &= ~(0xF<<4);
	GPIOA->CRL |= (0x2<<4);
	
	Init_LED2();
	
	GPIOC->CRH = 0x44444244;
	
	while (1)
	{
		Set_LED2(Get_Button_B1());
		short test = (GPIOC->IDR & 0b100000000);
		
		if (test == 0) {
		// On met le bit n°5 à 1 pour allumer la LED2
			GPIOC->ODR |= 0x1 << 10;
		} else {
			// On met le bit n°5 à 0 pour eteindre la LED2
			GPIOC->ODR &= ~(0x1 << 10);
				
		}
	}
}
