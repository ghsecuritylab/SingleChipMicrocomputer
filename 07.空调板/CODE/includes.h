
#ifndef _INCLUDES_H
#define _INCLUDES_H

#include <ioavr.h>
#include <intrinsics.h>	//包含nop指令头文
#include <stdio.h>
#include <stdbool.h>
#include <iom128a.h>



#include "typedefs.h"
#include "defines.h"
#include "main.h"
#include "AvrUART.h"
#include "CLModbus.h"
#include "CRC.h"
#include "StdMd.h"
#include "AvrEEp.h"
#include "Output.h"
#include "Input.h"
//#include "AvrAdc.h"
//#include "PWM.h"




#define Global_EI() {SREG |= BIT(7);}
#define Global_DI() {SREG &= ~BIT(7);}






#endif















