#ifndef __Includes_H
#define __Includes_H

#define _0XF1_MAX_DATA_LEN 4
#define _0XF2_MAX_DATA_LEN 4
#define _0XF3_MAX_DATA_LEN 7
#define _0XF4_MAX_DATA_LEN 8
#define _0XF5_MAX_DATA_LEN 1
#define _0XF6_MAX_DATA_LEN 52
#define _0XF7_MAX_DATA_LEN 58
#define _0XALL_MAX_DATA_LEN 70

#define _0X01_MAX_DATA_LEN 52

#include "stm32f10x_conf.h"

#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include  <intrinsics.h>
#include  <rtthread.h>
#include  <math.h>

#include "constdef.h"
#include "stdbool.h"
#include "misc_me.h"
#include "miscfuc.h"

#include "stm32f10x.h"
#include "UartTrace.h"

#include "typedef.h"

#include "CApp.h"
#include "CRC.h"
#include "CLModbus.h"
#include "DeviceDeal.h"

#include "SystemConfig.h"
#include "HardwareConfig.h"
#include "ExHal.h"
#include "Relay.h"
#include "74hc165.h"
#include "adc.h"
#include "StdMd.h"
#include "RTC.h"
#include "PWM.h"
#include "HwPanel.h"
#include "LEDs.h"
#include "PolMd.h"
#include "pid.h"
#include "Ctrl.h"


#include "flashsave.h"
#include "iap_flash.h"
//#include "eeprom.h"
#include  "parSave.h"

//my externs
extern UartType UartAppData1;
extern UartType UartAppData2;
extern UartType UartAppData3;
extern UartType UartAppData4;
extern UartType UartAppData5;



#endif

