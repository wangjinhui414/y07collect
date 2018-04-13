/**
  ******************************************************************************
  * @file    CAN/DualCAN/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "ucos_ii.h"
#include "app_cfg.h"
#include "pc_task.h"
#include "ecu_task.h"
#include "main.h"
#include <string.h>
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup CAN_DualCAN
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CanRxMsg RxMessage;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */


/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/


/**
  * @brief  This function handles CAN1 RX0 Handler.
  * @param  None
  * @retval None
  */
void CAN1_RX1_IRQHandler(void)
{


}



CanRxMsg RxMessage;

void CAN1_RX0_IRQHandler(void)
{
   	DWORD time = OSTimeGet();
	  
  	OS_CPU_SR  cpu_sr;
    OS_ENTER_CRITICAL();
    OSIntNesting++;
    OS_EXIT_CRITICAL();
    
    if( CAN_GetITStatus( CAN1, CAN_IT_FMP0 ) != RESET )
    {
        memset(RxMessage.Data,0,8);
  			CAN_Receive( CAN1, CAN_FIFO0, &RxMessage );
				if(RxMessage.IDE == 0)
				{ 
						send_buffer[0] = 0x08;
						send_buffer[1] = RxMessage.StdId>>24;
						send_buffer[2] = RxMessage.StdId>>16;
						send_buffer[3] = RxMessage.StdId>>8;
						send_buffer[4] = RxMessage.StdId;		 					
				}
				else
				{
						send_buffer[0] = 0x88;
						send_buffer[1] = RxMessage.ExtId>>24;
						send_buffer[2] = RxMessage.ExtId>>16;
						send_buffer[3] = RxMessage.ExtId>>8;
						send_buffer[4] = RxMessage.ExtId;		 
				}

				memcpy(&send_buffer[5],RxMessage.Data,RxMessage.DLC);
				memcpy(&send_buffer[13],&time,4);
				send_buffer[17] = RxMessage.DLC;
				send_offset =18;
				OSSemPost( g_pstMsgToEcu );
    }

    OSIntExit();	
}
void CAN2_RX0_IRQHandler(void)
{
   	DWORD time = OSTimeGet();
	  
  	OS_CPU_SR  cpu_sr;
    OS_ENTER_CRITICAL();
    OSIntNesting++;
    OS_EXIT_CRITICAL();
    
    if( CAN_GetITStatus( CAN2, CAN_IT_FMP0 ) != RESET )
    {
        memset(RxMessage.Data,0,8);
  			CAN_Receive( CAN2, CAN_FIFO0, &RxMessage );
				if(RxMessage.IDE == 0)
				{ 
						send_buffer[0] = 0x08;
						send_buffer[1] = RxMessage.StdId>>24;
						send_buffer[2] = RxMessage.StdId>>16;
						send_buffer[3] = RxMessage.StdId>>8;
						send_buffer[4] = RxMessage.StdId;		 					
				}
				else
				{
						send_buffer[0] = 0x88;
						send_buffer[1] = RxMessage.ExtId>>24;
						send_buffer[2] = RxMessage.ExtId>>16;
						send_buffer[3] = RxMessage.ExtId>>8;
						send_buffer[4] = RxMessage.ExtId;		 
				}
				memcpy(&send_buffer[5],RxMessage.Data,RxMessage.DLC);
				memcpy(&send_buffer[13],&time,4);
				send_buffer[17] = RxMessage.DLC;
				send_offset =18;
				OSSemPost( g_pstMsgToEcu );
    }
    OSIntExit();	
}
/**
  * @brief  This function handles CAN2 RX0 Handler.
  * @param  None
  * @retval None
  */


DWORD pcframetime = 0;
DWORD Kframetime = 0;
void USART2_IRQHandler(void)
{ 
		OS_CPU_SR  cpu_sr;
		OS_ENTER_CRITICAL();
		OSIntNesting++;
		OS_EXIT_CRITICAL();	

		OSIntExit();	
}

void USART3_IRQHandler(void)
{
		OS_CPU_SR  cpu_sr;
		OS_ENTER_CRITICAL();
		OSIntNesting++;
		OS_EXIT_CRITICAL();	
		Kframetime = OSTimeGet();
		if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)	   //ÅÐ¶Ï¶Á¼Ä´æÆ÷ÊÇ·ñ·Ç¿Õ
		{	   
			send_buffer[send_offset++] =  USART_ReceiveData(USART3);
		}
		OSIntExit();	
}
void UART4_IRQHandler(void)
{
		OS_CPU_SR  cpu_sr;
		OS_ENTER_CRITICAL();
		OSIntNesting++;
		OS_EXIT_CRITICAL();	
	  pcframetime = OSTimeGet();
		if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)	   //ÅÐ¶Ï¶Á¼Ä´æÆ÷ÊÇ·ñ·Ç¿Õ
		{	   
			recv_buffer[recv_offset++] =  USART_ReceiveData(UART4);
		}
		OSIntExit();	
}
extern BYTE g_bytetime;
void SysTick_Handler(void)
{
    OS_CPU_SR  cpu_sr;   
    OS_ENTER_CRITICAL();
    OSIntNesting++;
    OS_EXIT_CRITICAL();
	
    if(pcframetime!=0 && (OSTimeGet() - pcframetime) > 10)
		{
				OSSemPost( g_pstMsgToPc );
			  pcframetime = 0;
		}
		if(Kframetime!=0 && (OSTimeGet() - Kframetime) > g_bytetime)
		{
				OSSemPost( g_pstMsgToEcu );
			  Kframetime = 0;
		}
    OSTimeTick();
    OSIntExit();
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
