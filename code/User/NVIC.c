#include "NVIC.h"
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel)	 
{ 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = NVIC_Channel;
	/* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PreemptionPriority; 	
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_SubPriority;
	 /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
} 
