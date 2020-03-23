#ifndef  __QUEUE_H
#define  __QUEUE_H

#include "stm32f10x.h"

unsigned char RingBuf_Write(unsigned char data);
unsigned char RingBuf_Read(unsigned char* pData);

void queue_send(USART_TypeDef * pUSARTx);

#endif /* __QUEUE_H */
