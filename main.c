#include <stdint.h>
#include <stdbool.h>
#include "board.h"
#include "fsl_adc.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_device_registers.h"
#include "fsl_power.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "src/adc.h"
#include "src/timer.h"
#include "src/led.h"
#include "src/button.h"
#include "src/usart.h"

void BOARD_InitHardware(void) {
    /* Initialize the pins. */
    BOARD_InitBootPins();

    /* Enable clock to 30MHz. */
    BOARD_BootClockFRO30M();

    /* Select the main clock as source clock of USART0. */
    CLOCK_Select(kUART0_Clk_From_MainClk);
}

int main() {
    uint32_t amps[2] = {0};
    uint32_t report_interval_acc = 0;
    BOARD_InitHardware();
    leds_initialize();
    SysTick_Config(SystemCoreClock / 1000U);
    Pint_Initialize();
    adc_config();
    USART_Inititalization();
    NVIC_EnableIRQ(ADC0_SEQA_IRQn);
    while (1) {
        ADC_DoSoftwareTriggerConvSeqA(ADC0);
        if (conversionReady) {
            conversionReady = false;
            adc_volts_to_amps(amps);
        }
        select_led_on(amps);
        if (buttonReady) {
            buttonReady = false;
            currentFormat = Change_Format();
        }
        if (TimerReady) {
            TimerReady = false;
            Report_Interval_Act(report_interval * 1000U);
            Send_Output(amps, report_interval_acc);
            report_interval_acc += report_interval;
        }
        Rcv_Command();
        // SysDelay(report_interval * 1000U); // report_interval is in seconds
    }
}
