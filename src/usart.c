#include "usart.h"
#include "fsl_clock.h"
#include "fsl_usart.h"
#include <stdio.h>

#define WH_PRICE 3600.0f

usart_handle_t usart_handle;

static void usart_callback_func(USART_Type *base, usart_handle_t *handle, status_t status, void *userData) {

}

void USART_Inititalization(void) {
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

    USART_TransferCreateHandle(USART0, &usart_handle, usart_transfer_callback_t callback, void *userData)
    USART_Init(USART0, &config, CLOCK_GetFreq(kCLOCK_MainClk));
}

void Send_Output(float amps, uint16_t time) {
    uint8_t len;
    uint8_t buffer[40];
    switch (currentFormat) {
        case FORMAT_AMPS:
            len = snprintf(buffer, sizeof(buffer), "%.2f A %u seg\r\n", amps, time);
            USART_WriteBlocking(USART0, buffer, len);
            break;
        case FORMAT_WATTS: 
        {
            float watts = 220 * amps;
            len = snprintf(buffer, sizeof(buffer), "%.2f A %u seg\r\n", watts, time);
            USART_WriteBlocking(USART0, buffer, len);
            break;
        }
        case FORMAT_COST:
        {
            float cost = (220.0f * amps) * time/3600.0f * WH_PRICE;
            len = snprintf(buffer, sizeof(buffer), "$%.2f A %u seg\r\n", cost, time);
            USART_WriteBlocking(USART0, buffer, len);
            break;
        }
    }
}
