/*
***************************************************************
*该文件主要处理PC下发指令
***************************************************************
*/
#include "pc_task.h"
#include "bsp.h"
#include "string.h"

BYTE recv_buffer[255] = {0}; //PC接收缓冲区
BYTE recv_offset = 0;
BYTE send_buffer[300] = {0}; //发送PC缓冲区
BYTE send_offset = 0;
TYPEDEF_WORKMODE g_workmode = MODE_SIMULATION; //模拟器工作模式

//发送栏相关的变量
TYPE_BUSFRAMS g_allbusfram[250];//发送栏缓冲区
WORD g_busframetime = 2; //发送帧间隔
DWORD g_bustimes = 0;    //发送次数
BYTE g_busnum = 0;       //发送帧数量
//波特率选项
DWORD g_allbps[] = {CAN_B500K,CAN_B250K,CAN_B125K,CAN_B100K,CAN_B1000K,CAN_B83_3K,CAN_B50K,
                    10400,9600};

//时序变量
BYTE g_bytetime = 5;
BYTE g_frametime = 35;
BYTE g_waitanstime = 55;
WORD g_ecutimeout = 500;

//通道选择
CAN_TypeDef *CANx = CAN1;

//收到PC数据  处理
void fun_pc_task_start( void* pArg)
{
    BYTE u8Error;
  	while(1)
		{
			    OSSemPend( g_pstMsgToPc, 0, &u8Error );
					//设置指令 CAN采集模式
					if(recv_buffer[0] == MODE_COLLECTION && recv_buffer[1] <= 1)
					{
							BYTE i;
						  if(recv_buffer[1] == 0)
								CANx = CAN1;
							else if(recv_buffer[1] == 1)
								CANx = CAN2;
						  CAN_ITConfig( CAN1, CAN_IT_FMP0, DISABLE );
							CAN_ITConfig( CAN2, CAN_IT_FMP0, DISABLE );
							USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
						  CAN1->FA1R = 0;	
							//设置工作模式
							g_workmode = MODE_SIMULATION;
							//初始化CAN波特率
							bsp_canx_init( CANx , g_allbps[recv_buffer[2]]);
						  g_bytetime = recv_buffer[3];
						  g_frametime = recv_buffer[4];
						  g_waitanstime = recv_buffer[5];
						  g_ecutimeout = *(WORD*)&recv_buffer[6];
							for(i= 0;i!=recv_buffer[8];i++)
							{
								DWORD filterid = *(DWORD*)&recv_buffer[9+8*i+0];
								DWORD maskid =  *(DWORD*)&recv_buffer[9+8*i+4];
								//采集过滤ID和掩码设�
								if(CANx == CAN1)
									bsp_can_filter_mask( i , filterid, maskid);
								else
									bsp_can_filter_mask( i+14 , filterid, maskid);
							}
							if(!recv_buffer[8])
							{
								if(CANx == CAN1)
									bsp_can_filter_mask(0,0,0);
								else
									bsp_can_filter_mask(14,0,0);
							}
							USART_SendData(UART4, 0x55);                                   
							while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);							recv_offset = 0; //清楚下发缓冲
							send_offset = 0; //清楚上传缓冲
							CAN_ITConfig( CANx, CAN_IT_FMP0, ENABLE );
					}
					//设置指令 CAN模拟模式
					else if(recv_buffer[0] == MODE_SIMULATION && recv_buffer[1] <= 1)
					{
  						g_workmode = MODE_SIMULATION;
							if(recv_buffer[1] == 0)
								CANx = CAN1;
							else if(recv_buffer[1] == 1)
								CANx = CAN2;
						  CAN1->FA1R = 0;							CAN_ITConfig( CAN1, CAN_IT_FMP0, DISABLE );
 							CAN_ITConfig( CAN2, CAN_IT_FMP0, DISABLE );
							USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);							bsp_canx_init( CANx , g_allbps[recv_buffer[2]]);
							g_bytetime = recv_buffer[3];
						  g_frametime = recv_buffer[4];
						  g_waitanstime = recv_buffer[5];
						  g_ecutimeout = *(WORD*)&recv_buffer[6];
							if(CANx == CAN1)
								bsp_can_filter_mask(0,0,0);
							else
								bsp_can_filter_mask(14,0,0);
							USART_SendData(UART4, 0x55);                                   
							while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
							recv_offset = 0; //清楚下发缓冲
							send_offset = 0; //清楚上传缓冲
							CAN_ITConfig( CANx, CAN_IT_FMP0, ENABLE );
					}
					//发出扩展CAN帧数据
					else if( (recv_buffer[0] == 0x88 ||  recv_buffer[0] == 0x08 )&& g_workmode == MODE_SIMULATION) //下发发出的CAN数据   扩展CAN
					{
							CanTxMsg TxMessage;
						  DWORD filterid;
						  BYTE i = 0,framenum = recv_offset/0x0E;
							CAN_ITConfig( CANx, CAN_IT_FMP0, DISABLE );
						  OSTimeDlyHMSM( 0, 0, 0,g_waitanstime);
						  for(;i!=framenum;i++)
						  {
									filterid = recv_buffer[2+i*14]<<24 | recv_buffer[3+i*14]<<16 | recv_buffer[4+i*14]<<8 | recv_buffer[5+i*14];
									memcpy( &TxMessage.Data, &recv_buffer[6+i*14], 8 );									
									TxMessage.StdId = filterid;
									TxMessage.ExtId = filterid;
									TxMessage.RTR = 0;
									TxMessage.IDE = ( filterid > 0X7FF ) ? 4 : 0;
									TxMessage.DLC = recv_buffer[i*14+1];
								  while(CAN_Transmit(CANx,&TxMessage) == CAN_NO_MB);
								  OSTimeDlyHMSM( 0, 0, 0,g_frametime);
						  }
							recv_offset = 0;								
							CAN_ITConfig( CANx, CAN_IT_FMP0, ENABLE );														
					}
					//K线模式
          else if((recv_buffer[0] == MODE_COLLECTION || recv_buffer[0] == MODE_SIMULATION)
								&&  recv_buffer[1] > 1)
					{
							CAN_ITConfig( CAN1, CAN_IT_FMP0, DISABLE );
 							CAN_ITConfig( CAN2, CAN_IT_FMP0, DISABLE );
						  g_workmode = MODE_KLINE;
						  bsp_usart_baud_init( USART3,g_allbps[recv_buffer[2]]);
							USART_GetFlagStatus(USART3, USART_FLAG_TC);
							g_bytetime = recv_buffer[3];
						  g_frametime = recv_buffer[4];
						  g_waitanstime = recv_buffer[5];
						  g_ecutimeout = *(WORD*)&recv_buffer[6];
							USART_SendData(UART4, 0x55);                                   
							while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
						  recv_offset = 0;
							send_offset = 2;
							send_buffer[0] = 0X77;						
						  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
					}
					//K线模拟回复
					else if( recv_buffer[0] == 0x77&& g_workmode == MODE_KLINE) //下发CAN线回复
					{
							BYTE i = 1;
						  USART3->CR1 &= ~0X04;
							for(i = 1;i < recv_offset;i++)
							{
									USART_SendData(USART3, recv_buffer[i]);                                   
									while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
								  OSTimeDlyHMSM( 0, 0, 0,g_bytetime );
							}
							recv_offset = 0;
							USART3->CR1 |= 0X04;
					}
					//发送栏发送指令
					else if( recv_buffer[0] == 0xCC && g_workmode == MODE_SIMULATION)
					{
              BYTE i=0;
							g_busframetime =  *(WORD*)&recv_buffer[1] == 0 ? 1 :*(WORD*)&recv_buffer[1]; //不要设置0
						  g_bustimes =  *(WORD*)&recv_buffer[3];
						  g_busnum = recv_buffer[7];
						  if(g_busframetime == 0)
								g_busframetime =1;
						  for(i=0;i!=recv_buffer[7];i++)
						  {
								memcpy(g_allbusfram[i].onefram,&recv_buffer[8+i*13],13);
							}
							recv_offset = 0;
							OSTaskResume(APP_TASK_BUS_PRIO);
							OSSemPost( g_pstMsgToBus );
					}
					//发送栏取消发送指令
					else if( recv_buffer[0] == 0xDD && recv_buffer[1] == 0xDD && g_workmode == MODE_SIMULATION)
					{
              g_busframetime  = 10;
						  g_bustimes = 0;
						  g_busnum =0;												recv_offset = 0;
  						OSTaskSuspend(APP_TASK_BUS_PRIO);
					}
					else if(memcmp(recv_buffer,"$S_UPDATE",strlen("$S_UPDATE"))==0)
					{
							char *pcupde = "\r\nS_UPDATE=(OK!)\r\n";
							WORD i = 0;
              
							for(i = 0;i < strlen(pcupde);i++)
							{
									USART_SendData(UART4, pcupde[i]);                                   
									while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
							}
							WriteUpdataFlash();//更改bootload识别下载程序表示
							recv_offset = 0;							
  						NVIC_SystemReset();
						  while(1); 
					}							else if(memcmp(recv_buffer,"$HIDE_ALL",strlen("$HIDE_ALL"))==0)
					{
								char *pchide = "\r\nHIDE_ALL(OK!)\r\n";
								WORD i = 0;
								for(i = 0;i < strlen(pchide);i++)
								{
										USART_SendData(UART4, pchide[i]);                                   
										while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
								}
								recv_offset = 0;								
					}
					recv_offset = 0;
		}
	
}
void fun_bus_task_start( void* pArg)
{
     BYTE sendpos = 0;
	   DWORD sendtimes = 0;
	   BYTE u8Error;
	   CanTxMsg TxMessage;
     while(1)
		 {
					 OSSemPend( g_pstMsgToBus, 0, &u8Error );
					 while(1)
					 {
								if(sendpos >= g_busnum) //是否到一次循环
								{
                    sendtimes++;
  									if(sendtimes >= g_bustimes) //是否到循环次数
										{
												sendpos = 0;
												sendtimes = 0;
												break;
										}
										sendpos = 0;					
								}
								
								memcpy( &TxMessage.Data, &g_allbusfram[sendpos].onefram[4], 8 );						
								TxMessage.StdId = g_allbusfram[sendpos].onefram[0]<<24 |
																	g_allbusfram[sendpos].onefram[1]<<16 |
																	g_allbusfram[sendpos].onefram[2]<<8  |
																	g_allbusfram[sendpos].onefram[3];
								TxMessage.ExtId = TxMessage.StdId;
								TxMessage.RTR = 0;
								TxMessage.IDE = ( TxMessage.StdId > 0X7FF ) ? 4 : 0;
								TxMessage.DLC = g_allbusfram[sendpos].onefram[12];	
								CAN_Transmit( CANx, &TxMessage );
								sendpos++;
								OSTimeDlyHMSM( 0, 0, g_busframetime / 1000,g_busframetime % 1000 );
					}
		 }
}
BYTE g_8007800buff[1024];
void WriteUpdataFlash(void)
{
    const DWORD flagaddr = 0x8007800;
	  WORD i = 0,sum = 0;
  	FLASH_Unlock();
		memcpy(g_8007800buff,(BYTE*)flagaddr,1024);
	  g_8007800buff[4] = 0xA5;
	  g_8007800buff[5] = 0xA2;
	  for(i=4;i<0x10F;i++)
		{
			sum+=g_8007800buff[i] ;
		}
		memcpy(&g_8007800buff[2],&sum,2);
		FLASH_ErasePage(flagaddr);
		for(i=0;i!=1024/4;i++)
		{
         FLASH_ProgramWord(flagaddr+i*4,*(DWORD*)&g_8007800buff[i*4]);
		}
		FLASH_Lock();
}

