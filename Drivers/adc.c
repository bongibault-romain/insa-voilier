#include "adc.h"

void ADC_Enable(ADC_TypeDef *adc) {
	RCC->CFGR |= RCC_CFGR_ADCPRE; // On divise par 6 la fréquence de l'ADC (72/6=12MHz)
	
	if (adc == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	} else if (adc == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}
	
	adc->CR2 |= ADC_CR2_ADON;
	adc->CR2 |= ADC_CR2_EXTTRIG;
	adc->CR2 |= ADC_CR2_EXTSEL;	
}

unsigned short ADC_Read_Wait(ADC_TypeDef *adc, char channel) {
	adc->SQR3 &= ~ADC_SQR3_SQ1;
	adc->SQR3 |= channel;
	
	assert(channel < 17);
	
	adc->CR2 |= ADC_CR2_SWSTART;
	
	while ((adc->SR & ADC_SR_EOC) == 0) { };
	
	return (unsigned short) (adc->DR & ADC_DR_DATA);
}