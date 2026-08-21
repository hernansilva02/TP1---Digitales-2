#include "usart.h"
#include "fsl_clock.h"
#include "fsl_usart.h"
#include <stdio.h>
#include <string.h>

#define WH_PRICE 3600.0f

usart_handle_t usart_handle;
usart_transfer_t rcv;
volatile bool RxOngoing = false;
volatile bool RxBufferEmpty = true;
uint32_t report_interval = 5;
uint8_t RxData;
uint8_t CommandBuffer[16] = {0};

static void usart_callback_func(USART_Type *base, usart_handle_t *handle, status_t status, void *userData) {
    (void)userData;
    if (status == kStatus_USART_RxIdle) {
        RxOngoing = false;
        RxBufferEmpty = false;
    }
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

    USART_Init(USART0, &config, CLOCK_GetFreq(kCLOCK_MainClk));

    USART_TransferCreateHandle(USART0, &usart_handle, usart_callback_func, NULL);
    rcv.data = &RxData;
    rcv.dataSize = 1;
}

void Rcv_Command() {
    static uint8_t command_idx = 0;
    if (!RxOngoing && RxBufferEmpty) {
        RxOngoing = true;
        USART_TransferReceiveNonBlocking(USART0, &usart_handle, &rcv, NULL);
    }

    if (!RxBufferEmpty) {
        RxBufferEmpty = true;
        if ((RxData == '\n' || RxData == '\r') && command_idx > 0) {
            CommandBuffer[command_idx] = '\0';
            command_idx = 0;
            if (!strcmp(CommandBuffer, "time 5")) {
                report_interval = 5;
            } else if (!strcmp(CommandBuffer, "time 10")) {
                report_interval = 10;
            } else {
                uint8_t command_not_found[] = "Error. Unknown command\n";
                USART_WriteBlocking(USART0, command_not_found, sizeof(command_not_found) - 1);
            }
        } else {
            if (command_idx < sizeof(CommandBuffer)) {
                CommandBuffer[command_idx] = RxData;
                command_idx++;
            } else {
                return;
            }
        }
    }
}

void Send_Output(float amps, uint16_t report_interval_acc) {
    /*
    uint8_t txbuff[] =
    "Usart polling example.\r\nBoard will send back received characters.\r\nNow, please input any character:\r\n";

    USART_WriteBlocking(USART0, txbuff, sizeof(txbuff) - 1);
    */
    uint8_t len;
    uint8_t buffer[40];
    switch (currentFormat) {
        case FORMAT_AMPS:
            {
                uint32_t int_amps = (uint32_t)amps / 100;
                uint32_t dec_amps = (uint32_t)amps % 100;
                len = snprintf(buffer, sizeof(buffer), "%lu.%02lu A %u seg\r\n", int_amps, dec_amps, report_interval_acc);
                USART_WriteBlocking(USART0, buffer, len);
                break;
            }
        case FORMAT_WATTS: 
        {
            float watts = 220.0f * amps;
            len = snprintf(buffer, sizeof(buffer), "%f W %u seg\r\n", watts, report_interval_acc);
            USART_WriteBlocking(USART0, buffer, len);
            break;
        }
        case FORMAT_COST:
        {
            float cost = (220.0f * amps) * report_interval/3600.0f * WH_PRICE;
            len = snprintf(buffer, sizeof(buffer), "$f %u seg\r\n", cost, report_interval_acc);
            USART_WriteBlocking(USART0, buffer, len);
            break;
        }
    }
}
