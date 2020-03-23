#include "timer7.h"
#include "NVIC.h"

void TIM7_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = arr;	

	  // ʱ��Ԥ��Ƶ��Ϊ
    TIM_TimeBaseStructure.TIM_Prescaler= psc;
	
		// ʱ�ӷ�Ƶ���� ��������ʱ��û�У����ù�
    //TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
		// ����������ģʽ��������ʱ��ֻ�����ϼ�����û�м���ģʽ������
    //TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		
		// �ظ���������ֵ��������ʱ��û�У����ù�
		//TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
		
		// ����������жϱ�־λ
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
		
		// ʹ�ܼ�����
    TIM_Cmd(TIM7, ENABLE);
		
    MY_NVIC_Init(0,1,TIM7_IRQn);	//��ռ0�������ȼ�1����2									 
} 
