

#include "includes.h"


void Timer0_Pwm_Init(void)
{
   TCNT0 = 0x00;
   TCCR0 = 0x69; //快速PWM,比较匹配发生时OC0A清零,无分频
   OCR0 = 0;     //输出比较寄存器初值,设置该值可用于调节OC0占空比
}

void Timer1_Pwm_Init(void)
{
   TCCR1A = 0xA1;
   TCCR1B = 0x09;
   TCNT1  = 0x0000;
   ICR1   = 0x0000;
   OCR1A  = 0x0000;
   OCR1B  = 0x0000;
}

void Timer2_Pwm_Init(void)
{
   TCCR2 = 0x69;
   TCNT2 = 0x00;
   OCR2  = 0x00;
}

void Pwm_Init(void)
{
   Timer0_Pwm_Init();
   Timer1_Pwm_Init();
   Timer2_Pwm_Init();
}



#if 0
void SetPwm01(uint16 Voltage)
{
   OCR0 = Voltage;
}

void SetPwm02(uint16 Voltage)
{
   OCR1A = Voltage;
}

void SetPwm03(uint16 Voltage)
{
   OCR1B = Voltage;
}

void SetPwm04(uint16 Voltage)
{
   OCR2 = Voltage;
}


void PWMDeal(Module_All_Def *mode)
{
   if (Timer1.Flags.Solo._10ms == 0)
   {
      return;
   }
   SetPwm01(MODE1.AO.All[0] / 4);
   SetPwm02(MODE1.AO.All[1] / 4);
   SetPwm03(MODE1.AO.All[2] / 4);
   SetPwm04(MODE1.AO.All[3] / 4);
}
#else

void SetBitPwm(uint16 Voltage)
{
   if (Voltage == 0)
   {
      SetBit(PORTD, 7);
   }
   if (Voltage == 1)
   {
      SetBit(PORTD, 5);
   }
   if (Voltage == 2)
   {
      SetBit(PORTD, 4);
   }
   if (Voltage == 3)
   {
      SetBit(PORTB, 3);
   }
}

void ClrBitPwm(uint16 Voltage)
{
   if (Voltage == 0)
   {
      ClrBit(PORTD, 7);
   }
   if (Voltage == 1)
   {
      ClrBit(PORTD, 5);
   }
   if (Voltage == 2)
   {
      ClrBit(PORTD, 4);
   }
   if (Voltage == 3)
   {
      ClrBit(PORTB, 3);
   }
}

void PWMDeal(Module_All_Def *mode)
{
   if (Timer1.Timer0Cnt == 0)
   {
      return;
   }
   Timer1.Timer0Cnt = 0;
   uint08 tmp;
   static uint16 PWMCnt;
   PWMCnt++;
   for (tmp=0; tmp<4; tmp++)
   {
      if (PWMCnt <= (MODE1.AO.All[tmp]/10))
      {
	 SetBitPwm(tmp);
      }
      else if (PWMCnt <= 100)
      {
	 ClrBitPwm(tmp);
      }
      else
      {
	 PWMCnt = 0;
      }
   }
}


#endif


