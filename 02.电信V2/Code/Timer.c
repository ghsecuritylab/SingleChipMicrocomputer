
#include "includes.h"

#define Timer10ms    5
#define Timer30ms    15
#define Timer50ms    25
#define Timer100ms   50
#define Timer500ms   250
#define Timer1000ms  500
#define Timer5000ms  2500


TimerType Timer1;


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
}

void TimerDeal(TimerType *Times)
{
   if (Times->msTimeCnt == 0)
   {
      return;
   }
   Times->msTimeCnt = 0;
   Times->msTick++;
   Times->Flags.Solo._1ms = 1;
   if (Times->msTick % Timer10ms == 0)
   {
      Times->Flags.Solo._10ms ^= 1;
   }
   if (Times->msTick % Timer30ms == 0)
   {
      Times->Flags.Solo._30ms ^= 1;
   }
   if (Times->msTick % Timer50ms == 0)
   {
   }
   if (Times->msTick % Timer100ms == 0)
   {
      Times->Flags.Solo._100ms ^= 1;
      Times->Flags.Solo.FastBlink ^= 1;
   }
   if (Times->msTick % Timer500ms == 0)
   {
      Times->Flags.Solo.Blink ^= 1;
   }
   if (Times->msTick % Timer1000ms == 0)
   {
      Times->Flags.Solo._1000ms ^= 1;
   }
   if (Times->msTick % Timer5000ms == 0)
   {
      Times->Flags.Solo._5000ms ^= 1;
   }
   if (Times->msTick > 50000)
   {
      Times->msTick = 0;
   }
}

