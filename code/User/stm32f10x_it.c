/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "queue.h"

vu16 USART3_RX_STA=0;
extern uint8_t RecevData[10];
int ihmi=0;
extern int ENDFLAG;
int ENDCOUNT;
//���ڽ��ջ����� 	
extern u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */
extern void TimingDelay_Decrement(void);
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

void TIM7_IRQHandler(void)
{ 	  		    
	if( TIM_GetITStatus( TIM7, TIM_IT_Update) != RESET )//�Ǹ����ж�
	{	 			   
		USART3_RX_STA|=1<<15;	//��ǽ������
		TIM_ClearITPendingBit(TIM7 , TIM_FLAG_Update);		//����жϱ�־λ		   
		TIM_Cmd(TIM7, DISABLE);		//�رն�ʱ��7	  
	}	      											 
}

// �����жϷ�����
void DEBUG_USART1_IRQHandler(void)
{
  //uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USART1,USART_IT_RXNE)!=RESET)
	{		
		//ucTemp = USART_ReceiveData(DEBUG_USART1);
		//USART_ClearITPendingBit(DEBUG_USART1,USART_IT_RXNE);
		//RingBuf_Write(USART_ReceiveData(DEBUG_USART1));
    //USART_SendData(DEBUG_USART1,ucTemp);    
	}	 
}
void DEBUG_USART2_IRQHandler(void)
{
  //uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USART2,USART_IT_RXNE)!=RESET)
	{		
		//ucTemp = USART_ReceiveData(DEBUG_USART2);
    //USART_SendData(DEBUG_USART2,ucTemp); 
    //RingBuf_Write(USART_ReceiveData(DEBUG_USART2));		
	}	 
}
void DEBUG_USART3_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USART3,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USART3);
		if((USART3_RX_STA&(1<<15))==0)
		{
			if(USART3_RX_STA<USART3_MAX_RECV_LEN)
			{
				TIM_SetCounter(TIM7,0);         				//���������
				if(USART3_RX_STA==0) 				//ʹ�ܶ�ʱ��7���ж� 
				{
					TIM_Cmd(TIM7, ENABLE);     			//ʹ�ܶ�ʱ��7
				}
				USART3_RX_BUF[USART3_RX_STA++]=ucTemp;
			}
			else 
			{
				USART3_RX_STA|=1<<15;				//ǿ�Ʊ�ǽ������
			}
		}
    //USART_SendData(DEBUG_USART3,ucTemp);    
		//RingBuf_Write(USART_ReceiveData(DEBUG_USART3));
	}	 
}
void DEBUG_USART4_IRQHandler(void)
{
  //uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USART4,USART_IT_RXNE)!=RESET)
	{		
		//ucTemp = USART_ReceiveData(DEBUG_USART4);
   // USART_SendData(DEBUG_USART4,ucTemp); 
   //RingBuf_Write(USART_ReceiveData(DEBUG_USART4));	
   RecevData[ihmi] = USART_ReceiveData(DEBUG_USART4);
    if( RecevData[ihmi]== 0xFF)
		{
			ENDCOUNT++;
//			printf("���յ���%d������β\r\n",ENDCOUNT);
			if(ENDCOUNT==3)
			{
				ENDFLAG=1;
				ENDCOUNT=0;
				ihmi=0;
			}
			else
			{
				ihmi++;
			}
		}
     else
		 {
			 ihmi++;
			 ENDCOUNT=0;
		 }		
	}	 
}
void DEBUG_USART5_IRQHandler(void)
{
  //uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USART5,USART_IT_RXNE)!=RESET)
	{		
		//ucTemp = USART_ReceiveData(DEBUG_USART5);
    //USART_SendData(DEBUG_USART5,ucTemp); 
   //RingBuf_Write(USART_ReceiveData(DEBUG_USART5));		
	}	 
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
