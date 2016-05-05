

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

#if 0
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

#endif



#if 0
void PWMDeal(Module_All_Def *mode)
{
   static uint08 tmp = 0;
   static uint08 step = 0;
   static uint16 PWMCnt = 0;
   static uint16 PwmBuff[4];
   if (tmp++ >= 4)
   {
      tmp = 0;
   }
   PwmBuff[tmp] = MODE1.AO.All[tmp];
   PWMCnt++;
//   if (PWMCnt <= (PwmBuff[tmp] / 10) )
//   {
//      SetBitPwm(tmp);
//   }
//   else if (PWMCnt <= 100)
//   {
//      ClrBitPwm(tmp);
//   }
//   else
//   {
//      PWMCnt = 0;
//   }
   if (step == 0)
   {

   }
}

#else

#define  PWM_1_OFF()  SetBit(PORTB, 1)
#define  PWM_2_OFF()  SetBit(PORTB, 2)
#define  PWM_3_OFF()  SetBit(PORTB, 3)
#define  PWM_4_OFF()  SetBit(PORTB, 4)
#define  PWM_1_ON()   ClrBit(PORTB, 1)
#define  PWM_2_ON()   ClrBit(PORTB, 2)
#define  PWM_3_ON()   ClrBit(PORTB, 3)
#define  PWM_4_ON()   ClrBit(PORTB, 4)

void AO3_PWM(uint16 Voltage)
{
   if (Voltage >= 500)
   {
      Voltage = Voltage / 4 + 5;
   }
   else
   {
      Voltage = Voltage / 4;
   }
   OCR0 = Voltage;
}


void AO_TIMER_PWM(uint16 Voltage, uint08 tmp)
{
   static uint16 PwmBuff = 0;
   static uint16 Count = 0;
   if (Count++ > 1000)
   {
      Count = 0;
   }
   if (Voltage <= 500)
   {
      Voltage = Voltage - 50;
   }
   PwmBuff = Voltage;
   if (Count < PwmBuff)
   {
      SetBit(PORTB, tmp);
   }
   else
   {
      ClrBit(PORTB, tmp);
   }
}

void AO_1AND2AND4_PWM()
{
   static uint08 NumberCount = 0;
   if (NumberCount == 0)
   {
      AO_TIMER_PWM(MODE1.AO.Solo.AO1, 1);
      NumberCount++;
   }
   else if (NumberCount == 1)
   {
      AO_TIMER_PWM(MODE1.AO.Solo.AO2, 2);
      NumberCount++;
   }
   else
   {
      AO_TIMER_PWM(MODE1.AO.Solo.AO4, 4);
      NumberCount = 0;
   }
}

#endif



