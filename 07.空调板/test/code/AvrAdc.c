
#include "includes.h"
BuffFliter RoomTempFilter;
//#define ADC_POLL 0

#define KYJ_SCALE1000 1000


void MaoPao(uint16 *TrgBuff, uint08 MaxCnt)
{
   uint16 tmp;
   uint16 tmp2;
   uint16 tmpVolt;
   for (tmp = 0; tmp < MaxCnt; tmp++)
   {
      for (tmp2 = 0; tmp2 < (MaxCnt - tmp - 1); tmp2++)
      {
         if (TrgBuff[tmp2] < TrgBuff[tmp2 + 1])
         {
            tmpVolt = TrgBuff[tmp2];
            TrgBuff[tmp2] = TrgBuff[tmp2 + 1];
            TrgBuff[tmp2 + 1] = tmpVolt;
         }
      }
   }
}

uint16 uint16Average(uint16 *p2data, uint16 cnt)
{
   uint32 tmpSum = 0;
   uint08 tmp = 0;
   for (tmp = 0; tmp < cnt; tmp++)
   {
      tmpSum += p2data[tmp];
   }
   return (tmpSum / cnt);
}

uint16 TempGet(BuffFliter *Filter, uint16 AdInput)
{
   if (Filter->Flag.Cnt < 24)
   {
      Filter->Buff[Filter->Flag.Cnt] = AdInput;
      Filter->Flag.Cnt++;
      Filter->Average = uint16Average(Filter->Buff, Filter->Flag.Cnt);
      return Filter->Average;
   }
   else
   {
      Filter->Average = uint16Average(Filter->Buff, Filter->Flag.Cnt);
      Filter->Flag.Cnt = 0;
      return Filter->Average;
   }
//   else
//   {
//      if (AdInput > Filter->Average)
//      {
//         Filter->Buff[23] = AdInput;
//      }
//      else
//      {
//         Filter->Buff[0] = AdInput;
//      }
//      MaoPao(Filter->Buff, 24);
//      Filter->Average = uint16Average(&Filter->Buff[4], 16);
//      return Filter->Average;
//   }
}


void AdcInit()
{
   ADMUX = 0x43;
   {
      //T0 OVF
//    SetBit(SFIOR, 7);
//    ClrBit(SFIOR, 6);
//    ClrBit(SFIOR, 5);
   }
   ADCSRA = 0xED;
// ADCSRA = 0xAD;
}


#pragma vector = ADC_vect
__interrupt void ADC_ISR(void)
{
   RoomTempFilter.NowBuff = ADC;
   RoomTempFilter.Flag.New = 1;
// PORTA ^= BIT(6);
}

uint16 ykxbTemp(uint16 Xint, uint16 K)
{
   uint32 tmp = Xint;
   tmp *=  84;
   tmp = 68100 - tmp;
   tmp += 50;
   tmp /= 100;


   //斜率修正
   tmp -= 5;

   //限制大小
   if (tmp > 1000)
   {
      tmp = 0;
   }

   return tmp;
}

//void TempAdjust()
//{
//   uint08 SaveFlag = 0;
//   uint32 tmp;
//   if (FC1.Run.RoomTempAid != 0)
//   {
//      tmp = FC1.Run.RoomTempAid * 100;
//      tmp = 7105 - tmp;
//      tmp /= 9;
//      tmp = tmp / RoomTempFilter.NowBuff;
//      FC1.Run.RoomTempKvalue = tmp;
//      FC1.Run.RoomTempAid = 0;
//      SaveFlag = 1;
//   }
//}

uint16 nowTemp;
uint16 lastTemp;
BOOL oneTime;
void AdcGetAll(FCDataBaseDef *FC)
{

   uint32 tmp;
   if (!RoomTempFilter.Flag.New)
   {
      return;
   }
   RoomTempFilter.Flag.New = 0;
// TempAdjust();
   if (RoomTempFilter.Flag.Cnt < 24)
   {
      RoomTempFilter.Buff[RoomTempFilter.Flag.Cnt] = RoomTempFilter.NowBuff;
      RoomTempFilter.Flag.Cnt++;
   }
   else
   {
      RoomTempFilter.Average = uint16Average(RoomTempFilter.Buff, RoomTempFilter.Flag.Cnt);
      RoomTempFilter.Flag.Cnt = 0;
      nowTemp = ykxbTemp(RoomTempFilter.Average, FC->Buff.RoomTempKvalue);
      if (nowTemp != lastTemp && !oneTime)
      {
         FC->Buff.WorkTimer.TempChangeTimer = 200;
         oneTime = 1;
         lastTemp = nowTemp;
      }
      if (FC->Buff.WorkTimer.TempChangeTimer == 0)
      {
         FC->Buff.RoomTemp = lastTemp;
         oneTime = 0;
      }
   }
}















