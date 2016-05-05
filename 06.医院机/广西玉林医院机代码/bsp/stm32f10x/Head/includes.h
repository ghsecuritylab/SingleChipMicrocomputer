#ifndef __Include_H
#define __Include_H



#include "stm32f10x_conf.h"

#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <intrinsics.h>
//#include "constdef.h"
//#include "misc/stdbool.h"
#include "misc_me.h"
//#include "misc/miscfuc.h"

#include "stm32f10x.h"
//#include "misc/UartTrace.h"

#include "typedef.h"

//#include "../Cprotocal/CApp.h"
//#include "../Cprotocal/CRC.h"
//#include "../Cprotocal/CLModbus.h"
//#include "../Cprotocal/DeviceDeal.h"

//#include "SystemConfig.h"
//#include "HardwareConfig.h"
//#include "./misc/Misc.h"
//#include "ExHal.h"
#include "Relay.h"
#include "74hc165.h"
#include "adc.h"
//#include "StdMd.h"
//#include "RTC.h"
#include "PWM.h"
#include "HwPanel.h"
#include "LEDs.h"
//#include "PolMd.h"




////my externs
////extern SystemStatus CurrentSS ;
////extern BYTE *UartReceivedBuffer ;
//extern UartType *UartAppData1;
//extern UartType *UartAppData2;
//extern UartType *UartAppData3;
//extern UartType *UartAppData4;
//extern UartType *UartAppData5;
//extern New_Info_Panel_Def *InfoPanel;
//
//
//extern Cp_Rev_Def *cpcb1;
//extern Cp_Tcp_Dep Com2Tcp;
//extern CpErrEnum Com2Ret;
//
//
//
//
////old externs
//extern void ChipHalInit(void);
//extern void ChipOutHalInit(void);
//extern void EXTI_DeInit(void);
//extern void  OSInit (void);
//extern void system_init(void);
//extern int __std_printf(int dbgLevel, const char * format,...);
//extern void SystemIdleTask (void);
//extern INT8U  OSTaskCreateExt (void   (*task)(void *p_arg),
//                        void    *p_arg,
//                        OS_STK  *ptos,
//                        INT8U    prio,
//                        INT16U   id,
//                        OS_STK  *pbos,
//                        INT32U   stk_size,
//                        void    *pext,
//                        INT16U   opt) ;
//
//extern void InitBaseUARTComm(void); 
//extern void Init_targetIO(void);
#define PRINTF(x)   __std_printf  x
#define PRINTS(x)   __std_printf  x
////#define TRACE       __std_printf


#endif

