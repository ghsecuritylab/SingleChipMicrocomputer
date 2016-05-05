#include "includes.h"

void PWMInit()
{
   TCCR1A = 0x81;
   TCCR1B = 0x02;
   TCCR2 = 0x62;
}

void SetPWMAO1(uint16 tmp)
{
   OCR1A = tmp / 4;
}

void SetPWMAO2(uint16 tmp)
{
   OCR2 = tmp / 4;
}

uint16 lastAnalogOut01;
uint16 lastAnalogOut02;
void FCAnalogOutSet(FCDataBaseDef *FC)
{
   if (FC->State.Sys.Solo.Started)
   {
      if (FC->Buff.AnalogOut01 != lastAnalogOut01)
      {
         SetPWMAO1(FC->Buff.AnalogOut01);
         lastAnalogOut01 = FC->Buff.AnalogOut01;
      }
      if (FC->Buff.AnalogOut02 != lastAnalogOut02)
      {
         SetPWMAO2(FC->Buff.AnalogOut02);
         lastAnalogOut02 = FC->Buff.AnalogOut02;
      }
   }
   else
   {
      SetPWMAO1(0);
      SetPWMAO2(0);
   }
}
