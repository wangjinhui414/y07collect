/*
***************************************************************
*¸ÃÎÄ¼þÖ÷Òª´¦ÀíPCÏÂ·¢Ö¸Áî
***************************************************************
*/
#include "pc_task.h"
#include "bsp.h"
#include "string.h"

BYTE recv_buffer[255] = {0}; //PC½ÓÊÕ»º³åÇø
BYTE recv_offset = 0;
BYTE send_buffer[300] = {0}; //·¢ËÍPC»º³åÇø
BYTE send_offset = 0;
TYPEDEF_WORKMODE g_workmode = MODE_SIMULATION; //Ä£ÄâÆ÷¹¤×÷Ä£Ê½

//·¢ËÍÀ¸Ïà¹ØµÄ±äÁ¿
TYPE_BUSFRAMS g_allbusfram[250];//·¢ËÍÀ¸»º³åÇø
WORD g_busframetime = 2; //·¢ËÍÖ¡¼ä¸ô
DWORD g_bustimes = 0;    //·¢ËÍ´ÎÊý
BYTE g_busnum = 0;       //·¢ËÍÖ¡ÊýÁ¿
//²¨ÌØÂÊÑ¡Ïî
DWORD g_allbps[] = {CAN_B500K,CAN_B250K,CAN_B125K,CAN_B100K,CAN_B1000K,CAN_B83_3K,CAN_B50K,
                    10400,9600};

//Ê±Ðò±äÁ¿
BYTE g_bytetime = 5;
BYTE g_frametime = 35;
BYTE g_waitanstime = 55;
WORD g_ecutimeout = 500;

//Í¨µÀÑ¡Ôñ
CAN_TypeDef *CANx = CAN1;

//ÊÕµ½PCÊý¾Ý  ´¦Àí
void fun_pc_task_start( void* pArg)
{
    BYTE u8Error;
  	while(1)
		{
			    OSSemPend( g_pstMsgToPc, 0, &u8Error );
					//ÉèÖÃÖ¸Áî CAN²É¼¯Ä£Ê½
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
							//ÉèÖÃ¹¤×÷Ä£Ê½
							g_workmode = MODE_SIMULATION;
							//³õÊ¼»¯CAN²¨ÌØÂÊ
							bsp_canx_init( CANx , g_allbps[recv_buffer[2]]);
						  g_bytetime = recv_buffer[3];
						  g_frametime = recv_buffer[4];
						  g_waitanstime = recv_buffer[5];
						  g_ecutimeout = *(WORD*)&recv_buffer[6];
							for(i= 0;i!=recv_buffer[8];i++)
							{
								DWORD filterid = *(DWORD*)&recv_buffer[9+8*i+0];
								DWORD maskid =  *(DWORD*)&recv_buffer[9+8*i+4];
								//²É¼¯¹ýÂËIDºÍÑÚÂëÉèÖ
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
							while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);							recv_offset = 0; //Çå³þÏÂ·¢»º³å
							send_offset = 0; //Çå³þÉÏ´«»º³å
							CAN_ITConfig( CANx, CAN_IT_FMP0, ENABLE );
					}
					//ÉèÖÃÖ¸Áî CANÄ£ÄâÄ£Ê½
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
							recv_offset = 0; //Çå³þÏÂ·¢»º³å
							send_offset = 0; //Çå³þÉÏ´«»º³å
							CAN_ITConfig( CANx, CAN_IT_FMP0, ENABLE );
					}
					//·¢³öÀ©Õ¹CANÖ¡Êý¾Ý
					else if( (recv_buffer[0] == 0x88 ||  recv_buffer[0] == 0x08 )&& g_workmode == MODE_SIMULATION) //ÏÂ·¢·¢³öµÄCANÊý¾Ý   À©Õ¹CAN
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
					//KÏßÄ£Ê½
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
					//KÏßÄ£Äâ»Ø¸´
					else if( recv_buffer[0] == 0x77&& g_workmode == MODE_KLINE) //ÏÂ·¢CANÏß»Ø¸´
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
					//·¢ËÍÀ¸·¢ËÍÖ¸Áî
					else if( recv_buffer[0] == 0xCC && g_workmode == MODE_SIMULATION)
					{
              BYTE i=0;
							g_busframetime =  *(WORD*)&recv_buffer[1] == 0 ? 1 :*(WORD*)&recv_buffer[1]; //²»ÒªÉèÖÃ0
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
					//·¢ËÍÀ¸È¡Ïû·¢ËÍÖ¸Áî
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
							WriteUpdataFlash();//¸ü¸ÄbootloadÊ¶±ðÏÂÔØ³ÌÐò±íÊ¾
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
								if(sendpos >= g_busnum) //ÊÇ·ñµ½Ò»´ÎÑ­»·
								{
                    sendtimes++;
  									if(sendtimes >= g_bustimes) //ÊÇ·ñµ½Ñ­»·´ÎÊý
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

