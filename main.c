#include <stdint.h>
#include <stdbool.h>
#include "adc.h"
#include "board.h"
#include "fsl_adc.h"
#include "mnt/WDbk/Users/Hernan/Documents/UTN/2026/digitales2/real_tp1/src/usart.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_device_registers.h"
#include "fsl_power.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "src/adc.h"
#include "src/timer.h"
#include "src/leds.h"
#include "src/button.h"

void BOARD_InitHardware(void) {
    /* Initialize the pins. */
    BOARD_InitBootPins();

    /* Enable clock to 30MHz. */
    BOARD_BootClockFRO30M();

    /* Select the main clock as source clock of USART0. */
    CLOCK_Select(kUART0_Clk_From_MainClk);
}

int main() {
    float amps;
    uint16_t time = 0U;
    const uint32_t delay = 5000; // Delay provided by user via USART. Testing only
    BOARD_InitHardware();
    leds_intialize();
    Pint_Config();
    adc_config();
    NVIC_EnableIRQ(ADC0_SEQA_IRQn);
    while (1) {
        ADC_DoSoftwareTriggerConvSeqA(ADC0);
        if (conversionReady) {
            amps = adc_volts_to_amps();
            conversionReady = false;
        }
        select_led_on(amps);
        if (buttonReady) {
            buttonReady = false;
            currentFormat = Change_Format();
        }
        time += 5U;
        Send_Output(amps, time);
        SysDelay(delay);
    }
}
