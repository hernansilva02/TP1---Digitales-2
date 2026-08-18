#ifndef ADC_H 
#define ADC_H
#include <stdint.h>
#include <stdbool.h>

#define ADC_CHAN_NUMB 0U
#define ADC_TO_AMPS_FACTOR 0.003663004f

extern volatile bool conversionReady;

void adc_config();
float adc_volts_to_amps(void);
#endif
