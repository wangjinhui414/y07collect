#ifndef _PC_TASK_H_
#define _PC_TASK_H_
#include  "app_cfg.h"
#include "main.h"
extern BYTE recv_buffer[255];
extern BYTE recv_offset;
extern BYTE send_buffer[300];
extern BYTE send_offset;
extern TYPE_BUSFRAMS g_allbusfram[250];

extern CAN_TypeDef *CANx;

void fun_pc_task_start( void* pArg);
void fun_bus_task_start( void* pArg);
void WriteUpdataFlash(void);
#endif

