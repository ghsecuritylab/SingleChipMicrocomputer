


#include "includes.h"

CTRL_DEF  CTR1;
uchar mSTimeCnt = 0;
uint msTick = 0;
uint startupTimer = 0;
uchar KeyStartFlag = 0;


//********************************//引脚配置初始化
void  Pin_init(void)
{
   //个按键引脚配置
   ClrBit(DDRD, 4);      SetBit(PORTD, 4);
   ClrBit(DDRD, 5);      SetBit(PORTD, 5);
   ClrBit(DDRD, 6);      SetBit(PORTD, 6);
   ClrBit(DDRD, 7);      SetBit(PORTD, 7);
   //20个LED及蜂鸣器
   DDRA = 0xff;           PORTA = 0x00;
   DDRC = 0xff;           PORTC = 0x00;
   SetBit(DDRB, 0);      ClrBit(PORTB, 0);
   SetBit(DDRB, 1);      ClrBit(PORTB, 1);
   SetBit(DDRB, 2);      ClrBit(PORTB, 2);
   SetBit(DDRB, 3);      ClrBit(PORTB, 3);
   SetBit(DDRB, 4);      ClrBit(PORTB, 4);
   //RS485引脚配置
   SetBit(DDRD, 2);      ClrBit(PORTD, 2);
}

//********************************//定时器1
void  T1_Init(void)
{
   SREG |= BIT(7);
   TCNT1H = (65535 - 8000) / 256;
   TCNT1L = (65535 - 8000) % 256;
   TIMSK_TOIE1 = 1;
   TCCR1A = 0;
   TCCR1B_CS10 = 1;
}
//********************************//中断入口
#pragma vector = TIMER1_OVF_vect
__interrupt void T1_OVF_ISR(void)
{
   TCNT1H = (65535 - 8000) / 256;
   TCNT1L  = (65535 - 8000) % 256;
   mSTimeCnt = 1;
}
//********************************//定时时间处理
void TimeDeal(CTRL_DEF *Ctr)
{
   if (mSTimeCnt == 0)
   {
      return;
   }
   mSTimeCnt = 0;
   msTick++;
   KeyStartFlag++; 
   Ctr->Runflag.Solo._1ms = 1;
   if (msTick % 10 == 9)
   {
      Ctr->Runflag.Solo._10ms = 1;
   }
   if (msTick % 100 == 99)
   {
      Ctr->Runflag.Solo._100ms = 1;
   }
   if (msTick % 1000 == 999)
   {
      Ctr->Runflag.Solo._1000ms = 1;
   }
   if (msTick % 10000 == 9999)
   {
      Ctr->Runflag.Solo._10000ms = 1;
   }
   if (msTick % 500 == 499)
   {
      Ctr->Runflag.Solo.FastBlink ^= 1;
   }
   if (startupTimer <= 60000)
   {
      startupTimer++;
//      CTR1.Status.LED_16bit = ~CTR1.Status.LED_16bit;

   }

   if (Ctr->Runflag.Solo._1000ms)
   {
      uint16 tmpCrc = CTR1.Status.Crc;
      uint16 tmpCrcNew = GetCRC16((uint08 *)&CTR1.Status, 4);
      if (tmpCrc != tmpCrcNew)
      {
         EeWriteTrg(&EeSave1);//触发写
      }
   }
   if (Ctr->Runflag.Solo._10ms)
   {
      if (EeSave1.Solo.Timer > 0)
      {
         EeSave1.Solo.Timer--;
      }
      EePromDeal(&CTR1.Status, 4, &EeSave1);
   }
}
//********************************//蜂鸣器处理
void BuzzerPoll()
{

}
//********************************//主函数
void main(void)
{
   Pin_init();
   T1_Init();
   Uart_Init();
   Uart_AppInit();
   MdTcbInit();

   {
      EeSave1.Solo.BadSave = 0;
      EeReadTrg(&EeSave1);
      EePromDeal(&CTR1.Status, 4, &EeSave1);
      if (EeSave1.Solo.BadSave)
      {
         EeSave1.Solo.BadSave = 0;
         CTR1.Status.Ctrl.Solo.LocalPower = 0;
         CTR1.Status.Ctrl.Solo.LocalStandby = 0;
         CTR1.Status.Ctrl.Solo.RemotePower = 0;
         CTR1.Status.Ctrl.Solo.RemoteStandby = 0;
         CTR1.Status.RS485addr = 0x00f7;
      }
      if (EeSave1.Solo.Step == 0)
      {
         EeWriteTrg(&EeSave1);
      }
   }
   CTR1.Status.LED_16bit = 0;
   while (1)
   {
      TimeDeal(&CTR1);
      KeyScanDeal(KeyGet());
      KeyDeal(&CTR1);
      OutputCtrlDeal(&CTR1);
      StatusDeal(&CTR1);
      UartTimeOut(&UartAppData1);
      MdPoll();
      CTR1.Runflag.All = 0;
   }
}

