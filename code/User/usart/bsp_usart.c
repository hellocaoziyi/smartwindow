#include "bsp_usart.h"

//���ڷ��ͻ����� 	
__align(8) u8 USART1_TX_BUF[USART1_MAX_SEND_LEN]; 	//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
//���ڽ��ջ����� 	
u8 USART1_RX_BUF[USART1_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.

//���ڷ��ͻ����� 	
__align(8) u8 USART2_TX_BUF[USART2_MAX_SEND_LEN]; 	//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
//���ڽ��ջ����� 	
u8 USART2_RX_BUF[USART2_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.

//���ڷ��ͻ����� 	
__align(8) u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 	//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
//���ڽ��ջ����� 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.

//���ڷ��ͻ����� 	
__align(8) u8 USART4_TX_BUF[USART4_MAX_SEND_LEN]; 	//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
//���ڽ��ջ����� 	
u8 USART4_RX_BUF[USART4_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.

//���ڷ��ͻ����� 	
__align(8) u8 USART5_TX_BUF[USART5_MAX_SEND_LEN]; 	//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
//���ڽ��ջ����� 	
u8 USART5_RX_BUF[USART5_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.

uint8_t endbuff[3]={0xFF,0xFF,0xFF};
 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART1_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART4_IRQ;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART5_IRQ;
	NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART1_GPIO_CLK, ENABLE);
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK, ENABLE);
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART3_GPIO_CLK, ENABLE);
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART4_GPIO_CLK, ENABLE);
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART5_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART1_APBxClkCmd(DEBUG_USART1_CLK, ENABLE);
	DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK, ENABLE);
	DEBUG_USART3_APBxClkCmd(DEBUG_USART3_CLK, ENABLE);
	DEBUG_USART4_APBxClkCmd(DEBUG_USART4_CLK, ENABLE);
	DEBUG_USART5_APBxClkCmd(DEBUG_USART5_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART1_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
	GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART3_TX_GPIO_PIN;
	GPIO_Init(DEBUG_USART3_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART4_TX_GPIO_PIN;
	GPIO_Init(DEBUG_USART4_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART5_TX_GPIO_PIN;
	GPIO_Init(DEBUG_USART5_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
	GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART3_RX_GPIO_PIN;
	GPIO_Init(DEBUG_USART3_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART4_RX_GPIO_PIN;
	GPIO_Init(DEBUG_USART4_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART5_RX_GPIO_PIN;
	GPIO_Init(DEBUG_USART5_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART1_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USART1, &USART_InitStructure);
	
	USART_InitStructure.USART_BaudRate = DEBUG_USART2_BAUDRATE;
	USART_Init(DEBUG_USART2, &USART_InitStructure);
	
	USART_InitStructure.USART_BaudRate = DEBUG_USART3_BAUDRATE;
	USART_Init(DEBUG_USART3, &USART_InitStructure);
	
	USART_InitStructure.USART_BaudRate = DEBUG_USART4_BAUDRATE;
	USART_Init(DEBUG_USART4, &USART_InitStructure);
	
	USART_InitStructure.USART_BaudRate = DEBUG_USART5_BAUDRATE;
	USART_Init(DEBUG_USART5, &USART_InitStructure);
	
	// �����ж����ȼ�����
	NVIC_Configuration();
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(DEBUG_USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(DEBUG_USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(DEBUG_USART3, USART_IT_RXNE, ENABLE);
	USART_ITConfig(DEBUG_USART4, USART_IT_RXNE, ENABLE);
	USART_ITConfig(DEBUG_USART5, USART_IT_RXNE, ENABLE);	
	
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USART1, ENABLE);
  USART_Cmd(DEBUG_USART2, ENABLE);
  USART_Cmd(DEBUG_USART3, ENABLE);	
	USART_Cmd(DEBUG_USART4, ENABLE);
	USART_Cmd(DEBUG_USART5, ENABLE);

  // ���������ɱ�־
	//USART_ClearFlag(USART1, USART_FLAG_TC);     
}
/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}
/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/****************** ����8λ������ ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

//����printf����
void u1_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART1_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART1_TX_BUF);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		while(USART_GetFlagStatus(DEBUG_USART1, USART_FLAG_TXE) == RESET){}//ѭ������,ֱ��������� 
    USART_SendData(DEBUG_USART1,USART1_TX_BUF[j]);
	}
}
void u2_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		while(USART_GetFlagStatus(DEBUG_USART2, USART_FLAG_TXE) == RESET){}//ѭ������,ֱ��������� 
    USART_SendData(DEBUG_USART2,USART2_TX_BUF[j]);
	}
}
void u3_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		while(USART_GetFlagStatus(DEBUG_USART3, USART_FLAG_TXE) == RESET){}//ѭ������,ֱ��������� 
    USART_SendData(DEBUG_USART3,USART3_TX_BUF[j]);
	}
}
void u4_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART4_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART4_TX_BUF);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		while(USART_GetFlagStatus(DEBUG_USART4, USART_FLAG_TXE) == RESET){}//ѭ������,ֱ��������� 
    USART_SendData(DEBUG_USART4,USART4_TX_BUF[j]);
	}
}
void u4_HMIprintfhead(int num)  
{  
	Usart_SendArray(DEBUG_USART4,endbuff,3);
	u4_printf("t");
	u4_printf("%d",num);
	u4_printf(".txt=\"");
}
void u4_HMIprintfend(void)  
{
	u4_printf("\"");
	u4_printf("\"");
	Usart_SendArray(DEBUG_USART4,endbuff,3);
}
void u5_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART5_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART5_TX_BUF);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		while(USART_GetFlagStatus(DEBUG_USART5, USART_FLAG_TXE) == RESET){}//ѭ������,ֱ��������� 
    USART_SendData(DEBUG_USART5,USART5_TX_BUF[j]);
	}
}
void endcommand(void)
{
	Usart_SendArray(DEBUG_USART4,endbuff,3);
}

