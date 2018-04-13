#ifndef _BSP_H_
#define _BSP_H_
#include "app_cfg.h"

//#define CAN_B500K           0x00070204
//#define CAN_B250K           0x00070208
//#define CAN_B125K           0x00070210
//#define CAN_B83_3K          0x00070218
//#define CAN_B50K            0x00070228
//#define CAN_B33_3K          0x0007023c
#define CAN_B500K	0x00070206
#define CAN_B250K	0x000D0208
#define CAN_B125K	0x000D0216
#define CAN_B100K	0x000F0212
#define CAN_B1000K	0x00040204
#define CAN_B83_3K	0x000a0510
#define CAN_B50K	0x00090420


/************************I/O DEFINES(For GT Series hardware V2.0 100 pin)****************************/
																											/* -------------------- GPIOA PINS -------------------- */
#define  BSP_GPIOA_GPS_POWEN					GPIO_Pin_0			/* I/O  GPS POWON.																			*/
#define  BSP_GPIOA_AIN                GPIO_Pin_1    	/* POW12V AIN                                    				*/ 
#define  BSP_GPIOA_USART2_TX          GPIO_Pin_2    	/* GPS TXD.                                           	*/
#define  BSP_GPIOA_USART2_RX          GPIO_Pin_3    	/* GPS RXD.                                           	*/
#define  BSP_GPIOA_GPS_RTC_POW				GPIO_Pin_4    	/* I/O  GPS RTC POW.                                 		*/
#define  BSP_GPIOA_SPI1_SCK						GPIO_Pin_5    	/* FLASH SCK.                                      			*/
#define  BSP_GPIOA_SPI1_MISO					GPIO_Pin_6    	/* FLASH MISO.                                     			*/
#define  BSP_GPIOA_SPI1_MOSI					GPIO_Pin_7    	/* FLASH MOSI.                                     			*/
#define  BSP_GPIOA_GSM_POWON					GPIO_Pin_8    	/* I/O  GSM POWON.                                      */
#define  BSP_GPIOA_USART1_TX					GPIO_Pin_9    	/* GSM	TXD.                                           	*/
#define  BSP_GPIOA_USART1_RX					GPIO_Pin_10    	/* GSM	RXD.                                           	*/
#define  BSP_GPIOA_CAN1_RX						GPIO_Pin_11    	/* CAN1 RX. H-CAN				                              	*/
#define  BSP_GPIOA_CAN1_TX  					GPIO_Pin_12    	/* CAN1_TX.                               							*/
#define  BSP_GPIOA_JTAG_TMS						GPIO_Pin_13    	/* JTAG TMS/SWDIO.                                      */
#define  BSP_GPIOA_JTAG_TCK						GPIO_Pin_14    	/* JTAG TCK/SWCLK.                                      */
#define  BSP_GPIOA_JTAG_TDI						GPIO_Pin_15    	/* NULL.                                            		*/

                                                      /* -------------------- GPIOB PINS -------------------- */
#define  BSP_GPIOB_AD_DET							GPIO_Pin_0    	/* AD . 用于I.O检测                                    	*/
#define  BSP_GPIOB_K_SW_L							GPIO_Pin_1    	/* I/O	K SW L.                                   			*/
#define  BSP_GPIOB_CPU_BOOT1					GPIO_Pin_2    	/* CPU  BOOT1.                                          */
#define  BSP_GPIOB_ACC_OUT						GPIO_Pin_3    	/* I/O                                            			*/
#define  BSP_GPIOB_LIN_NSLEEP					GPIO_Pin_4    	/* I/O                                           			  */
#define  BSP_GPIOB_SP3232EN						GPIO_Pin_5    	/* I/O	SP3232EN                                   			*/
#define  BSP_GPIOB_IIC_SCL						GPIO_Pin_6    	/* IIC  SCL.                                           	*/
#define  BSP_GPIOB_IIC_SDA						GPIO_Pin_7    	/* IIC  SDA.                                       			*/
#define  BSP_GPIOB_LED_DATA						GPIO_Pin_8    	/* I/O 	LED DATA.                          							*/
#define  BSP_GPIOB_LED_RUN						GPIO_Pin_9    	/* I/O 	LED RUN.                                				*/
#define  BSP_GPIOB_USART3_TX					GPIO_Pin_10    	/* K/LIN	TXD.                                          */
#define  BSP_GPIOB_USART3_RX					GPIO_Pin_11    	/* K/LIN	RXD.                                          */
#define  BSP_GPIOB_CAN2_RX						GPIO_Pin_12    	/* CAN2 RX.  SW-CAN/FS-CAN                         			*/
#define  BSP_GPIOB_CAN2_TX						GPIO_Pin_13    	/* CAN2 TX.                                       			*/
#define  BSP_GPIOB_NULL14							GPIO_Pin_14    	/* NULL                                      						*/
#define  BSP_GPIOB_HCAN1_STB					GPIO_Pin_15    	/* I/O	CAN1 STB.                                      	*/


                                                      /* -------------------- GPIOC PINS -------------------- */
#define  BSP_GPIOC_ACC_INT1						GPIO_Pin_0    	/* ACC 	INT1#.																					*/
#define  BSP_GPIOC_GSM_RING						GPIO_Pin_1    	/* GSM  RING#.	 																				*/
#define  BSP_GPIOC_GSM_DTR					  GPIO_Pin_2    	/* GSM  DTR.	 																					*/
#define  BSP_GPIOC_WAKEUP							GPIO_Pin_3    	/* I/O  WAKEUP#. 																				*/
#define  BSP_GPIOC_FLASH_WP						GPIO_Pin_4    	/* I/O 	FLASH WP.                                      	*/
#define  BSP_GPIOC_FLASH_CS						GPIO_Pin_5    	/* I/O	FLASH CS .                                      */
#define	 BSP_GPIOC_SPAKEREN						GPIO_Pin_6			/* I/O	SPAKER EN .																			*/
#define  BSP_GPIOC_GSM_POWDET					GPIO_Pin_7    	/* I/O	GSM POW DET .                                   */
#define  BSP_GPIOC_GSM_POWEN					GPIO_Pin_8    	/* I/O 	POWER EN.                                       */
#define  BSP_GPIOC_CAN1_INT 					GPIO_Pin_9    	/* I/O  CAN1 interupt.   	                                  */
#define  BSP_GPIOC_UART4_TX						GPIO_Pin_10    	/* DBG TXD                               								*/
#define  BSP_GPIOC_UART4_RX						GPIO_Pin_11    	/* DBG RXD.                                        	  	*/
#define  BSP_GPIOC_UART5_TX						GPIO_Pin_12    	/* LIN TXD.                                      	  		*/
#define  BSP_GPIOC_NULL1							GPIO_Pin_13    	/* NULL1.																								*/
#define  BSP_GPIOC_OSC32_IN						GPIO_Pin_14    	/* OSC32.768 IN.                                        */
#define  BSP_GPIOC_OSC32_OUT					GPIO_Pin_15    	/* OSC32.768 OUT.                                       */

                                                      /* -------------------- GPIOD PINS -------------------- */
#define  BSP_GPIOD_OSC_IN							GPIO_Pin_0    	/* OSC  IN                       												*/
#define  BSP_GPIOD_OSC_OUT						GPIO_Pin_1    	/* OSC	OUT                        											*/
#define  BSP_GPIOD_UART5_RX						GPIO_Pin_2    	/* LIN RXD.                                          		*/
#define  BSP_GPIOD_NULL3							GPIO_Pin_3    	/* NULL.                                    						*/
#define  BSP_GPIOD_NULL4							GPIO_Pin_4    	/* NULL.                                								*/
#define  BSP_GPIOD_NULL5							GPIO_Pin_5    	/* NULL.                                 								*/
#define  BSP_GPIOD_NULL6							GPIO_Pin_6    	/* NULL.                                  							*/
#define  BSP_GPIOD_NULL7							GPIO_Pin_7    	/* NULL.                                  							*/
#define  BSP_GPIOD_NULL8							GPIO_Pin_8    	/* NULL. 																								*/
#define  BSP_GPIOD_SCAN2_MODE1				GPIO_Pin_9    	/* SW CAN MODE1.                                 				*/
#define  BSP_GPIOD_SCAN2_MODE0				GPIO_Pin_10    	/* SW CAN MODE0.                                    		*/
#define  BSP_GPIOD_NULL11							GPIO_Pin_11    	/* NULL.                                  							*/
#define  BSP_GPIOD_CON_04							GPIO_Pin_12    	/* I/O.                                   							*/
#define  BSP_GPIOD_CON_03							GPIO_Pin_13    	/* I/O.                                   		 					*/
#define  BSP_GPIOD_CON_02							GPIO_Pin_14    	/* I/O.                               									*/
#define  BSP_GPIOD_CON_01							GPIO_Pin_15    	/* I/O.																									*/

																											/* -------------------- GPIOE PINS -------------------- */
#define  BSP_GPIOE_NULL0							GPIO_Pin_0    	/* NULL.                                       					*/
#define  BSP_GPIOE_NULL1							GPIO_Pin_1    	/* NULL.                                     						*/
#define  BSP_GPIOE_NULL2							GPIO_Pin_2			/* NULL.																								*/
#define  BSP_GPIOE_NULL3							GPIO_Pin_3			/* NULL.																								*/
#define	 BSP_GPIOE_NULL4							GPIO_Pin_4			/* NULL.																								*/
#define  BSP_GPIOE_NULL5							GPIO_Pin_5			/* NULL.																								*/
#define  BSP_GPIOE_NULL6							GPIO_Pin_6    	/* NULL.                               									*/
#define  BSP_GPIOE_NULL7							GPIO_Pin_7    	/* NULL.																								*/																			
#define  BSP_GPIOE_NULL8							GPIO_Pin_8    	/* NULL.																								*/
#define  BSP_GPIOE_NULL9							GPIO_Pin_9    	/* NULL.                                    						*/
#define  BSP_GPIOE_NULL10							GPIO_Pin_10    	/* NULL.                                   							*/
#define  BSP_GPIOE_CAN_POWEN					GPIO_Pin_11    	/* I/O.                                     						*/
#define  BSP_GPIOE_NULL12							GPIO_Pin_12    	/* NULL.                                     						*/
#define  BSP_GPIOE_CAN2_SW						GPIO_Pin_13    	/* I/O.                                     						*/
#define  BSP_GPIOE_NULL14							GPIO_Pin_14    	/* NULL.                                    						*/
#define  BSP_GPIOE_FCAN2_STB					GPIO_Pin_15    	/* No such pin.                                      		*/

/**************************************************************************************************************/

void bsp_gpio_Init( void );
void bsp_NVCI_Configuration( void );
 void	bsp_sysexit_Init (void);
void bsp_canx_init( CAN_TypeDef* canx , DWORD u32CanBaud );
void bsp_can_filter_mask(BYTE u8FilterGroup, DWORD u32FilterId ,DWORD idmask);
void bsp_usart_baud_init( USART_TypeDef* USARTx, DWORD u32UsartBaud );
void bsp_systick_init( void );
void bsp_SystemInit( void );
//通讯管脚配置
#define ISO14230_KLINE_PORT            GPIOB
#define ISO14230_LLINE_PORT            GPIOB
#define ISO14230_KLINE_TXPIN           GPIO_Pin_10
#define ISO14230_KLINE_RXPIN           GPIO_Pin_11
#define ISO14230_LLINE_PIN             GPIO_Pin_1
#define ISO14230_LLINE_SET             GPIO_ResetBits( ISO14230_LLINE_PORT, ISO14230_LLINE_PIN )
#define ISO14230_LLINE_RESET           GPIO_SetBits( ISO14230_LLINE_PORT, ISO14230_LLINE_PIN )
#define ISO14230_KLINE_RESET           GPIO_ResetBits( ISO14230_KLINE_PORT, ISO14230_KLINE_TXPIN )
#define ISO14230_KLINE_SET             GPIO_SetBits( ISO14230_KLINE_PORT, ISO14230_KLINE_TXPIN )
void bsp_fun_obd_Kline_init( void );
#endif




