#ifndef MY_USART_H
#define MY_USART_H
#include "button.h"
#include <stdint.h>

#define WH_PRICE 36

extern uint8_t CommandBuffer[16];
extern uint32_t report_interval;

void USART_Inititalization(void);
void Send_Output(uint32_t* amps, uint32_t time);
void Rcv_Command();

#endif // MY_USRT_H
