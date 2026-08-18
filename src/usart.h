#ifndef MY_USART_H
#define MY_USART_H
#include "fsl_usart.h"
#include "button.h"

status_t USART_Inititalization(void);
void Send_Output(output_format_t format);

#endif // MY_USRT_H
