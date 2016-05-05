#include <ioavr.h>
#include <intrinsics.h>	//包含nop指令头文
#include <stdio.h>
#include <stdbool.h>
#include <iom128a.h>
#include "includes/typedef.h"
#include "includes/userMacros.h"
#include "main.h"
#include "AvrUART.h"
#include "CLModbus.h"
#include "CRC.h"
#include "FFU.h"
#include "StdMd.h"
#include "DIDrv.h"
#include "AvrEEp.h"
#include "AvrAdc.h"
#include "FC.h"
#include "PWM.h"
#include "PID.h"

#define Global_EI() {SREG |= BIT(7);}
#define Global_DI() {SREG &= ~BIT(7);}






















