


#ifndef FLSKEYTEXSTCTRL_H
#define FLSKEYTEXSTCTRL_H


#include "includes.h"

#define _MAX_DI_ 12


#define BITX(x) (1<<(x)) 
#define SetBit(x,y) (x|=BITX(y)) 
#define ClrBit(x,y) (x&=~BITX(y)) 
#define GetBit(x,y) (x&BITX(y)) 



extern uchar KeyOldDeal;

void KeyDeal(FLS_DEF *Fls);
void  KeyScanDeal(uint Key);
uint  KeyGet(void);
void RedLineDeal(FLS_DEF *Fls);
void FlsCtrlOutput(FLS_DEF *Fls);


#endif
