#include "bsp.h"
#include "stm32f10x.h"
void bsp_gpio_Init( void )
{
    GPIO_InitTypeDef  gpio_init;
					  																															/*************PortA************/	
		
		/* GPS_POWEN | GPS_RTC_POW | GSM_POWON */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    gpio_init.GPIO_Pin   = BSP_GPIOA_GPS_POWEN | BSP_GPIOA_GPS_RTC_POW | BSP_GPIOA_GSM_POWON;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOA, &gpio_init);

																																					/*************PortB************/
		/* K_SW_L | ACC_OUT | LIN_NSLEEP | SP3232EN | LED_DATA | LED_RUN | HCAN1_STB */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  	gpio_init.GPIO_Pin   = BSP_GPIOB_K_SW_L | BSP_GPIOB_ACC_OUT | BSP_GPIOB_LIN_NSLEEP | BSP_GPIOB_SP3232EN |  BSP_GPIOB_LED_DATA | BSP_GPIOB_LED_RUN |
  												 BSP_GPIOB_HCAN1_STB;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &gpio_init);
	
		/* AD_IN */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    gpio_init.GPIO_Pin   = BSP_GPIOB_AD_DET;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &gpio_init);
		
																																					/*************PortC************/
		/* ACC_INT1 | GSM_RING | WAKEUP | GSM_POWDET */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    gpio_init.GPIO_Pin   = BSP_GPIOC_ACC_INT1 	| BSP_GPIOC_GSM_RING | BSP_GPIOC_GSM_POWDET;
    gpio_init.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &gpio_init);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    gpio_init.GPIO_Pin   = BSP_GPIOC_WAKEUP;
    gpio_init.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &gpio_init);

		/* GSM_DTR | FLASH_WP | FLASH_CS | SPAKEREN | GSM_POWEN*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    gpio_init.GPIO_Pin   = BSP_GPIOC_GSM_DTR | BSP_GPIOC_FLASH_WP 	|  BSP_GPIOC_FLASH_CS | BSP_GPIOC_SPAKEREN | 
    											 BSP_GPIOC_GSM_POWEN;	     											 
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOC, &gpio_init);
    
    /*CAN1_INT*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    gpio_init.GPIO_Pin   = BSP_GPIOC_CAN1_INT;	     											 
    gpio_init.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOC, &gpio_init);

																																					/*************PortD************/																																					
		/* SCAN2_MODE1 | SCAN2_MODE0 | CON_04 | CON_03 | CON_02 | CON_01 */
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
     gpio_init.GPIO_Pin   = BSP_GPIOD_SCAN2_MODE1 | BSP_GPIOD_SCAN2_MODE0;	     											 
     gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
     gpio_init.GPIO_Mode  = GPIO_Mode_Out_PP;
 		GPIO_Init(GPIOD, &gpio_init);
	
																																					/*************PortE************/																																				
		/* CAN_POWEN | CAN2_SW | FCAN2_STB */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    gpio_init.GPIO_Pin   = BSP_GPIOE_CAN_POWEN | BSP_GPIOE_CAN2_SW 	|  BSP_GPIOE_FCAN2_STB;   											 
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOE, &gpio_init);
		
		// Port_A //		
		/* GPS_POWEN=0 | GPS_RTC_POW=0 | GSM_POWON */	
		GPIO_ResetBits(GPIOA,	BSP_GPIOA_GPS_POWEN  | BSP_GPIOA_GPS_RTC_POW | BSP_GPIOA_GSM_POWON);

		// Port_B //
		/* K_SW_L=0 | ACC_OUT=0 | LIN_NSLEEP=0 | SP3232EN=0 | LED_DATA=1 | LED_RUN=1 | HCAN1_STB=1(Sleep mode) */	
		GPIO_ResetBits(GPIOB,	BSP_GPIOB_K_SW_L | BSP_GPIOB_ACC_OUT | BSP_GPIOB_LIN_NSLEEP | BSP_GPIOB_SP3232EN);
		GPIO_SetBits	(GPIOB,	BSP_GPIOB_LED_DATA | BSP_GPIOB_LED_RUN | BSP_GPIOB_HCAN1_STB);	

		// Port_C //
		/* GSM_DTR=0(GSM Don't sleep) | FLASH_WP=1 | FLASH_CS=1 | SPAKEREN=0 | GSM_POWEN=0 | GSM_RESET=0 */
		GPIO_ResetBits(GPIOC,	BSP_GPIOC_GSM_DTR | BSP_GPIOC_SPAKEREN | BSP_GPIOC_GSM_POWEN);
	  GPIO_SetBits	(GPIOC,	BSP_GPIOC_FLASH_WP | BSP_GPIOC_FLASH_CS);
	
		// Port_D //		
		/* SCAN2_MODE1=0(Sleep mode) | SCAN2_MODE0=0(Sleep mode) | CON_04=0 | CON_03=0 | CON_02=0 | CON_01=0 */	
		GPIO_ResetBits(GPIOD,	BSP_GPIOD_SCAN2_MODE1  | BSP_GPIOD_SCAN2_MODE0);
	
		// Port_E //
		/* FCAN2_STB=1(Sleep mode) | CAN_POWEN=0 | CAN2_SW=0(Default FS-CAN) */
		GPIO_ResetBits(GPIOE,	BSP_GPIOE_CAN_POWEN | BSP_GPIOE_CAN2_SW);
	  GPIO_SetBits	(GPIOE,	BSP_GPIOE_FCAN2_STB);

		GPIO_ResetBits		(GPIOB, BSP_GPIOB_LED_RUN); //电源指示
   // GPIO_ResetBits		(GPIOB, BSP_GPIOB_LED_DATA);

    //CAN的IO配置
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2 , ENABLE );

    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;

    // Configure CAN1 pin: RX
    gpio_init.GPIO_Pin = GPIO_Pin_11;
    gpio_init.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init( GPIOA, &gpio_init );

    //Configure CAN1 pin: TX
    gpio_init.GPIO_Pin = GPIO_Pin_12;
    gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init( GPIOA, &gpio_init );

    //Configure CAN2 pin: RX
    gpio_init.GPIO_Pin = GPIO_Pin_12;
    gpio_init.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init( GPIOB, &gpio_init );

    //Configure CAN2 pin: TX
    gpio_init.GPIO_Pin = GPIO_Pin_13;
    gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init( GPIOB, &gpio_init );


    gpio_init.GPIO_Pin = GPIO_Pin_15 ;
    gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init( GPIOB, &gpio_init );

    gpio_init.GPIO_Pin = GPIO_Pin_15 ;
    gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init( GPIOE, &gpio_init );

    //CAN2 select double line can
    gpio_init.GPIO_Pin = GPIO_Pin_13;
    gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init( GPIOE, &gpio_init );

    GPIO_ResetBits( GPIOE, GPIO_Pin_13 );

    //允许can线
    GPIO_ResetBits( GPIOB, GPIO_Pin_15 );
    GPIO_ResetBits( GPIOE, GPIO_Pin_15 );
}

void bsp_NVCI_Configuration( void )
{
		NVIC_InitTypeDef NVIC_InitStructure;
	

		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0xA000);
		
		/* Configure one bit for preemption priority */
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
		/* USART3_IRQn 中断 [K] */
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 11;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		
		/* CAN1_IRQn中断  [OBD]*/
		NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;	
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		/* CAN2_IRQn中断  [Car Control CAN Bus]*/
		NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		/* WAKEUP_DET低脉冲中断	[IO]*/
		NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		/* RING_DET中断	[IO]*/
		NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		/* UART5_RX中断	[IO]*/
		NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 9;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		/* ACCINT1_DET中断	[IO]*/
		NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 10;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		/* UART4_IRQn 中断 [Debug] */
		NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		/* RTC_Arlam中断		[RTC]*/
		NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 12;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		/* CAN1_RXD,CAN2_RXD LIN_INH中断 [IO]*/
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 13;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

}

void bsp_canx_init( CAN_TypeDef* canx , DWORD u32CanBaud )
{
		CAN_InitTypeDef        CAN_InitStructure;
		CAN_DeInit( canx );
		CAN_StructInit( &CAN_InitStructure );
		CAN_InitStructure.CAN_TTCM = DISABLE;
		CAN_InitStructure.CAN_ABOM = DISABLE;
		CAN_InitStructure.CAN_AWUM = DISABLE;
		CAN_InitStructure.CAN_NART = DISABLE;
		CAN_InitStructure.CAN_RFLM = DISABLE;
		CAN_InitStructure.CAN_TXFP = DISABLE;
		CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;//CAN_Mode_LoopBack;// 
		CAN_InitStructure.CAN_SJW = u32CanBaud >> 24;
		CAN_InitStructure.CAN_BS1 = ( u32CanBaud >> 16 ) & 0xff;
		CAN_InitStructure.CAN_BS2 = ( u32CanBaud >> 8 ) & 0xff;
		CAN_InitStructure.CAN_Prescaler = u32CanBaud & 0xff;;
		CAN_Init( canx, &CAN_InitStructure );
}

void bsp_can_filter_mask(BYTE u8FilterGroup, DWORD u32FilterId ,DWORD idmask)
{
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    CAN1->FA1R &= ~( 0x1 << u8FilterGroup );
    CAN_FilterInitStructure.CAN_FilterNumber = u8FilterGroup;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh =
        ( u32FilterId > 0x7ff ) ? ( ( ( u32FilterId << 3 ) & 0xFFFF0000 ) >> 16 ) : ( ( ( u32FilterId << 21 ) & 0xffff0000 ) >> 16 ) ;
    CAN_FilterInitStructure.CAN_FilterIdLow =
        ( u32FilterId > 0x7ff ) ? ( ( ( u32FilterId << 3 ) | CAN_ID_EXT | CAN_RTR_DATA ) & 0xFFFF ) : ( ( ( u32FilterId << 21 ) | CAN_ID_STD | CAN_RTR_DATA ) & 0xffff );
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (idmask<<3)>>16;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = idmask<<3;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit( &CAN_FilterInitStructure );
}

void bsp_usart_baud_init( USART_TypeDef* USARTx, DWORD u32UsartBaud )
{
		GPIO_InitTypeDef        gpio_init;
  	USART_InitTypeDef      usart_initstructure;
		USART_ClockInitTypeDef  usart_clk_init;
	  
	  if(USARTx == UART4)
		{
			//调试串口
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
																																	/* Configure GPIOC.10 as push-pull                       */
			gpio_init.GPIO_Pin   = GPIO_Pin_10;
			gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
			gpio_init.GPIO_Mode  = GPIO_Mode_AF_PP;
			GPIO_Init(GPIOC, &gpio_init);

																																	/* Configure GPIOC.11 as input floating                 */
			gpio_init.GPIO_Pin   = GPIO_Pin_11;
			gpio_init.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOC, &gpio_init);
		}
    else if(USARTx == USART3)
		{
			//K线串口
			bsp_fun_obd_Kline_init();
		}
	
		USART_DeInit(USARTx);
		usart_initstructure.USART_BaudRate = u32UsartBaud;
		usart_initstructure.USART_WordLength =USART_WordLength_8b;
		usart_initstructure.USART_StopBits = USART_StopBits_1;
		usart_initstructure.USART_Parity =USART_Parity_No;
		usart_initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		usart_initstructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USARTx, &usart_initstructure);
	
		usart_clk_init.USART_Clock           = USART_Clock_Disable;
    usart_clk_init.USART_CPOL            = USART_CPOL_Low;
    usart_clk_init.USART_CPHA            = USART_CPHA_2Edge;
    usart_clk_init.USART_LastBit         = USART_LastBit_Disable;
	
		USART_Init(USARTx, &usart_initstructure);
		USART_ClockInit(USARTx, &usart_clk_init);
		
		// Clean interrupt flag, and disable txd & rxd interrupt
		USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);
		USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);

		USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
		USART_ClearITPendingBit(USARTx, USART_IT_TXE);
				
		USART_Cmd(USARTx, ENABLE);			
}
void bsp_systick_init( void )
{
    RCC_ClocksTypeDef  RccClocks;
    DWORD u32cnts;
    RCC_GetClocksFreq( &RccClocks );
    u32cnts = ( DWORD )RccClocks.HCLK_Frequency / OS_TICKS_PER_SEC;
    SysTick_Config( u32cnts );
}
void bsp_fun_obd_Kline_init( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //使能对应外设时钟,串口2用于和手机端通讯,串口3,can1用于和ECU通讯,定时器2用于
    //许多功能
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
    //请看具体功能
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    //B端口浮空管脚配置
    GPIO_InitStructure.GPIO_Pin = ISO14230_KLINE_RXPIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init( ISO14230_KLINE_PORT, &GPIO_InitStructure );

    //B端口推挽管脚配置
    GPIO_InitStructure.GPIO_Pin = ISO14230_KLINE_TXPIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init( ISO14230_KLINE_PORT, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = ISO14230_LLINE_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init( GPIOB, &GPIO_InitStructure );

    ISO14230_LLINE_RESET;
    ISO14230_KLINE_SET;
}

void bsp_SystemInit( void )
{
		//RCC_ClocksTypeDef RCC_ClockFreq;	
		SystemInit();		
		//RCC_GetClocksFreq(&RCC_ClockFreq);
}
