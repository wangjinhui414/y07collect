#include "app_cfg.h"
#include "main.h"
#include "bsp.h"
#include "string.h"
OS_STK		STK_TASK_START[APP_TASK_START_SIZE];
OS_STK		STK_TASK_PC[APP_TASK_PC_SIZE];
OS_STK		STK_TASK_ECU[APP_TASK_ECU_SIZE];
OS_STK		STK_TASK_BUS[APP_TASK_BUS_SIZE];

OS_EVENT *g_pstMsgToEcu = NULL;
OS_EVENT *g_pstMsgToPc = NULL;
OS_EVENT *g_pstMsgToBus = NULL;


int main(void)
{
		INT8U  os_err;
	
		SysTick->CTRL  = SysTick_CTRL_ENABLE_Msk; //禁用所有中断	
	  bsp_SystemInit();                         //时钟源初始化
		bsp_NVCI_Configuration();   	            //中断设置
		bsp_gpio_Init();                          //IO口初始化
	
		OSInit();
    OSTaskCreateExt(
        fun_app_task_start,
        ( void * ) 0,
        ( OS_STK * ) &STK_TASK_START[APP_TASK_START_SIZE-1],
        APP_TASK_START_PRIO,
        APP_TASK_START_PRIO,
        ( OS_STK * ) &STK_TASK_START[0],
        APP_TASK_START_SIZE,
        ( void * ) 0,
        OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR );
				
    OSTaskNameSet( APP_TASK_START_PRIO, (INT8U*)"Head Task!", &os_err );
    OSStart();
    return ( 0 );
}

void fun_app_task_start( void* pArg)
{
		OS_CPU_SR cpu_sr=0;
    //CanTxMsg TxMessage;
	  g_pstMsgToEcu = OSSemCreate( 0 );
	  g_pstMsgToPc = OSSemCreate( 0 );
    g_pstMsgToBus = OSSemCreate( 0 );
	    bsp_systick_init();//系统滴答设置

    //PC通讯串口初始化
  	bsp_usart_baud_init( UART4,115200);
	  USART_GetFlagStatus(UART4, USART_FLAG_TC);
	
	  bsp_usart_baud_init( USART3,10400);
	  USART_GetFlagStatus(USART3, USART_FLAG_TC);
//	{
//		//			BYTE buffer[11] = {0x8A,0XF1,0X10,0X61,0XDF,0X21,0X02,0X03,0X04,0X05,0XFA};
//			int o = 0;

//		BYTE buffer1[5] = {0x81,0x10,0xF1,0x81,0x03};
//		while(1)
//		{
//									USART_SendData(USART3, buffer1[o++]);                                   
//						while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
//			      OSTimeDlyHMSM( 0, 0, 0,5);
//			      if(o==5)
//						{
//							 o=0;
//							OSTimeDlyHMSM( 0, 0, 0,500);
//						}
//		}

//	}		
		GPIO_SetBits			(GPIOE, BSP_GPIOE_CAN_POWEN);
  	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	  //USART_SendData(UART4, 0xAA);

    //初始化默认CAN 接收500K数据所有ID数据
		bsp_canx_init( CAN1 , CAN_B500K); 
		bsp_can_filter_mask(0,0,0);    	
	  CAN_ITConfig( CAN1, CAN_IT_FMP0, ENABLE );

     



OS_ENTER_CRITICAL();
  	OSTaskCreateExt(
			fun_pc_task_start,
			( void * ) 0,
			( OS_STK * ) &STK_TASK_PC[APP_TASK_PC_SIZE-1],
			APP_TASK_PC_PRIO,
			APP_TASK_PC_PRIO,
			( OS_STK * ) &STK_TASK_PC[0],
			APP_TASK_PC_SIZE,
			( void * ) 0,
			OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR );
			
		OSTaskCreateExt(
			fun_ecu_task_start,
			( void * ) 0,
			( OS_STK * ) &STK_TASK_ECU[APP_TASK_ECU_SIZE-1],
			APP_TASK_ECU_PRIO,
			APP_TASK_ECU_PRIO,
			( OS_STK * ) &STK_TASK_ECU[0],
			APP_TASK_ECU_SIZE,
			( void * ) 0,
			OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR );
			
		OSTaskCreateExt(
			fun_bus_task_start,
			( void * ) 0,
			( OS_STK * ) &STK_TASK_BUS[APP_TASK_BUS_SIZE-1],
			APP_TASK_BUS_PRIO,
			APP_TASK_BUS_PRIO,
			( OS_STK * ) &STK_TASK_BUS[0],
			APP_TASK_BUS_SIZE,
			( void * ) 0,
			OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR );

		OSTaskSuspend(APP_TASK_START_PRIO);
			
		OS_EXIT_CRITICAL();	

}
