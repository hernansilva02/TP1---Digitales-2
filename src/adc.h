#ifndef ADC_H 
#define ADC_H
#include <stdint.h>
#include <stdbool.h>

#define ADC_CHAN_NUMB 1U
#define VOLTS_TO_AMPS_FACTOR_INT 454 // 4.54 A/V
#define ADC_VOLTS_PER_CONV 805 // 0.000805

extern volatile bool conversionReady;

void adc_config();
void adc_volts_to_amps(uint32_t* amps);
#endif
