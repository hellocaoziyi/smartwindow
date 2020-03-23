#include "queue.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"

#define BUFFER_MAX 255

typedef struct
{
	unsigned short int headPosition;
	unsigned short int tailPositon;
	//short int tailPositon;
	unsigned short int Length;
	unsigned char RingBuff[BUFFER_MAX];
}ringBuffer_t;

ringBuffer_t ringBuff;

void RingBuff_Init(void)
{
   ringBuff.headPosition = 0;
   ringBuff.tailPositon = 0;
   ringBuff.Length = 0;
}

unsigned char RingBuf_Write(unsigned char data)
{
	if(ringBuff.Length>=BUFFER_MAX)
	{
		return 1;
	}
	ringBuff.RingBuff[ringBuff.tailPositon]=data;
	ringBuff.tailPositon=(ringBuff.tailPositon+1)%BUFFER_MAX;
	ringBuff.Length++;
	return 0;
}
unsigned char RingBuf_Read(unsigned char* pData)
{
	if(ringBuff.Length==0)
	{
		return 1;
	}
	*pData=ringBuff.RingBuff[ringBuff.headPosition];
	ringBuff.headPosition = (ringBuff.headPosition+1)%BUFFER_MAX;
  ringBuff.Length--;
	return 0;
}
void queue_send(USART_TypeDef * pUSARTx)
{
	uint8_t data=0;
		while(RingBuf_Read(&data)==0)
		{
			USART_SendData(pUSARTx,data);
			SysTick_Delay_Us(200);
		}
}
