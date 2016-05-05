#include "includes.h"
uchar mSTimeCnt = 0;
uint16 msTick = 0;
//uint msStartUpCnt = 0;
uchar speedTI = 0;
uint16 nTimeSpeed = 500;
uint16 speedPerMin;

extern BOOL swih;

//extern uint08 speedShakeCnt = 0;
//extern uint16 speedCnt = 0;

void T1_Init(void);
void TimeDeal(FCDataBaseDef *FC);


/******************IO口引脚配置*************************/
void  Pin_Init(void)
{
   {

//    DDRA = 0x78;
//    PORTA = 0x78;
//
//    DDRB = 0x1F;
//    PORTB = ~DDRB;
//
//    DDRC = 0xE0;
//    PORTC = ~DDRC;
//
//    DDRD = 0xA6;
//    PORTD = ~DDRD;
      DDRA = 0x00;
      PORTA = 0x00;

//    DDRB = 0xA0;
//    PORTB = ~DDRB;

      DDRB = 0xB0;
      PORTB = 0x5F;

      DDRC = 0x00;
      PORTC = 0xFF;

      DDRD = 0x0A;
      PORTD = 0x0C;

      DDRE = 0xFE;
      PORTE = 0x03;

      DDRF = 0x40;
      PORTF = 0xB0;

      DDRG = 0x00;
      PORTG = 0xFF;

//    ClrBit(DDRD, 0);      //U_RX
//    SetBit(PORTD, 0);
   }
}



void  T0_Init(void)
{
   TCCR0 = 0x03;
   TIMSK_TOIE0 = 1;   //使能T0溢出中断
   TCNT0 = 0x83;
   Global_EI();
}

#pragma vector = TIMER0_OVF_vect
__interrupt void T0_OVF_ISR(void)
{
   TCNT0 = 0x83;
   mSTimeCnt++;
//        swih ^= 1;
//        PORTB_PORTB4 = swih;
   speedTI++;

}

void  T1_Init(void)
{
   TCCR1A = 0;
   TCCR1B_CS10 = 1; //使用时钟分频选择 000=stop 001=1 010=8 011=64 100=256
                    //TCCR1B_CS11=1; //使用时钟分频选择 具体看P10页
                    //TCCR1B_CS12=1; //使用时钟分频选择
   TIMSK_TOIE1 = 1;   //使能T0溢出中断
   TCNT1H = (65535 - 8000) / 256;
   TCNT1L  = (65535 - 8000) % 256;
   Global_EI();
}

#pragma vector = TIMER1_OVF_vect
__interrupt void T1_OVF_ISR(void)
{
   TCNT1H = (65535 - 8000) / 256;
   TCNT1L  = (65535 - 8000) % 256;
//       PORTA ^= BIT(6);
}

void TimeDeal(FCDataBaseDef *FC)
{
   if (mSTimeCnt < 4)
   {
      return;
   }
// swih ^= 1;
// PORTB_PORTB4 = swih;
   mSTimeCnt = 0;
   FC->Buff.Flag.solo._2msFlag = 1;
   msTick++;
   if (msTick % 2 == 0)
   {
      FC->Buff.Flag.solo.KeySwitch = 1;
      FC->Buff.Flag.solo._4msFlag = 1;
   }
   if (msTick % 20 == 0)
   {
      FC->Buff.Flag.solo._20msFlag = 1;
   }
   if (msTick % 5 == 0)
   {
      FC->Buff.Flag.solo._10msFlag = 1;
   }
   if (msTick % 500 == 0)
   {
      FC->Buff.Flag.solo._1000msFlag = 1;
   }
   if (msTick % 5000 == 0)
   {
      FC->Buff.Flag.solo._10000msFlag = 1;
   }
   if (msTick % (5 * nTimeSpeed) == 0)
   {
      FC->Buff.Flag.solo._nmsFlag = 1;
   }

}

extern ulong currentSpeedsET;
BOOL cnm;

/******************主程序********************************/
void main(void)
{
   Pin_Init();
   T0_Init();
   Uart_Init();
   Uart2_Init();
   Uart_AppInit();
   Uart2_AppInit();
   MdTcbInit();
   MdTcbInit2();
   AdcInit();
   PWMInit();
   FCInitOne();
   while (1)
   {
      TimeDeal(&FC1);
      MdPoll();
      MdMasterPoll();
      FCKeyScan(&FC1);
      ResetDeal(&FC1);
      FCURun(&FC1);
      FCRelayOutput(&FC1);
      if (FC1.Buff.Flag.solo._2msFlag)
      {
//        FC2IOScan(&FC1);
          swih ^= 1;
          PORTB_PORTB4 = swih;
         TestSpeed();
         UartTimeOut(&UartAppData1);
         UartTimeOut(&UartAppData2);
      }
      if (FC1.Buff.Flag.solo._4msFlag)
      {
         InputDeal();
      }
      if (FC1.Buff.Flag.solo._10msFlag)
      {
         FCWorkTime(&FC1);
      }
      if (FC1.Buff.Flag.solo._20msFlag)
      {
         AdcGetAll(&FC1);
         FCAnalogOutSet(&FC1);
         EePromDeal(&FC1.Run, sizeof(FC_RUNING_Def) - CRC_LEN, &EeSave1);
      }
      if (FC1.Buff.Flag.solo._10000msFlag)
      {
         uint16 tmpCrc = FC1.Run.RunCrc;
         uint16 tmpCrcNew = GetCRC16((uint08 *)&FC1.Run, sizeof(FC_RUNING_Def) - CRC_LEN);
         if (tmpCrc != tmpCrcNew)
         {
            EeWriteTrg(&EeSave1);
         }
      }
      if (FC1.Buff.Flag.solo._nmsFlag)
      {
          speedPerMin = speedCnt * 60 / 4 / (nTimeSpeed / 100);
          speedCnt = 0;
      }

      FC1.Buff.Flag.All = 0;
   }
}
