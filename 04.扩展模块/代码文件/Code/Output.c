
#include "includes.h"



void OutputDeal(Module_All_Def *mode)
{
   if (mode->DO.Solo.DO3)
   {
      SetBit(PORTD, 3);
   }
   else
   {
      ClrBit(PORTD, 3);
   }
   if (mode->DO.Solo.DO2)
   {
      SetBit(PORTD, 4);
   }
   else
   {
      ClrBit(PORTD, 4);
   }
   if (mode->DO.Solo.DO1)
   {
      SetBit(PORTD, 5);
   }
   else
   {
      ClrBit(PORTD, 5);
   }

//----------------------------------
   if (mode->DO.Solo.LED1)
   {
      ClrBit(PORTC, 6);
   }
   else
   {
      SetBit(PORTC, 6);
   }
   if (mode->DO.Solo.LED2)
   {
      ClrBit(PORTC, 7);
   }
   else
   {
      SetBit(PORTC, 7);
   }
}



