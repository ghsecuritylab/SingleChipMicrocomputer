
#include "includes.h"



void OutputDeal(Module_All_Def *mode)
{
   if (Timer1.Flags.Solo._10ms == 0)
   {
      return;
   }

   if (mode->DO.Solo.DO1)
   {
      SetBit(PORTB, 0);
   }
   else
   {
      ClrBit(PORTB, 0);
   }
   if (mode->DO.Solo.DO2)
   {
      SetBit(PORTB, 1);
   }
   else
   {
      ClrBit(PORTB, 1);
   }
   if (mode->DO.Solo.DO3)
   {
      SetBit(PORTB, 2);
   }
   else
   {
      ClrBit(PORTB, 2);
   }
   if (mode->DO.Solo.DO4)
   {
      SetBit(PORTB, 4);
   }
   else
   {
      ClrBit(PORTB, 4);
   }
   if (mode->DO.Solo.LED1)
   {
      ClrBit(PORTD, 3);
   }
   else
   {
      SetBit(PORTD, 3);
   }
   if (mode->DO.Solo.LED2)
   {
      ClrBit(PORTD, 6);
   }
   else
   {
      SetBit(PORTD, 6);
   }
}



