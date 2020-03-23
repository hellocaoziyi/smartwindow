#include "./wifi/common.h"
#include "./led/bsp_led.h"
#include "./dht11/bsp_dht11.h"
#include "./adc/bsp_adc.h"
#include "./GeneralTim/bsp_GeneralTim.h"

//ATK-ESP8266 WIFI STA测试

u8 atk_8266_wifista_test(void)
{ 
	u8 *p;
	u8 *p1;
	u16 t=999;		//加速第一次获取链接状态
	u8 res=0;
	u16 rlen=0;
	DHT11_Data_TypeDef DHT11_Data;
	uint16_t lx;
	uint16_t mq4;
	uint16_t np;
	u16 turn=68;
	
	p=mymalloc(32);							//申请32字节内存
	p1=mymalloc(64);
	
	atk_8266_send_cmd("AT+WLMODE=1","[WLMODE]OK",50);		//设置WIFI STA模式
	//设置连接到的WIFI网络名称/加密方式/密码,这几个参数需要根据您自己的路由器设置进行修改!! 
	sprintf((char*)p,"AT+WLSTAPARAM=%s,%s",wifista_ssid,wifista_password);//设置无线参数:ssid,密码
	Usart_SendString( UART4, "vis p2,0");endcommand();
	while(atk_8266_send_cmd(p,"[WLSTAPARAM]OK",600));					//连接目标路由器,并且获得IP
	Usart_SendString( UART4, "vis p2,1");endcommand();
	sprintf((char*)p,"AT+NWKCTCP=SERVER,%s",(u8*)portnum); 
	atk_8266_send_cmd(p,"[NWKCTCP_ID]",50);
  USART3_RX_STA=0;
	Usart_SendString( UART4,"p1.pic=14");endcommand();
	while(1)
	{
//				t++;
				SysTick_Delay_Ms(100);
				HMI();
				if(USART3_RX_STA&0X8000)			//接收到一次数据了
				{ 
					p1=atk_8266_check_cmd("_");
					p1++;
					if(strstr(p1,"LED_1_1"))
					{
						Usart_SendString( UART4, "p5.pic=24");endcommand();
						LED1_OFF;
					}
					if(strstr(p1,"LED_2_1"))
					{
						Usart_SendString( UART4, "p5.pic=23");endcommand();
						LED1_ON;
					}
					if(strstr(p1,"LED_3_1"))
					{
						Usart_SendString( UART4, "h0.val=0");endcommand();
						TIM_SetCompare1(TIM3,68);
					}
					if(strstr(p1,"BUZZER_1"))
					{
						Usart_SendString( UART4, "h0.val=100");endcommand();
						TIM_SetCompare1(TIM3,130);
					}
					USART3_RX_STA=0;
        }  
//				if(t==1000)//连续10秒钟没有收到任何数据,检查连接是不是还存在.
//				{
//					//constate=atk_8266_consta_check();//得到连接状态
//					SysTick_Delay_Ms(10);
//					if(atk_8266_send_cmd("AT+WLCONNECTINFO","[WLCONNECTINFO]DISCONNECTED!",20)){Usart_SendString( UART4, "vis p2,1");endcommand();}
//					else{Usart_SendString( UART4, "vis p2,0");endcommand();} 
//					t=0;
//				}
				//温湿度传感器
				if( DHT11_Read_TempAndHumidity ( & DHT11_Data ) == SUCCESS)
			{
				sprintf((char*)p,"n5.val=%d",(DHT11_Data.temp_int-5));
				Usart_SendString( UART4,p);endcommand();
				sprintf((char*)p,"n6.val=%d",DHT11_Data.humi_int); 
				
				Usart_SendString( UART4,p);endcommand();
			}
			switch(functionFLAG)
			{
				case 1: LED1_OFF;functionFLAG=0;break;
				case 2: LED1_ON;functionFLAG=0;break;
				case 3:{Usart_SendString( UART4,"p1.pic=14");endcommand();functionFLAG=0;}
			}
			turn=HMI_Scan();
			if(turn!=0)
			{
			TIM_SetCompare1(TIM3,turn);
			}
			lx=Get_LX_Average(40);
//		  mq4=Get_MQ4_Average(40);
			np=Get_Pressure_Average(40);
			if(np<4000)
			{
				Usart_SendString( UART4,"play 0,0,1");endcommand();
				Usart_SendString( UART4,"p1.pic=18");endcommand();
			}
			if(lx>300)
			{
				Usart_SendString( UART4, "p5.pic=23");endcommand();
				LED1_ON;
			}
			if((DHT11_Data.temp_int-5)>26)
			{
						Usart_SendString( UART4, "h0.val=100");endcommand();
						TIM_SetCompare1(TIM3,130);
			}
			if(DHT11_Data.humi_int>70)
			{
						Usart_SendString( UART4, "h0.val=0");endcommand();
						TIM_SetCompare1(TIM3,68);
			}
				Usart_SendString( UART4, "t10.txt=\"良好\"");endcommand();
//				atk_8266_at_response(1);
		}
	myfree(p);		//释放内存 
	myfree(p1);		//释放内存 
	return res;		
	}
