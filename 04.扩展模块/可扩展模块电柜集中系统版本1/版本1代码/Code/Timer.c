
#include "includes.h"

#define Timer10ms    5
#define Timer20ms    10
#define Timer50ms    25
#define Timer100ms   50
#define Timer500ms   250
#define Timer1000ms  500
#define Timer5000ms  2500


TimerType Timer1;
//Time=PRE*(MAX-TCNT0+1)/F_cpu=1·ÖÆµ*(255-131+1)/8MHz=1ms
void Timer0_Init(void)
{
   TCNT0 = 0x83;
   TIMSK_TOIE0 = 1;
   TCCR0  = 0x03;
}

#pragma vector = TIMER0_OVF_vect
__interrupt void T0_OVF_ISR(void)
{
   __enable_interrupt();
   TCNT0 = 0x83;
}


void Timer1_Init(void)
{
   TCNT1H = (65535 - 8000) / 256; //¶¨Ê±1ms
   TCNT1L = (65535 - 8000) % 256;
   TIMSK_TOIE1 = 1;
   TCCR1A = 0;
   TCCR1B_CS10 = 1;
}

#pragma vector = TIMER1_OVF_vect
__interrupt void T1_OVF_ISR(void)
{
   TCNT1H = (65535 - 8000) / 256;
   TCNT1L  = (65535 - 8000) % 256;
   Timer1.msTimeCnt++;
   Timer1.Timer0Cnt++;
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
   if (pdata->msTick % Timer10ms == 0)
   {
      pdata->Flags.Solo._10ms ^= 1;
   }
   if (pdata->msTick % Timer20ms == 0)
   {
      pdata->Flags.Solo._20ms ^= 1;
   }
   if (pdata->msTick % Timer50ms == 0)
   {
      pdata->Flags.Solo.FastBlink ^= 1;
   }
   if (pdata->msTick % Timer100ms == 0)
   {
      pdata->Flags.Solo._100ms ^= 1;
   }
   if (pdata->msTick % Timer500ms == 0)
   {
      pdata->Flags.Solo.Blink ^= 1;
      MODE1.DO.Solo.LED1 ^= 1;
   }
   if (pdata->msTick % Timer1000ms == 0)
   {
      pdata->Flags.Solo._1000ms ^= 1;
   }
   if (pdata->msTick % Timer5000ms == 0)
   {
      pdata->Flags.Solo._5000ms ^= 1;
   }
   if (pdata->msTick > 50000)
   {
      pdata->msTick = 0;
   }
}

