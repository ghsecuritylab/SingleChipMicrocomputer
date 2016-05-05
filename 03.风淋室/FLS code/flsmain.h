



#ifndef FLSMAIN_H
#define FLSMAIN_H
#include <ioavr.h>
#include <intrinsics.h>	//包含nop指令头文
#include <stdio.h>
#include <stdbool.h>
#include <iom16a.h>

typedef unsigned char uchar,uint08;
typedef unsigned int  uint,uint16;


#define SYS_OSC (8000000U)

#define __25ms__ 25
#define __5ms__ 5
#define __10_000ms 1000
#define __20_000ms 2000
#define __30_000ms 3000
#define __40_000ms 4000
#define _FORCEING_TIME 6000*5


#define BIT(x) (1<<x)



//WTV040引脚
#define  WTVDATA1   PORTD |= BIT(6)
#define  WTVDATA0   PORTD &= ~BIT(6)
#define  WTVRST1    PORTD |= BIT(7)
#define  WTVRST0    PORTD &= ~BIT(7)
//HT1621引脚
#define CS1  	    PORTC |=  BIT(7)
#define CS0  	    PORTC &= ~BIT(7)
#define WRITE1      PORTC |=  BIT(6)
#define WRITE0      PORTC &= ~BIT(6)
#define DATA1       PORTC |=  BIT(5)
#define DATA0       PORTC &= ~BIT(5)
//背光引脚
#define BACKLED_ON     	PORTB |=  BIT(5)
#define BACKLED_OFF     PORTB &= ~BIT(5)
//继电器引脚
#define FAN_ON    	PORTB |=  BIT(4)    //风机
#define FAN_OFF    	PORTB &= ~BIT(4)
#define WORKLED_ON    	PORTB |=  BIT(3)    //风机指示灯
#define WORKLED_OFF    	PORTB &= ~BIT(3)
#define LIGHT_ON    	PORTB |=  BIT(2)    //照明
#define LIGHT_OFF    	PORTB &= ~BIT(2)
#define OUTDOOR_ON      PORTB |=  BIT(1)    //外门锁
#define OUTDOOR_OFF     PORTB &= ~BIT(1)
#define INDOOR_ON    	PORTB |=  BIT(0)    //内门锁
#define INDOOR_OFF    	PORTB &= ~BIT(0)
//RS485引脚
#define RS485_ON    	PORTD |=  BIT(2)
#define RS485_OFF    	PORTD &= ~BIT(2)
//74LS165引脚   	   
#define _165EN_1    	PORTD |=  BIT(3)
#define _165EN_0    	PORTD &= ~BIT(3)
#define _165SCLK_1   	PORTD &= ~BIT(4)
#define _165SCLK_0   	PORTD |=  BIT(4)
//#define _165DATA_1    	PORTD &= ~BIT(5)
//#define _165DATA_0    	PORTD &= ~BIT(5)




typedef union
{
   uchar All;
   struct {
      uchar _1ms:1;
      uchar _10ms:1;
      uchar _1000ms:1;
      uchar _10000ms:1;
      uchar Blink:1;
      uchar FastBlink:1;
   } Solo;
}RunFlag_Def;




extern RunFlag_Def RunFlag;

extern uchar mSTimeCnt;
extern uchar KeyStartFlag;
extern uint msTick;
extern uchar TestMe;
extern uchar NUMshow;

void eeprom_read(unsigned int addr, unsigned char number, unsigned char *p_buff);
void eeprom_write(unsigned int addr, unsigned char number, unsigned char *p_buff);

#endif



//
//uchar EEPROM_read(uint uiAddress)
//{
//   while (EECR &  BIT(1));
//   EEAR = uiAddress;
//   EECR |= BIT(0);
//   return EEDR;
//}
//
//void EEPROM_write(uint uiAddress, uchar ucData)
//{
//   while (EECR &  BIT(1));
//   EEAR = uiAddress;
//   EEDR = ucData;
//   EECR |= BIT(2);
//   EECR |= BIT(1);
//}

