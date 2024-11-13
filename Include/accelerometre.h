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

/* Initialisation accéléromètre
*/
void init_accelerometre();


/* Détection du zéro -> interrupt
dès que nous détectons un front montant sur le capteur zéro (girouette index)
Il faut mettre l'angle à zéro
*/


/* Détection de l'angle 
On détecte l'angle grâce à 2 plaques (A et B) séparé par un angle de 1/4 angle
Si un front montant est détecté en premier sur A, donc on est dans le sens clockwise (positif)
Si un front montant est détecté en premier sur B, donc on est dans le sens anti-clockwise (négatif)
*/
void detection_angle();


#endif