#include "usart.h"
#include "fsl_clock.h"
#include "mnt/WDbk/Users/Hernan/Documents/UTN/2026/digitales2/real_tp1/src/button.h"

status_t USART_Inititalization(void) {
    usart_config_t config = {
        .baudRate_Bps = 9600U,
        .enableTx = true,
        .enableRx = true,
        .enableContinuousSCLK = false,
        .loopback = false,
        .parityMode = kUSART_ParityDisabled,
        .stopBitCount = kUSART_OneStopBit,
        .bitCountPerChar = kUSART_8BitsPerChar,
    };

    return USART_Init(USART0, &config, CLOCK_GetFreq(kCLOCK_MainClk));
}

void Send_Output(output_format_t format,) {
    uint8_t* output;
    switch (format) {
        case FORMAT_AMPS:
            output 
    }
}
