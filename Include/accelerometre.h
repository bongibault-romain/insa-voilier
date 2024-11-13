#ifndef ACCELEROMETRE_H
#define ACCELEROMETRE_H

#include "stm32f10x.h"
#include "gpio.h"
#include "timer.h"


/********INFO IMPORTANTES********/
/* Utilisation GPIOC 
- broche 0 - index 0
- broche 1 - plaque A
- broche 2 - plaque B
*/

/* Initialisation acc�l�rom�tre
*/
void init_accelerometre();


/* D�tection du z�ro -> interrupt
d�s que nous d�tectons un front montant sur le capteur z�ro (girouette index)
Il faut mettre l'angle � z�ro
*/


/* D�tection de l'angle 
On d�tecte l'angle gr�ce � 2 plaques (A et B) s�par� par un angle de 1/4 angle
Si un front montant est d�tect� en premier sur A, donc on est dans le sens clockwise (positif)
Si un front montant est d�tect� en premier sur B, donc on est dans le sens anti-clockwise (n�gatif)
*/
void detection_angle();


#endif