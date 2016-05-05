

#ifndef MAIN_H
#define MAIN_H


#define SYS_OSC (8000000U)






extern uint08 Cnt;
extern uint16 msTick;
extern uint08 mSTimeCnt;


void T0_Init(void);
void T1_Init(void);
void TimeDeal(AHU_DEF *Ahu);
#endif























