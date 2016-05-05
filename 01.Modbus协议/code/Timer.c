
#include "includes.h"


TimerType Timer1;


void Timer1_Init(void)
{
   TCNT1H = (65535 - 8000) / 256; //¶¨Ê±1ms
   TCNT1L = (65535 - 8000) % 256;
   TIMSK_TOIE1 = 1;
   TCCR1A = 0;
   TCCR1B_CS10 = 1;
   SREG |= BIT(7);
}

#pragma vector = TIMER1_OVF_vect
__interrupt void T1_OVF_ISR(void)
{
   TCNT1H = (65535 - 8000) / 256;
   TCNT1L  = (65535 - 8000) % 256;
   Timer1.msTimeCnt++;
}

void TimerDeal(TimerType *pdata)
{
   if (pdata->msTimeCnt == 0)
   {
      return;
   }
   pdata->msTimeCnt = 0;
   pdata->msTick++;
   pdata->Flags.Solo._1ms = 1;
   if (pdata->msTick % 5 == 0)
   {
      pdata->Flags.Solo._5ms = 1;
   }
   if (pdata->msTick % 10 == 0)
   {
      pdata->Flags.Solo._10ms = 1;
   }
   if (pdata->msTick % 20 == 0)
   {
      pdata->Flags.Solo._20ms = 1;
   }
   if (pdata->msTick % 50 == 0)
   {
      pdata->Flags.Solo._50ms = 1;
   }
   if (pdata->msTick % 100 == 0)
   {
      pdata->Flags.Solo._100ms = 1;
      pdata->Flags.Solo.FastBlink ^= 1;
   }
   if (pdata->msTick % 500 == 0)
   {
      pdata->Flags.Solo._100ms = 1;
      pdata->Flags.Solo.Blink ^= 1;
   }
   if (pdata->msTick % 1000 == 0)
   {
      pdata->Flags.Solo._1000ms = 1;
   }
   if (pdata->msTick % 5000 == 0)
   {
      pdata->Flags.Solo._5000ms = 1;
   }
   if (pdata->msTick >= 50000)
   {
      pdata->msTick = 0;
   }
}

