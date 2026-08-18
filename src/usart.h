#ifndef MY_USART_H
#define MY_USART_H
#include "fsl_usart.h"
#include "button.h"
#include <stdint.h>

void USART_Inititalization(void);
void Send_Output(float amps, uint16_t time);

#endif // MY_USRT_H
