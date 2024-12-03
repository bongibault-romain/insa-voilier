#include "battery.h"
#include "adc.h"
#include <stddef.h>

static ADC_TypeDef * battery_adc = NULL;
static char battery_channel = 0;

void Battery_Init(ADC_TypeDef * adc, char channel) {
    battery_adc = adc;
    battery_channel = channel;
    ADC_Enable(adc);
}

char Battery_Read() {
    // Received value from the battery (0-0xFFF) (12 bits)
    int read = ADC_Read_Wait(battery_adc, battery_channel);

    // The max value for the battery is (12/13)V = 0.923 V that converts to 1145.35
    // TODO:
    return (char) read;
}
