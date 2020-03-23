#include "./adc/bsp_adc.h"
#include <stdio.h>
#include "./SysTick/bsp_SysTick.h"
__IO uint16_t ADC_ConvertedValue[NOFCHANEL]={0,0,0,0};

/**
  * @brief  ADC GPIO ��ʼ��
  * @param  ��
  * @retval ��
  */

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// �� ADC IO�˿�ʱ��
	ADC_GPIO_APBxClock_FUN ( ADC_GPIO_CLK|RCC_APB2Periph_GPIOB, ENABLE );
	// ���� ADC IO ����ģʽ
//	GPIO_InitStructure.GPIO_Pin = 	ADC_PIN1|ADC_PIN2|ADC_PIN3|ADC_PIN4|ADC_PIN5|ADC_PIN6;
	GPIO_InitStructure.GPIO_Pin = ADC_PIN3|ADC_PIN4|ADC_PIN5|ADC_PIN6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	// ��ʼ�� ADC IO
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	                 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;           
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GP2Y_High;	
}

/**
  * @brief  ����ADC����ģʽ
  * @param  ��
  * @retval ��
  */
static void ADCx_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	// ��DMAʱ��
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);
	// ��ADCʱ��
	ADC_APBxClock_FUN ( ADC_CLK, ENABLE );
	
	// ��λDMA������
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( u32 ) ( & ( ADC_x->DR ) );
	
	// �洢����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;
	
	// ����Դ��������
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// ��������С��Ӧ�õ�������Ŀ�ĵصĴ�С
	DMA_InitStructure.DMA_BufferSize = NOFCHANEL;
	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// �洢����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	
	// �ڴ����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	

	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	// ��ʼ��DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	
	// ʹ�� DMA ͨ��
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	// ADC ģʽ����
	// ֻʹ��һ��ADC�����ڵ�ģʽ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	
	// ɨ��ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; 

	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;

	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;

	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
	// ת��ͨ������
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANEL;	
		
	// ��ʼ��ADC
	ADC_Init(ADC_x, &ADC_InitStructure);
	
	// ����ADCʱ�ӣΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	// ����ADC ͨ����ת��˳��Ͳ���ʱ��
//	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL1, 1, ADC_SampleTime_55Cycles5);
//	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL2, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL3, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL4, 4, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL5, 5, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL6, 6, ADC_SampleTime_55Cycles5);
	
	// ʹ��ADC DMA ����
	ADC_DMACmd(ADC_x, ENABLE);
	
	// ����ADC ������ʼת��
	ADC_Cmd(ADC_x, ENABLE);
	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADC_x);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADC_x));
	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADC_x);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADC_x));
	
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
	
}

/**
  * @brief  ADC��ʼ��
  * @param  ��
  * @retval ��
  */
void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
}

float Get_LX(void)
{
			float ADCVal;
			uint16_t lx;
			ADCVal = (float) ADC_ConvertedValue[3]/4096*3.3;
			lx = (3.3-ADCVal)*200;
			return lx;
} 
u16 Get_LX_Average(u8 times)
{
	u32 lx_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		lx_val+=Get_LX();
		SysTick_Delay_Ms(5);
	}
	return lx_val/times;
} 
float Get_MQ4(void)
{
			float ADCVal;
			uint16_t mq4;
			ADCVal = (float) ADC_ConvertedValue[4]/4096*3.3;
			mq4 = (ADCVal-0.5)*2000;
			return mq4;
} 
u16 Get_MQ4_Average(u8 times)
{
	u32 mq4_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		mq4_val+=Get_MQ4();
		SysTick_Delay_Ms(5);
	}
	printf("���飺 %d\n",mq4_val/times);
	return mq4_val/times;
}
//float GetGP2Y(void)
//{
//    float AD_PM;  
//	  float pm; 
//    GP2Y_Low;
//    SysTick_Delay_Us(280);
//    AD_PM = (float) ADC_ConvertedValue[5];
//    SysTick_Delay_Us(40);
//    GP2Y_High;
//    SysTick_Delay_Us(9680);
//    pm = 0.17*AD_PM-0.1; //ת����ʽ
//		return pm;
//} 

//u16 Get_GP2Y_Average(u8 times)
//{
//	float pm_val=0;
//	u8 t;
//	for(t=0;t<times;t++)
//	{
//		pm_val+=GetGP2Y();
//		SysTick_Delay_Ms(5);
//	}   
//	printf("PM2.5��%.2f\n",pm_val/times);
//	return pm_val/times;
//}
float Get_Pressure(void)
{
			float ADCVal;
			uint16_t np;
			ADCVal = (float) ADC_ConvertedValue[2];
			np = ADCVal;
			return np;
} 

u16 Get_Pressure_Average(u8 times)
{
	u32 np_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		np_val+=Get_Pressure();
		SysTick_Delay_Ms(5);
	}   
//	printf("NP: %d\n",np_val/times);
	return np_val/times;
}



/*********************************************END OF FILE**********************/
