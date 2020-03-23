//USER
#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "NVIC.h"
//UART
#include "bsp_usart.h"
#include "queue.h"
//WIFI
#include "./wifi/timer7.h"
#include "./wifi/common.h"
//Sensor
#include "./dht11/bsp_dht11.h"
#include "./adc/bsp_adc.h"
//window
#include "./led/bsp_led.h"
#include "./GeneralTim/bsp_GeneralTim.h"  
//MALLOC
#include "./MALLOC/malloc.h"

extern vu16 USART3_RX_STA;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	MY_NVIC_Init(0,0,USART3_IRQn);
	TIM7_Int_Init(1000-1,7200-1);			//100ms�ж�һ��
	TIM_Cmd(TIM7, DISABLE);								//�رն�ʱ��7
	USART3_RX_STA=0;									//���� 
	mem_init();				//��ʼ���ڴ��
	GENERAL_TIM_Init();
	DHT11_Init ();
	LED_GPIO_Config();
	ADCx_Init();
	
  atk_8266_test();
	while(1)
	{}
}

/*********************************************END OF FILE**********************/
