#include <stdint.h>
#include <stdbool.h>
#include "adc.h"
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_device_registers.h"
#include "fsl_power.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "src/adc.h"

void BOARD_InitHardware(void)
{
    /* Initialize the pins. */
    BOARD_InitBootPins();

    /* Enable clock to 30MHz. */
    BOARD_BootClockFRO30M();

    /* Select the main clock as source clock of USART0. */
    CLOCK_Select(kUART0_Clk_From_MainClk);
}

int main() {
    BOARD_InitHardware();
    adc_config();
    EnableIRQ(ADC_SEQA_IRQn);
    while (1) {
        while (!conversionReady);

        float amps = adc_volts_to_amps();
        conversionReady = false;
    }
}
