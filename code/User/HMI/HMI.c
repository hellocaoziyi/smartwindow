/****
名称：串口屏
作者：曹梓艺
*****/

#include "./HMI/HMI.h"
#include "bsp_SysTick.h"

uint8_t RecevData[10];
int functionFLAG;
int ENDFLAG;

/****串口屏数据返回，定时执行进行数据查询，相当于按键使用*****/

void HMI(void)
{
			if(ENDFLAG==1)
		{
			ENDFLAG=0;
			switch (RecevData[0])
			{
				case 0x65:
				{
							if(RecevData[1]==0x00)
						{
									switch (RecevData[2])
									{
										case 0x01:functionFLAG=1;break;
										case 0x02:functionFLAG=2;break;
										case 0x03:functionFLAG=3;break;
									}
						}
						break;
				}
				default :
				{
					   u1_printf("未找到匹配项！！！！");
				}
			}
		}
}
int HMI_Scan(void)
{
			if(ENDFLAG==1)
		{
			ENDFLAG=0;
			switch (RecevData[0])
			{
				case 0x65:
				{
							if(RecevData[1]==0x01)
						{
							return RecevData[2];
//									switch (RecevData[2])
//									{
//										case 0x01:return 1;
//										case 0x02:return 2;
//										case 0x03:return 3;
//									}
						}
						break;
				}
				default :
				{
					   u1_printf("未找到匹配项！！！！");
				}
			}
		}
		return 0;
}
int HMI_get_ip(void)
{
	int i;
			if(ENDFLAG==1)
		{
			ENDFLAG=0;
			switch (RecevData[0])
			{
				case 0x65:
				{
							if(RecevData[1]==0x00)
						{
								switch(RecevData[2])
                {
									case 0x01:
									{
										for(i=3;i<20;i++)
										{
											if(RecevData[i]==0xFF)
											{
												return 0;
											}
											else
											{
											}
										}
										break;
									}
								  case 0x02:
									{
										return 1;
									}
								}									
						}
						break;
				}
				default :
				{
					   u1_printf("未找到匹配项！！！！");
				}
			}
		}
		return 2;
}
void HMI_clear(void)
{
	int i;
	for(i=0;i<16;i++){u4_HMIprintfhead(i);u4_HMIprintfend();SysTick_Delay_Ms(5);}
}
void HMI_clearline(int i)
{
  u4_HMIprintfhead(i);u4_HMIprintfend();SysTick_Delay_Ms(10);
}
/*****end of file******/
