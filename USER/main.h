#ifndef _MAIN_H_
#define _MAIN_H_

#include "app_cfg.h"
//任务优先级
#define  APP_TASK_START_PRIO							6u	
#define	 APP_TASK_PC_PRIO								  7u
#define	 APP_TASK_ECU_PRIO								8u#define	 APP_TASK_BUS_PRIO								9u
//任务堆栈大小
#define	 APP_TASK_START_SIZE              125u
#define	 APP_TASK_PC_SIZE                 255u
#define	 APP_TASK_ECU_SIZE                255u
#define	 APP_TASK_BUS_SIZE                255u




extern OS_EVENT *g_pstMsgToEcu;
extern OS_EVENT *g_pstMsgToPc;
extern OS_EVENT *g_pstMsgToBus;
void fun_app_task_start( void* pArg );
void fun_app_task_create(void );

extern void fun_pc_task_start( void* pArg);
extern void fun_ecu_task_start( void* pArg);
extern void fun_bus_task_start( void* pArg);
#endif
