#include <stdbool.h>
#include <stdint.h>
#include "adc.h"
#include "fsl_adc.h"
#include "fsl_clock.h"
#include "fsl_common.h"
#include "fsl_common_arm.h"
#include "fsl_power.h"

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
        .interruptMode = kADC_InterruptForEachSequence
    };

    CLOCK_Select(kADC_Clk_From_Fro);
    CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1U);
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);

    ADC_GetDefaultConfig(&AdcConfigStruct);
    AdcConfigStruct.clockMode = kADC_ClockAsynchronousMode;
    ADC_Init(ADC0, &AdcConfigStruct);
    ADC_SetConvSeqAConfig(ADC0, &AdcConvConfigStruct);
    ADC_EnableConvSeqA(ADC0, true);

    ADC_EnableInterrupts(ADC0, kADC_ConvSeqAInterruptEnable);
}

void ADC0_SEQA_IRQHandler(void) {
    if (kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0)) {
        ADC_GetChannelConversionResult(ADC0, ADC_CHAN_NUMB, &conversionResults);
        ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);
        conversionReady = true;
    }

    SDK_ISR_EXIT_BARRIER;
}

void adc_volts_to_amps(uint32_t* amps) {
    uint32_t int_volts_to_amps = (conversionResults.result * ADC_VOLTS_PER_CONV * VOLTS_TO_AMPS_FACTOR_INT) / 100000;
    amps[0] = int_volts_to_amps / 1000UL;
    amps[1] = int_volts_to_amps % 1000UL;
}
