
#include "includes.h"


#define KEY1   (PINF&BIT(1))   //工作按键
#define KEY2   (PINE&BIT(3))   //值班按键
#define KEY3   (PINB&BIT(6))   //正负压按键
#define KEY4   (PIND&BIT(4))   //备用按键
#define KEY5   (PINF&BIT(3))   //温度上调按键
#define KEY6   (PINF&BIT(0))   //温度下调按键
#define KEY7   (PING&BIT(4))   //湿度上调按键
#define KEY8   (PIND&BIT(6))   //湿度下调按键
#define KEY9   (PINB&BIT(5))   //设定按键


uint16  KeyGet(void)
{
   uint16 KeyOut = 0;
   if (!KEY1)
   {
      SetBit(KeyOut, 0); 
   }
   if (!KEY2)
   {
      SetBit(KeyOut, 1); 
   }
   if (!KEY3)
   {
      SetBit(KeyOut, 2); 
   }
   if (!KEY4)
   {
      SetBit(KeyOut, 3); 
   }
   if (!KEY5)
   {
      SetBit(KeyOut, 4); 
   }
   if (!KEY6)
   {
      SetBit(KeyOut, 5);
   }
   if (!KEY7)
   {
      SetBit(KeyOut, 6); 
   }
   if (!KEY8)
   {
      SetBit(KeyOut, 7); 
   }
   if (!KEY9)
   {
      SetBit(KeyOut, 8);
   }
   return KeyOut;
}


#define _MAX_DI_ 9
void  KeyScanDeal(uint16 Key)
{
   uchar tmp;
   static uint16 KeyLastRec;
   static uint16 KeyOut;
   static uint16 KeyInputCnt[_MAX_DI_];

   for (tmp = 0; tmp < 9; tmp++)
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
   Ahu1.Key.All = KeyOut;
}


void KeyRunning(AHU_DEF *Ahu)
{
   if (Ahu->Key.Solo.KeyRun && !Ahu->KeyCheck.Solo.KeyRun)
   {
      Ahu->KeyCheck.Solo.KeyRun = 1;
      Ahu->State.Solo.KeyRun ^= 1;
   }  
   else if (!Ahu->Key.Solo.KeyRun)
   {
      Ahu->KeyCheck.Solo.KeyRun = 0;
   }
//---------------------------------
   if (Ahu->State.Solo.KeyRun)
   {
      Ahu->Led.Solo.LedRunning = 1;
   }
   else
   {
      Ahu->Led.Solo.LedRunning = 0;
   }
}

void KeyStadby(AHU_DEF *Ahu)
{
   if (Ahu->Key.Solo.KeyStadby && !Ahu->KeyCheck.Solo.KeyStadby)
   {
      Ahu->KeyCheck.Solo.KeyStadby = 1;
      Ahu->State.Solo.KeyStadby ^= 1;
   }  
   else if (!Ahu->Key.Solo.KeyStadby)
   {
      Ahu->KeyCheck.Solo.KeyStadby = 0;
   }
//---------------------------------
   if (Ahu->State.Solo.KeyStadby)
   {
      Ahu->Led.Solo.LedStadby = 1;
   }
   else
   {
      Ahu->Led.Solo.LedStadby = 0;
   }
}


void KeyNgt(AHU_DEF *Ahu)
{
   if (Ahu->Key.Solo.KeyNgt && !Ahu->KeyCheck.Solo.KeyNgt)
   {
      Ahu->KeyCheck.Solo.KeyNgt = 1;
      Ahu->State.Solo.KeyNgt ^= 1;

      Ahu1.Led.Solo.LedRunning = 1;
   }  
   else if (!Ahu->Key.Solo.KeyNgt)
   {
      Ahu->KeyCheck.Solo.KeyNgt = 0;
   }
//---------------------------------
   if (Ahu->State.Solo.KeyNgt)
   {
      Ahu->Led.Solo.LedNgt = 1;
   }
   else
   {
      Ahu->Led.Solo.LedNgt = 0;
   }
}

void KeyBackup(AHU_DEF *Ahu)
{
   if (Ahu->Key.Solo.KeyBackup && !Ahu->KeyCheck.Solo.KeyBackup)
   {
      Ahu->KeyCheck.Solo.KeyBackup = 1;
      Ahu->State.Solo.KeyBackup ^= 1;
   }  
   else if (!Ahu->Key.Solo.KeyBackup)
   {
      Ahu->KeyCheck.Solo.KeyBackup = 0;
   }
//---------------------------------
   if (Ahu->State.Solo.KeyBackup)
   {
      ;
   }
   else
   {
      ;
   }
}

void KeySetting(AHU_DEF *Ahu)
{
   if (Ahu->Key.Solo.KeySetting && !Ahu->KeyCheck.Solo.KeySetting)
   {
      Ahu->KeyCheck.Solo.KeySetting = 1;
      Ahu->State.Solo.KeySetting = 1;
   }  
   else if (!Ahu->Key.Solo.KeySetting)
   {
      Ahu->KeyCheck.Solo.KeySetting = 0;
   }

   if (Ahu->State.Solo.KeySetting)
   {
      Ahu->State.Solo.KeySetting = 0;
//      Ahu->Temperature
   }
}

void KeyTmepAdd(AHU_DEF *Ahu)
{
   if (Ahu->Key.Solo.KeyTmepAdd && !Ahu->KeyCheck.Solo.KeyTmepAdd)
   {
      Ahu->KeyCheck.Solo.KeyTmepAdd = 1;
      Ahu->State.Solo.KeyTmepAdd = 1;
   }  
   else if (!Ahu->Key.Solo.KeyTmepAdd)
   {
      Ahu->KeyCheck.Solo.KeyTmepAdd = 0;
   }
}

void KeyTmepSub(AHU_DEF *Ahu)
{

}


void KeyAllStateDeal(AHU_DEF *Ahu)
{
   KeyRunning(Ahu);
   KeyStadby(Ahu);
   KeyNgt(Ahu);
}

