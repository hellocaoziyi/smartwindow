#include "NVIC.h"
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel)	 
{ 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = NVIC_Channel;
	/* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_PreemptionPriority; 	
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_SubPriority;
	 /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
} 
