#ifndef ROUES_H
#define ROUES_H

#include "stm32f10x.h"

#include <stdbool.h>

void Wheels_Init(TIM_TypeDef * timer);

void Wheels_Set_Rotation_Direction(bool direction);

void Wheels_Rotate(unsigned short valeur);

void Wheels_On_Receive(char value);

#endif
