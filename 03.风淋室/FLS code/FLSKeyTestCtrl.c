
#include "includes.h"


uint  KeyGet(void)
{
   uint KeyOut = 0;
   //五个按键
   if (!(PINC & BIT(4)))
   {
      SetBit(KeyOut, 0);
   }
   if (!(PINC & BIT(3)))
   {
      SetBit(KeyOut, 1);
   }
   if (!(PINC & BIT(2)))
   {
      SetBit(KeyOut, 2);
   }
   if (!(PINC & BIT(1)))
   {
      SetBit(KeyOut, 3);
   }
   if (!(PINC & BIT(0)))
   {
      SetBit(KeyOut, 4);
   }
   //红外
   if (PINA & BIT(4))
   {
      SetBit(KeyOut, 5);
   }
   //内门磁
   if (PINA & BIT(5))
   {
      SetBit(KeyOut, 6);
   }
   //外门磁
   if (PINA & BIT(6))
   {
      SetBit(KeyOut, 7);
   }
   //内门电锁检测
   if (!(PINA & BIT(1)))
   {
      SetBit(KeyOut, 8);
   }
   //外门电锁检测
   if (!(PINA & BIT(0)))
   {
      SetBit(KeyOut, 9);
   }
   //风机检测
   if (!(PINA & BIT(2)))
   {
      SetBit(KeyOut, 10);
   }
   //照明检测
   if (!(PINA & BIT(3)))
   {
      SetBit(KeyOut, 11);
   }
   return KeyOut;
}


void  KeyScanDeal(uint Key)
{
   uchar tmp;
   static uint KeyLastRec;
   static uint KeyOut;
   static uchar KeyInputCnt[_MAX_DI_];
   if (KeyStartFlag == 0)
   {
      return;
   }
   KeyStartFlag = 0;

   for (tmp = 0; tmp < _MAX_DI_; tmp++)
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
   FLS1.Input.All = KeyOut;
}

void KeyDeal(FLS_DEF *Fls)
{
//------------------------------------------------------------
   if (Fls->Input.Solo.KeyEmc && !Fls->KeyTreated.Solo.KeyEmc)
   {
      Fls->KeyTreated.Solo.KeyEmc = 1;
      Fls->Status.Solo.Emc ^= 1;
   }
   else if (!Fls->Input.Solo.KeyEmc)
   {
      Fls->KeyTreated.Solo.KeyEmc = 0;
   }
//------------------------------------------------------------
   if (Fls->Input.Solo.KeyFan && !Fls->KeyTreated.Solo.KeyFan)
   {
      Fls->KeyTreated.Solo.KeyFan = 1;
      Fls->FOutput.Solo.Fan ^= 1;
   }
   else if (!Fls->Input.Solo.KeyFan)
   {
      Fls->KeyTreated.Solo.KeyFan = 0;
   }
//---------------------------------------------------------------
   if (Fls->Input.Solo.KeyLight && !Fls->KeyTreated.Solo.KeyLight)
   {
      Fls->KeyTreated.Solo.KeyLight = 1;
      Fls->FOutput.Solo.Light ^= 1;
   }
   else if (!Fls->Input.Solo.KeyLight)
   {
      Fls->KeyTreated.Solo.KeyLight = 0;
   }
//------------------------------------------------------------
   if (Fls->Input.Solo.KeyAdd && !Fls->KeyTreated.Solo.KeyAdd)
   {
      Fls->KeyTreated.Solo.KeyAdd = 1;
      if (!Fls->Output.Solo.Fan)
      {
	 Fls->Par.FanRunningTime++;
         if (Fls->Par.FanRunningTime > 99)
         {
            Fls->Par.FanRunningTime = 99;
         }
      }
   }
   else if (!Fls->Input.Solo.KeyAdd)
   {
      Fls->KeyTreated.Solo.KeyAdd = 0;
   }
//------------------------------------------------------------
   if (Fls->Input.Solo.KeySub && !Fls->KeyTreated.Solo.KeySub)
   {
      Fls->KeyTreated.Solo.KeySub = 1;
      if (!Fls->Output.Solo.Fan)
      {
	 Fls->Par.FanRunningTime--;
         if (Fls->Par.FanRunningTime < 5)
         {
            Fls->Par.FanRunningTime = 5;
         }
      }
   }
   else if (!Fls->Input.Solo.KeySub)
   {
      Fls->KeyTreated.Solo.KeySub = 0;
   }

//-----------按键长按加减-------------------
   if (RunFlag.Solo._1ms)
   {
      static uint ReDealCnt = 0;
      if (Fls->KeyTreated.Solo.KeyAdd ^ Fls->KeyTreated.Solo.KeySub)
      {
         if (ReDealCnt++ > 250)
         {
            ReDealCnt = 0;
            Fls->KeyTreated.Solo.KeyAdd = 0;
            Fls->KeyTreated.Solo.KeySub = 0;
         }
      }
      else
      {
         ReDealCnt = 0;
      }
   }
}



void FlsCtrlOutput(FLS_DEF *Fls)
{
//--------------------------
   if (Fls->Output.Solo.Fan)
   {
      FAN_ON;
   }
   else
   {
      FAN_OFF;
   }
//--------------------------
   if (Fls->Output.Solo.WorkLed)
   {
      WORKLED_ON;
   }
   else
   {
      WORKLED_OFF;
   }
//--------------------------
   if (Fls->Output.Solo.Light)
   {
      LIGHT_ON;
   }
   else
   {
      LIGHT_OFF;
   }
//--------------------------
   if (Fls->Output.Solo.Indoor)
   {
      INDOOR_ON;
   }
   else
   {
      INDOOR_OFF;
   }
//--------------------------
   if (Fls->Output.Solo.Outdoor)
   {
      OUTDOOR_ON;
   }
   else
   {
      OUTDOOR_OFF;
   }
}


