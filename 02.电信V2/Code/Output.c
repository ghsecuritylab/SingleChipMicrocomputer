
#include "includes.h"



void OutputDeal(DianXin_All_Def *pData)
{
   if (pData->DO.Solo.DO1)
   {
      SetBit(PORTD, 6);
   }
   else
   {
      ClrBit(PORTD, 6);
   }
   if (pData->DO.Solo.DO2)
   {
      SetBit(PORTD, 5);
   }
   else
   {
      ClrBit(PORTD, 5);
   }
   if (pData->DO.Solo.DO3)
   {
      SetBit(PORTD, 4);
   }
   else
   {
      ClrBit(PORTD, 4);
   }
   if (pData->DO.Solo.DO4)
   {
      SetBit(PORTD, 3);
   }
   else
   {
      ClrBit(PORTD, 3);
   }
   //-----------------------------
}


void _164Output(uint08 Data)
{
   uint08 tmp;
   for (tmp = 0; tmp < 8; tmp++)
   {
      _164SCK_LOW();
      if (Data & 0x01)
      {
         _164DATA_HIGH();
      }
      else
      {
         _164DATA_LOW();
      }
      _164SCK_HIGH();
      Data >>= 1;
   }
}

void LedDispSet(DianXin_All_Def *pData)
{
   pData->Leds.Solo.LED_DI_1 = 0;
   pData->Leds.Solo.LED_DI_2 = 0;
   pData->Leds.Solo.LED_DI_3 = 0;
   pData->Leds.Solo.LED_DI_4 = 0;
   pData->Leds.Solo.LED_DI_5 = 0;
   pData->Leds.Solo.LED_DI_6 = 0;
   if (pData->DI.Solo.DI2)
   {
      pData->Leds.Solo.LED_DI_1 = 1;
   }
   if (pData->DI.Solo.DI5)
   {
      pData->Leds.Solo.LED_DI_2 = 1;
   }
   if (pData->DI.Solo.DI1)
   {
      pData->Leds.Solo.LED_DI_3 = 1;
   }
   if (pData->DI.Solo.DI6)
   {
      pData->Leds.Solo.LED_DI_4 = 1;
   }
   if (pData->DI.Solo.DI8)
   {
      pData->Leds.Solo.LED_DI_5 = 1;
   }
   if (pData->DI.Solo.DI7)
   {
      pData->Leds.Solo.LED_DI_6 = 1;
   }

   pData->Leds.Solo.LED_DO_1 = 0;
   pData->Leds.Solo.LED_DO_2 = 0;
   pData->Leds.Solo.LED_DO_3 = 0;
   pData->Leds.Solo.LED_DO_4 = 0;
   if (pData->DO.Solo.DO4)
   {
      pData->Leds.Solo.LED_DO_1 = 1;
   }
   if (pData->DO.Solo.DO3)
   {
      pData->Leds.Solo.LED_DO_2 = 1;
   }
   if (pData->DO.Solo.DO1)
   {
      pData->Leds.Solo.LED_DO_3 = 1;
   }
   if (pData->DO.Solo.DO2)
   {
      pData->Leds.Solo.LED_DO_4 = 1;
   }

   pData->Leds.Solo.LED_RXD = 0;
   pData->Leds.Solo.LED_TXD = 0;
   if (UartAppData1.RxTimeout > 0)
   {
      pData->Leds.Solo.LED_RXD = Timer1.Flags.Solo.Blink;
   }
   if (UartAppData1.TxTimeout > 0)
   {
      pData->Leds.Solo.LED_TXD = Timer1.Flags.Solo.Blink;
   }

   pData->Leds.Solo.LED_AI_1 = 0;
   pData->Leds.Solo.LED_AI_2 = 0;
   if (pData->AI.Solo.AI3 > 5)
   {
      pData->Leds.Solo.LED_AI_1 = 1;
   }
   if (pData->AI.Solo.AI4 > 5)
   {
      pData->Leds.Solo.LED_AI_2 = 1;
   }

   pData->Leds.Solo.LED_AO_1 = 0;
   if (pData->AO.Solo.AO1)
   {
      pData->Leds.Solo.LED_AO_1 = 1;
   }

   pData->Leds.Solo.LED_RUN = 0;
   if (1)
   {
      pData->Leds.Solo.LED_RUN = Timer1.Flags.Solo.FastBlink;
   }
}



uint08 LedBuff[2];
void LedBuffSet(DianXin_All_Def *pData)
{
//   if (pData->Leds.All[0] > 0 || pData->Leds.All[1] > 0)
//   {
//      LedBuff[0] = ~pData->Leds.All[0];
//      LedBuff[1] = ~pData->Leds.All[1];
//   }
//   else
//   {
//      LedBuff[0] = 0x00;
//      LedBuff[1] = 0x00;
//   }
      LedBuff[0] = ~pData->Leds.All[0];
      LedBuff[1] = ~pData->Leds.All[1];
}

void LedOutput()
{
   static uint08 step = 0;
   LEDCOM1_OFF();
   LEDCOM2_OFF();
   if (step == 0)
   {
      _164Output(LedBuff[0]);
      LEDCOM1_ON();
      step++;
   }
   else if (step == 1)
   {
      _164Output(LedBuff[1]);
      LEDCOM2_ON();
      step = 0;
   }
}

void LedScan(DianXin_All_Def *pData)
{
   LedBuffSet(pData);
   LedOutput();
}
