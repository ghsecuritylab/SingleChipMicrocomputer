
#ifndef TIMER_H
#define TIMER_H

typedef struct
{
   uint08 msTimeCnt;
   uint08 Timer0Cnt;
   uint16 msTick;
   union
   {
      uint16 All;
      struct
      {
         uint16  _1ms          :1;   //1����
         uint16  _10ms         :1;   //10����
         uint16  _20ms         :1;   //20����
         uint16  _100ms        :1;   //100����
         uint16  _1000ms       :1;   //1000����
         uint16  _5000ms       :1;   //5000����
         uint16  Blink         :1;   //��˸
         uint16  FastBlink     :1;   //����
         uint16  Time          :8;   //��ʱʱ��    
      }Solo;
   }Flags;
}TimerType;

extern TimerType Timer1;
void Timer0_Init(void);
void Timer1_Init(void);
void TimerDeal(TimerType *pdata);

#endif
