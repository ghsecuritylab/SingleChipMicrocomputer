


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


#if 1
uint16 GetOneAdc(uint08 Channel)
{
   uint16 addata;
//   ADMUX = 0xc0;              //2.56V ��Ƭ�ڻ�׼��ѹԴ,ADC0
   ADMUX = 0x40 | Channel;     //ת������Ҷ���,AVCC�ο���ѹ,0ͨ��
   ADCSRA |= BIT(7);           //��λADEN
   ADCSRA |= BIT(6);           //ADSC��λ,����AD
   while (!(ADCSRA & 0x10));   //�жϲ�ѯ
   ADCSRA |= BIT(4);          //����жϱ�־λ
   addata = ADCL;
   addata = addata + ADCH * 256;
   return addata;
}

void AdcDeal(Module_All_Def *mode)
{
   if (Timer1.Flags.Solo._20ms == 0)
   {
      return;
   }
   uint08 tmp;
   static uint08 Channel;
   static uint16 Buff[20];
   for (tmp = 0; tmp < 20; tmp++)
   {
      Buff[tmp] = GetOneAdc(Channel);
   }
   mode->AI.All[Channel] = AverageValue(Buff, 20);
   Channel++;
   if (Channel >= 5)
   {
      Channel = 0;
   }
}

#else

void Adc_Init(uint08 Channel)
{
   ACSR = 0x80;         //��ģ��Ƚ���
   ADMUX = 0x40 | Channel; //ת������Ҷ���,AVCC�ο���ѹ,0ͨ��
   ADCSRA = 0xC8;       //��ADC,����ADC�ж�,2��Ƶ
}


#pragma vector = ADC_vect
__interrupt void ADC_ISR(void)
{
   MODE1.AI.Solo.ADCBuff = ADC & 0x3FF;
   MODE1.Status.Solo.ADCFlag = 1;
}


void AdcDeal(Module_All_Def *mode)
{
   if (Timer1.Flags.Solo._20ms == 0)
   {
      return;
   }
   static uint16 Buff[20];
   static uint08 tmp = 0;
   static uint08 Channel = 0;
   Adc_Init(Channel);
   if (mode->Status.Solo.ADCFlag == 0)
   {
      return;
   }
   MODE1.Status.Solo.ADCFlag = 0;
   if (tmp < 20)
   {
      Buff[tmp++] = MODE1.AI.Solo.ADCBuff;
   }
   else
   {
      tmp = 0;
      MODE1.AI.All[Channel++] = AverageValue(Buff, 20);
      if (Channel >= 5)
      {
	 Channel = 0;
      }
   }
}

#endif



