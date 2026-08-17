#ifndef ADC_H 
#define ADC_H
#include <stdint.h>

#define ADC_CHAN_NUMB 0U

extern bool volatile conversionReady;

void adc_config();
float adc_volts_to_amps(void);
#endif
