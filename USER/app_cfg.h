#ifndef _APP_CFG_H_
#define _APP_CFG_H_

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_it.h"
#include "stdio.h"
#include "ucos_ii.h"

typedef unsigned char                  BYTE;
typedef unsigned short                 WORD;
typedef unsigned int                   DWORD;

typedef enum  {MSG_PCDOWN = 0,MSG_PCUP} TYPEDEF_MSG;
typedef enum  {MODE_COLLECTION = 0xAA,MODE_SIMULATION = 0xBB ,MODE_KLINE = 0X77} TYPEDEF_WORKMODE;
typedef struct TYPE_BUSFRAMS
{
	 BYTE onefram[13];
}TYPE_BUSFRAMS;

#endif

