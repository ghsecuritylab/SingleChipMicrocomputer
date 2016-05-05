


#include "includes.h"


uint16 AverageValue(uint16 *p2data, uint16 cnt)
{
   uint32 itmp = 0;
   uint08 tmp = 0;
   for (tmp = 2; tmp < cnt; tmp++)
   {
      itmp += p2data[tmp];
   }
   return (itmp / (cnt-4));
}

uint16 MaoPao(uint16 *p2buff) //冒泡排序法从小到大排列
{
   uint08 tmp = 0;
   uint08 tmpx = 0;
   uint16 itmp = 0;
   uint32 SumValue = 0;
   for (tmp = 0; tmp < 24 - 1; tmp++)
   {
      for (tmpx = 0; tmpx < 24 - tmp - 1; tmpx++)
      {
         if (p2buff[tmpx] < p2buff[tmpx + 1])
         {

            itmp = p2buff[tmpx];
            p2buff[tmpx] = p2buff[tmpx + 1];
            p2buff[tmpx + 1] = itmp;
         }
      }
   }
   for (tmp = 4; tmp < 20; tmp++)
   {
      SumValue += p2buff[tmp];
   }
   return SumValue / 16;
}

#if 0
uint16 GetOneAdc(uint08 Channel)
{
   uint16 addata;
   ADMUX = 0x40 | (Channel & 0x0f);     //转换结果右对齐,AVCC参考电压,0通道
   ADCSRA |= BIT(7);           //置位ADEN
   ADCSRA |= BIT(6);           //ADSC置位,启动AD
   while (!(ADCSRA & 0x10));   //中断查询
   ADCSRA |= BIT(4);          //清除中断标志位
   addata = ADCL;
   addata = addata + ADCH * 256;
   return addata;
}

void AdcDeal(Module_All_Def *mode)
{
   static uint08 tmp = 0;
   static uint08 Channel = 0;
   static uint16 Buff[24];
   Buff[tmp++] = GetOneAdc(Channel);
   if (tmp >= 24)
   {
      tmp = 0;
   }
   else
   {
      return;
   }
   mode->AI.All[Channel++] = MaoPao(Buff);
   if (Channel >= 6)
   {
      Channel = 0;
   }
}

#else

void Adc_Init(uint08 Channel)
{
   ACSR = 0x80;         //关模拟比较器
   ADMUX = 0x40 | (Channel & 0x0f); //转换结果右对齐,AVCC参考电压,0通道
   ADCSRA = 0xC8;       //打开ADC,允许ADC中断,2分频
}


uint16 buff = 0;
uint08 flags = 0;

#pragma vector = ADC_vect
__interrupt void ADC_ISR(void)
{
   buff = ADC & 0x3FF;
   flags = 1;
}

void AdcDeal(Module_All_Def *mode)
{
   static uint16 Buff[24];
   static uint08 tmp = 0;
   static uint08 Channel = 0;
   if (flags == 1)
   {
      flags = 0;
      Adc_Init(Channel);
      ADCSRA_ADEN = 1;   
      Buff[tmp++] = buff;
      if (tmp >= 24)
      {
         tmp = 0;
      }
      else
      {
         return;
      }
      mode->AI.All[Channel++] = MaoPao(Buff);
      if (Channel >= 6)
      {
         Channel = 0;
      }
   }
}


#endif



