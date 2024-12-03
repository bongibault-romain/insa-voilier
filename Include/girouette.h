#ifndef GIROUETTE_H
#define GIROUETTE_H

#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"
#include "adc.h"

void detect_zero_handler();

/* Initialisation des broches pour A, B, index 
** et du timer incremental
*/
void setup_girouette();

float convert_to_degrees();
#endif