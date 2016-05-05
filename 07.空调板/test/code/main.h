

#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define SYS_OSC (8000000U)

//extern uint msStartUpCnt;
extern uint16 msTick;

extern uint16 nTimeSpeed;
extern uint16 speedPerMin;


//#define __10_000ms 1000
//#define __20_000ms 2000
//#define __30_000ms 3000
//#define __40_000ms 4000
//#define _FORCEING_TIME 6000*5



//HT1621引脚
//#define CS1  	    PORTA |=  BIT(5)
//#define CS0  	    PORTA &= ~BIT(5)
//#define WRITE1      PORTA |=  BIT(4)
//#define WRITE0      PORTA &= ~BIT(4)
//#define DATA1       PORTA |=  BIT(3)
//#define DATA0       PORTA &= ~BIT(3)
//背光引脚
//#define BACKLED_ON     	PORTA |=  BIT(6)
//#define BACKLED_OFF     PORTA &= ~BIT(6)
//继电器引脚
#define RelayFanLvlHigh     PORTE_PORTE7
#define RelayFanLvlMed     PORTE_PORTE6
#define RelayFanLvlLow     PORTE_PORTE5
#define RelayValveOn     PORTE_PORTE4
#define RelayValveOff     PORTE_PORTE3
//#define FanLvlHigh_ON    	PORTB |=  BIT(0)    //风机
//#define FanLvlHigh_OFF    	PORTB &= ~BIT(0)
//#define FanLvlMed_ON    	PORTB |=  BIT(1)    //风机指示灯
//#define FanLvlMed_OFF    	PORTB &= ~BIT(1)
//#define FanLvlLow_ON    	PORTB |=  BIT(2)    //照明
//#define FanLvlLow_OFF    	PORTB &= ~BIT(2)
//#define Out_ON_2_ON      PORTB |=  BIT(3)    //外门锁
//#define Out_ON_2_OFF     PORTB &= ~BIT(3)
//#define Out_ON_1_ON    	PORTB |=  BIT(4)    //内门锁
//#define Out_ON_1_OFF    	PORTB &= ~BIT(4)



#endif























