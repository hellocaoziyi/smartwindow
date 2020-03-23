#include "timer7.h"
#include "NVIC.h"

void TIM7_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// 开启定时器时钟,即内部时钟CK_INT=72M
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = arr;	

	  // 时钟预分频数为
    TIM_TimeBaseStructure.TIM_Prescaler= psc;
	
		// 时钟分频因子 ，基本定时器没有，不用管
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
		// 计数器计数模式，基本定时器只能向上计数，没有计数模式的设置
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		
		// 重复计数器的值，基本定时器没有，不用管
		//TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	  // 初始化定时器
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
		
		// 清除计数器中断标志位
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
		
		// 使能计数器
    TIM_Cmd(TIM7, ENABLE);
		
    MY_NVIC_Init(0,1,TIM7_IRQn);	//抢占0，子优先级1，组2									 
} 
