#ifndef TIMER_H
#define TIMER_H

/*
* 110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
* else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0’) as long as
* TIMx_CNT>TIMx_CCR1 else active (OC1REF=’1’).
* 111: PWM mode 2 - In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1
* else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else
* inactive.
*/
#define PWM_MODE_1 0
#define PWM_MODE_2 1

#define TIM_CHANNEL_1 1
#define TIM_CHANNEL_2 2
#define TIM_CHANNEL_3 3
#define TIM_CHANNEL_4 4

#define TIM1_CHANNEL_1_GPIO GPIOA
#define TIM1_CHANNEL_2_GPIO GPIOA
#define TIM1_CHANNEL_3_GPIO GPIOA
#define TIM1_CHANNEL_4_GPIO GPIOA

#define TIM2_CHANNEL_1_GPIO GPIOA
#define TIM2_CHANNEL_2_GPIO GPIOA
#define TIM2_CHANNEL_3_GPIO GPIOA
#define TIM2_CHANNEL_4_GPIO GPIOA

#define TIM3_CHANNEL_1_GPIO GPIOA
#define TIM3_CHANNEL_2_GPIO GPIOA
#define TIM3_CHANNEL_3_GPIO GPIOB
#define TIM3_CHANNEL_4_GPIO GPIOB

#define TIM4_CHANNEL_1_GPIO GPIOB
#define TIM4_CHANNEL_2_GPIO GPIOB
#define TIM4_CHANNEL_3_GPIO GPIOB
#define TIM4_CHANNEL_4_GPIO GPIOB

#define TIM1_CHANNEL_1_PIN 8
#define TIM1_CHANNEL_2_PIN 9
#define TIM1_CHANNEL_3_PIN 10
#define TIM1_CHANNEL_4_PIN 11

#define TIM2_CHANNEL_1_PIN 0
#define TIM2_CHANNEL_2_PIN 1
#define TIM2_CHANNEL_3_PIN 2
#define TIM2_CHANNEL_4_PIN 3

#define TIM3_CHANNEL_1_PIN 6
#define TIM3_CHANNEL_2_PIN 7
#define TIM3_CHANNEL_3_PIN 0
#define TIM3_CHANNEL_4_PIN 1

#define TIM4_CHANNEL_1_GPIO 6
#define TIM4_CHANNEL_2_GPIO 7
#define TIM4_CHANNEL_3_GPIO 8
#define TIM4_CHANNEL_4_GPIO 9

#include "stm32f10x.h"
#include <stddef.h>
#include <assert.h>

void Timer_Enable(TIM_TypeDef *timer, unsigned short psc, unsigned short arr);

void Timer_Start(TIM_TypeDef *timer);
void Timer_Stop(TIM_TypeDef *timer);

void Timer_Active_IT(TIM_TypeDef *timer, uint32_t priority, void (*callback) (void));

void Timer_PWM_Enable(TIM_TypeDef * timer, char channel, char mode);

void Timer_PWM_Set(TIM_TypeDef *timer, char channel, unsigned short value);

#endif
