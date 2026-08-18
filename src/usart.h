#ifndef MY_USART_H
#define MY_USART_H
#include "fsl_usart.h"
#include "button.h"
#include <stdint.h>

extern char CommandBuffer[16];
extern uint8_t report_interval;

void USART_Inititalization(void);
void Send_Output(float amps, uint16_t time);
void Rcv_Command();

#endif // MY_USRT_H
