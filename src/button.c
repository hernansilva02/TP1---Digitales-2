#include "button.h"
#include "fsl_pint.h"
#include "fsl_syscon.h"
#include "fsl_syscon_connections.h"
#include "fsl_usart.h"
#include <stdint.h>

#define FORMAT_COUNT 3U

volatile bool buttonReady = false;
volatile bool StartStopButtonReady = false;
output_format_t currentFormat = FORMAT_AMPS;

void button_callback(pint_pin_int_t pintr, pint_status_t* status) {
    if (pintr == kPINT_PinInt0) {
        buttonReady = true;
        return;
    }

    if (pintr == kPINT_PinInt1) {
        StartStopButtonReady = true;
        return;
    }
}

void Pint_Initialize(void) {
    SYSCON_AttachSignal(SYSCON, kPINT_PinInt0, kSYSCON_GpioPort0Pin4ToPintsel); // Attaches PIO4 to PINT0
    SYSCON_AttachSignal(SYSCON, kPINT_PinInt1, kSYSCON_GpioPort0Pin12ToPintsel); // Attaches PIO12 to PINT1 (ISPO Button - used to start/stop program)
    PINT_Init(PINT);
    PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableFallEdge);
    PINT_PinInterruptConfig(PINT, kPINT_PinInt1, kPINT_PinIntEnableFallEdge);
    PINT_SetCallback(PINT, button_callback);
    PINT_EnableCallbackByIndex(PINT, kPINT_PinInt0);
    PINT_EnableCallbackByIndex(PINT, kPINT_PinInt1);
}

output_format_t Change_Format(void) {
     return (currentFormat + 1) % FORMAT_COUNT;
}
