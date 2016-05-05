
#include "includes.h"

uint08  InputGet(void)
{
   uint08 KeyInput = 0;
   if ( (PINC & BIT(0)) == 0)
   {
      SetBit(KeyInput, 0); 
   }
   if ( (PINC & BIT(1)) == 0)
   {
      SetBit(KeyInput, 1); 
   }
   if ( (PINC & BIT(6)) == 0)
   {
      SetBit(KeyInput, 2); 
   }
   if ( (PINC & BIT(7)) == 0)
   {
      SetBit(KeyInput, 3); 
   }
   return KeyInput;
}


#define _MAX_DI_ 4
void InputScan(uint08 KeyInput, Module_All_Def *mode)
{
   if (Timer1.Flags.Solo._1ms == 0)
   {
      return;
   }

   uint08 tmp;
   static uint08 KeyLastRec;
   static uint08 KeyResult;
   static uint08 KeyInputCnt[_MAX_DI_];
   for (tmp = 0; tmp < _MAX_DI_; tmp++)
   {
      if ((GetBit(KeyInput, tmp) ^ GetBit(KeyLastRec, tmp)) != 0)
      {
         ClrBit(KeyResult, tmp);
         KeyInputCnt[tmp] = 0;
      }
      else
      {
         KeyInputCnt[tmp]++;
         if (KeyInputCnt[tmp] >= 20)
         {
            if (GetBit(KeyInput, tmp) != 0)
            {
               SetBit(KeyResult, tmp);
            }
            else
            {
               ClrBit(KeyResult, tmp);
            }
         }
      }
   }
   KeyLastRec = KeyInput;
   mode->DI.All = KeyResult;
}



void InputDeal(Module_All_Def *mode)
{
   static Module_DI_Def KeyTreated;
   if (mode->DI.Solo.DI1  && !KeyTreated.Solo.DI1)
   {
      KeyTreated.Solo.DI1 = 1;
      //此处为按键的功能处理代码
   }
   else if (!mode->DI.Solo.DI1)
   {
      KeyTreated.Solo.DI1 = 0;
   }

}
