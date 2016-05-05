
#ifndef TIMER_H
#define TIMER_H

typedef struct
{
   uint08 msTimeCnt;
   uint16 msTick;
   union
   {
      uint08 All[2];
      struct
      {
         uint08  _1ms          :1;  
         uint08  _10ms         :1;  
         uint08  _20ms         :1;  
         uint08  _50ms         :1;  
         uint08  _100ms        :1;  
         uint08  _500ms        :1;  
         uint08  _1000ms       :1;  
         uint08  _5000ms       :1;  
         uint08  Blink         :1;  
         uint08  FastBlink     :1;  
         uint08  PwmFlag       :1;  
         uint08  Times         :5;  
      }Solo;
   }Flags;
}TimerType;

extern TimerType Timer1;
void Timer0_Init(void);
void Timer1_Init(void);
void TimerDeal(TimerType *pdata);

#endif
