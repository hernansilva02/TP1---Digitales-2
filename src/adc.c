#include <stdbool.h>
#include "adc.h"
#include "fsl_adc.h"
#include "fsl_common.h"

static adc_result_info_t conversionResults;
volatile bool conversionReady = false;

void adc_config() {
    adc_config_t AdcConfigStruct;
    adc_conv_seq_config_t AdcConvConfigStruct = {
        .channelMask = (1U << ADC_CHAN_NUMB),
        .triggerMask = 0U, // software triggered sequence
        .triggerPolarity = kADC_TriggerPolarityPositiveEdge,
        .enableSyncBypass = false,
        .enableSingleStep = false,
        .interruptMode = kADC_InterruptForEachConversion
    };

    ADC_GetDefaultConfig(&AdcConfigStruct);
    ADC_SetConvSeqAConfig(ADC0, &AdcConvConfigStruct);

    ADC_EnableInterrupts(ADC0, kADC_ConvSeqAInterruptEnable);
}

void ADC0_SEQA_IRQHandler(void) {
    if (kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0)) {
        ADC_GetChannelConversionResult(ADC0, ADC_CHAN_NUMB, &conversionResults);
        ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);
        conversionReady = true;
    }
}

float adc_volts_to_amps(void) {
    return conversionResults.result * ADC_TO_AMPS_FACTOR;
}
