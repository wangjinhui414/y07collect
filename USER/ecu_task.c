/*
***************************************************************
*该文件主要处理ECU数据上传
***************************************************************
*/

#include "ecu_task.h"
#include "main.h"
#include "pc_task.h"#include "bsp.h"
#include <string.h>
extern BYTE g_workmode;
//收到ECU数据后上传PC
void fun_ecu_task_start( void* pArg)
{
	BYTE u8Error;	BYTE i;
	BYTE cout = 0;
	static DWORD ledtime = 0;
	static BYTE ledstaus = 0;
   	while(1)
		{
        OSSemPend( g_pstMsgToEcu, 0, &u8Error );
				if((OSTimeGet() - ledtime)>500)
				{
						if(ledstaus)
						{
								GPIO_SetBits		(GPIOB, BSP_GPIOB_LED_DATA);
								ledstaus=!ledstaus;
						}
						else
						{
								GPIO_ResetBits		(GPIOB, BSP_GPIOB_LED_DATA);
								ledstaus=!ledstaus;
						}
					ledtime = OSTimeGet();
				}
				if(g_workmode != MODE_KLINE)//CAN线的上传
				{
						CAN_ITConfig( CANx, CAN_IT_FMP0, DISABLE );
						for(i = 0;i < send_offset;i++)
						{
								USART_SendData(UART4, send_buffer[i]);                                   
								while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
								//
						}
						send_offset = 0;
						CAN_ITConfig( CANx, CAN_IT_FMP0, ENABLE );
						if(cout++ == 0xFF)
							OSTimeDlyHMSM( 0, 0, 0,10);
				}
			else	if(g_workmode == MODE_KLINE)
			{
				 send_buffer[1] = send_offset-2;
				 memcpy(&send_buffer[send_offset],(BYTE*)&ledtime,4);
         send_offset+=4;				
				for(i = 0;i < send_offset;i++)
				{
						USART_SendData(UART4, send_buffer[i]);                                   
						while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
						//
				}							
				memset(&send_buffer[1],0,send_offset+1);
				send_offset = 2;
			}				
		}				
}
