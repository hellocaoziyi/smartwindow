#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"
//#define GP2Y_High GPIO_SetBits(GPIOB,GPIO_Pin_1);
//#define GP2Y_Low  GPIO_ResetBits(GPIOB,GPIO_Pin_1);

// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOC  
#define    ADC_PORT                      GPIOC

// ע��
// 1-PC0 ��IOT����ӵ��Ƿ�������Ĭ�ϱ�����
// 2-PC0 ��MINI����ӵ���SPI FLASH�� Ƭѡ��Ĭ�ϱ�����
// ���� PC0 �� ADC ת��ͨ����ʱ�򣬽�����ܻ������

// ת��ͨ������
#define    NOFCHANEL										 4

//#define    ADC_PIN1                      GPIO_Pin_0
//#define    ADC_CHANNEL1                  ADC_Channel_10

//#define    ADC_PIN2                      GPIO_Pin_1
//#define    ADC_CHANNEL2                  ADC_Channel_11

#define    ADC_PIN3                      GPIO_Pin_2
#define    ADC_CHANNEL3                  ADC_Channel_12

#define    ADC_PIN4                      GPIO_Pin_3
#define    ADC_CHANNEL4                  ADC_Channel_13

#define    ADC_PIN5                      GPIO_Pin_4
#define    ADC_CHANNEL5                  ADC_Channel_14

#define    ADC_PIN6                      GPIO_Pin_5
#define    ADC_CHANNEL6                  ADC_Channel_15


// ADC1 ��Ӧ DMA1ͨ��1��ADC3��ӦDMA2ͨ��5��ADC2û��DMA����
#define    ADC_x                         ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1


/**************************��������********************************/
void               ADCx_Init                               (void);
float Get_LX(void);
u16 Get_LX_Average(u8 times);
float Get_MQ4(void);
u16 Get_MQ4_Average(u8 times);
//float GetGP2Y(void);
//u16 Get_GP2Y_Average(u8 times);
float Get_Pressure(void);
u16 Get_Pressure_Average(u8 times);
#endif /* __ADC_H */

