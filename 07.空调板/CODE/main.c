#include "includes.h"

AHU_DEF Ahu1;
uint08 mSTimeCnt = 0;
uint16 msTick = 0;


void  Pin_Init(void)
{

   //10个按键引脚配置
   ClrBit(DDRD, 6);      SetBit(PORTD, 6);
   ClrBit(DDRF, 3);      SetBit(PORTF, 3);
   ClrBit(DDRF, 0);      SetBit(PORTF, 0);
   ClrBit(DDRF, 1);      SetBit(PORTF, 1);
   ClrBit(DDRE, 3);      SetBit(PORTE, 3);
   ClrBit(DDRB, 5);      SetBit(PORTB, 5);
   ClrBit(DDRB, 6);      SetBit(PORTB, 6);
   ClrBit(DDRD, 4);      SetBit(PORTD, 4);
   ClrBit(DDRG, 4);      SetBit(PORTG, 4);

   //5个平面灯引脚配置
   SetBit(DDRE, 7);      ClrBit(PORTE, 7);//yunxing
   SetBit(DDRB, 0);      ClrBit(PORTB, 0);//zhiji
   SetBit(DDRB, 2);      ClrBit(PORTB, 2);//guzhang
   SetBit(DDRB, 3);      ClrBit(PORTB, 3);//高效
   SetBit(DDRB, 4);      ClrBit(PORTB, 4);

   //4个LED灯引脚配置
   SetBit(DDRF, 2);      SetBit(PORTF, 2);
   SetBit(DDRE, 4);      SetBit(PORTE, 4);
   SetBit(DDRB, 7);      SetBit(PORTB, 7);
   SetBit(DDRD, 5);      SetBit(PORTD, 5);

   //3个温度数码管公共端引脚配置
   SetBit(DDRA, 0);      SetBit(PORTA, 0);
   SetBit(DDRA, 1);      SetBit(PORTA, 1);
   SetBit(DDRA, 2);      SetBit(PORTA, 2);

   //温度数码管8段引脚配置
   SetBit(DDRA, 4);      ClrBit(PORTA, 4);
   SetBit(DDRA, 3);      ClrBit(PORTA, 3);
   SetBit(DDRC, 7);      ClrBit(PORTC, 7);
   SetBit(DDRG, 2);      ClrBit(PORTG, 2);
   SetBit(DDRA, 7);      ClrBit(PORTA, 7);
   SetBit(DDRA, 5);      ClrBit(PORTA, 5);
   SetBit(DDRA, 6);      ClrBit(PORTA, 6);
   SetBit(DDRE, 5);      ClrBit(PORTE, 5);

   //3个湿度数码管公共端引脚配置
   SetBit(DDRG, 1);      SetBit(PORTG, 1);
   SetBit(DDRG, 0);      SetBit(PORTG, 0);
   SetBit(DDRD, 7);      SetBit(PORTD, 7);

   //湿度数码管8段引脚配置
   SetBit(DDRC, 2);      ClrBit(PORTC, 2);
   SetBit(DDRC, 3);      ClrBit(PORTC, 3);
   SetBit(DDRC, 4);      ClrBit(PORTC, 4);
   SetBit(DDRC, 5);      ClrBit(PORTC, 5);
   SetBit(DDRC, 6);      ClrBit(PORTC, 6);
   SetBit(DDRC, 1);      ClrBit(PORTC, 1);
   SetBit(DDRC, 0);      ClrBit(PORTC, 0);
   SetBit(DDRE, 6);      ClrBit(PORTE, 6);

   //RS485引脚配置
   SetBit(DDRD, 1);      ClrBit(PORTD, 1);
   SetBit(DDRE, 2);      ClrBit(PORTE, 2);
}



void T0_Init(void)
{
   TCCR0 = 0x03;
   TIMSK_TOIE0 = 1;
   TCNT0 = 0x83;
   Global_EI();
}

#pragma vector = TIMER0_OVF_vect
__interrupt void T0_OVF_ISR(void)
{
   TCNT0 = 0x83;
   mSTimeCnt++;
}

void T1_Init(void)
{
   TCCR1A = 0;
   TCCR1B_CS10 = 1;
   TIMSK_TOIE1 = 1;
   TCNT1H = (65535 - 8000) / 256;
   TCNT1L  = (65535 - 8000) % 256;
   Global_EI();
}

#pragma vector = TIMER1_OVF_vect
__interrupt void T1_OVF_ISR(void)
{
   TCNT1H = (65535 - 8000) / 256;
   TCNT1L  = (65535 - 8000) % 256;
}

void TimeDeal(AHU_DEF *Ahu)
{
   if (mSTimeCnt < 2)
   {
      return;
   }
   mSTimeCnt = 0;
   msTick++;
   Ahu->Times.Solo._1msFlag = 1;
   if (msTick % 5 == 0)
   {
      Ahu->Times.Solo._5msFlag = 1;
   }
   if (msTick % 10 == 0)
   {
      Ahu->Times.Solo._10msFlag = 1;
   }
   if (msTick % 20 == 0)
   {
      Ahu->Times.Solo._20msFlag = 1;
   }
   if (msTick % 100 == 0)
   {
      Ahu->Times.Solo._100msFlag = 1;
   }
   if (msTick % 1000 == 0)
   {
      Ahu->Times.Solo._1000msFlag = 1;
      Ahu->Times.Solo.Blink ^= 1;
   }
   if (msTick % 5000 == 0)
   {
      Ahu->Times.Solo._5000msFlag = 1;
   }
}

uint08 flag = 0;
/******************主程序********************************/
void main(void)
{
   Pin_Init();
   T0_Init();
   Uart1_Init();
   Uart2_Init();
   Uart1_AppInit();
   Uart2_AppInit();
   MdTcbInit1();
   MdTcbInit2();
   Global_EI();
   while (1)
   {
      TimeDeal(&Ahu1);
      MdPoll01();
      MdPoll02();
      if (Ahu1.Times.Solo._1msFlag)
      {
         UartTimeOut(&UartAppData1);
         UartTimeOut(&UartAppData2);
	 KeyScanDeal(KeyGet());
	 KeyAllStateDeal(&Ahu1);
	 NumberDisplayScan(&Ahu1);
      }
      DisplayNumber(flag);
      if (Ahu1.Times.Solo._5msFlag)
      {
	 LedOutputScan(&Ahu1);
	 RhDisplayScan(&Ahu1);    
	 TmepDisplayScan(&Ahu1);  
      }
      if (Ahu1.Times.Solo._10msFlag)
      {


      }
      if (Ahu1.Times.Solo._1000msFlag)
      {
	 flag++;
      }
//      Ahu1.Humidity.Solo.SEG_B = 1;
//      Ahu1.Temperature.Solo.SEG_C = 1;
      Ahu1.Times.All[0] = 0;
   }
}
