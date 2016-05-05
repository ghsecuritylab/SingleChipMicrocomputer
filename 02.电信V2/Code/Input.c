
#include "includes.h"

uint16  InputGet(void)
{
   uint16 KeyInput = 0;
   uint08 tmp = 0;
   //拨码
   for (tmp=0; tmp<8; tmp++)
   {
      if ( (PINB & BIT(tmp)) == 0)
      {
         SetBit(KeyInput, tmp);
      }
   }
   //干接点
   for (tmp=8; tmp<16; tmp++)
   {
      if ( (PINC & BIT(tmp-8)) == 0)
      {
         SetBit(KeyInput, tmp);
      }
   }
   return KeyInput;
}
//{
//   uint16 KeyInput = 0;
//   if ( (PINB & BIT(0)) == 0) //key8
//   {
//      SetBit(KeyInput, 7);
//   }
//   if ( (PINB & BIT(1)) == 0)//key7
//   {
//      SetBit(KeyInput, 6);
//   }
//   if ( (PINB & BIT(2)) == 0)//key6
//   {
//      SetBit(KeyInput, 5);
//   }
//   if ( (PINB & BIT(3)) == 0)//key5
//   {
//      SetBit(KeyInput, 4);
//   }
//   if ( (PINB & BIT(5)) == 0)//key4
//   {
//      SetBit(KeyInput, 3);
//   }
//   if ( (PINB & BIT(7)) == 0)//key3
//   {
//      SetBit(KeyInput, 2);
//   }
//   if ( (PINB & BIT(6)) == 0)//key2
//   {
//      SetBit(KeyInput, 1);
//   }
//   if ( (PINB & BIT(4)) == 0)//key1
//   {
//      SetBit(KeyInput, 0);
//   }
//
//
//   if ( (PINC & BIT(4)) == 0)//DI1
//   {
//      SetBit(KeyInput, 8);
//   }
//   if ( (PINC & BIT(5)) == 0)//DI2
//   {
//      SetBit(KeyInput, 9);
//   }
//   if ( (PINC & BIT(6)) == 0)//DI3
//   {
//      SetBit(KeyInput, 10);
//   }
//   if ( (PINC & BIT(7)) == 0)//DI4
//   {
//      SetBit(KeyInput, 11);
//   }
//   if ( (PINC & BIT(0)) == 0)//DI5
//   {
//      SetBit(KeyInput, 12);
//   }
//   if ( (PINC & BIT(1)) == 0)//DI6
//   {
//      SetBit(KeyInput, 13);
//   }
//   if ( (PINC & BIT(2)) == 0)//DI7
//   {
//      SetBit(KeyInput, 14);
//   }
//   if ( (PINC & BIT(3)) == 0)//DI8
//   {
//      SetBit(KeyInput, 15);
//   }
//   return KeyInput;
//}


#define _MAX_DI_ 16
void InputScan(uint16 Key, DianXin_All_Def *pData)
{
   uchar tmp;
   static uint16 KeyLastRec;
   static uint16 KeyOut;
   static uint08 KeyInputCnt[_MAX_DI_];
   for (tmp = 0; tmp < 16; tmp++)
   {
      if ((GetBit(Key, tmp) ^ GetBit(KeyLastRec, tmp)) != 0)
      {
         ClrBit(KeyOut, tmp);
         KeyInputCnt[tmp] = 0;
      }
      else
      {
         KeyInputCnt[tmp]++;
         if (KeyInputCnt[tmp] >= 20)
         {
            if (GetBit(Key, tmp) != 0)
            {
               SetBit(KeyOut, tmp);
            }
            else
            {
               ClrBit(KeyOut, tmp);
            }
         }
      }
   }
   KeyLastRec = Key;
   pData->DI.All = KeyOut;
}



void InputDeal(DianXin_All_Def *pData)
{
   static DianXin_All_Def KeyTreated;
   if (pData->DI.Solo.DI1  && !KeyTreated.DI.Solo.DI1)
   {
      KeyTreated.DI.Solo.DI1 = 1;
      //此处为按键的功能处理代码
   }
   else if (!pData->DI.Solo.DI1)
   {
      KeyTreated.DI.Solo.DI1 = 0;
   }
}

void InputAddr(DianXin_All_Def *pData)
{
   pData->Address = 0;
   if (pData->DI.Solo.button1)
   {
      pData->Address |= 1;
   }
   if (pData->DI.Solo.button2)
   {
      pData->Address |= 2;
   }
   if (pData->DI.Solo.button3)
   {
      pData->Address |= 4;
   }
   if (pData->DI.Solo.button4)
   {
      pData->Address |= 8;
   }
   if (pData->DI.Solo.button5)
   {
      pData->Address |= 16;
   }
   if (pData->DI.Solo.button6)
   {
      pData->Address |= 32;
   }
   if (pData->DI.Solo.button7)
   {
      pData->Address |= 64;
   }
   if (pData->DI.Solo.button8)
   {
      pData->Address |= 128;
   }
}
