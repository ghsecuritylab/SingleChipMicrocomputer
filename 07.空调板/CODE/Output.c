
#include "includes.h"



void LedOutputScan(AHU_DEF *Ahu)
{
   if (Ahu->Led.Solo.LedRunning)
   {
      SetBit(PORTE, 7);
   }
   else
   {
      ClrBit(PORTE, 7);
   }
   if (Ahu->Led.Solo.LedStadby)
   {
      SetBit(PORTB, 0);
   }
   else
   {
      ClrBit(PORTB, 0);
   }
   if (Ahu->Led.Solo.LedError)
   {
      SetBit(PORTB, 2);
   }
   else
   {
      ClrBit(PORTB, 2);
   }
   if (Ahu->Led.Solo.LedEfficient)
   {
      SetBit(PORTB, 3);
   }
   else
   {
      ClrBit(PORTB, 3);
   }
   if (Ahu->Led.Solo.LedNgt)
   {
      SetBit(PORTB, 4);
   }
   else
   {
      ClrBit(PORTB, 4);
   }
}


void TmepDisplayScan(AHU_DEF *Ahu)
{
   if (Ahu->Temperature.Solo.SEG_A)
   {
      SetBit(PORTA, 4);
   }
   else
   {
      ClrBit(PORTA, 4);
   }
   if (Ahu->Temperature.Solo.SEG_B)
   {
      SetBit(PORTA, 3);
   }
   else
   {
      ClrBit(PORTA, 3);
   }
   if (Ahu->Temperature.Solo.SEG_C)
   {
      SetBit(PORTC, 7);
   }
   else
   {
      ClrBit(PORTC, 7);
   }
   if (Ahu->Temperature.Solo.SEG_D)
   {
      SetBit(PORTG, 2);
   }
   else
   {
      ClrBit(PORTG, 2);
   }
   if (Ahu->Temperature.Solo.SEG_E)
   {
      SetBit(PORTA, 7);
   }
   else
   {
      ClrBit(PORTA, 7);
   }
   if (Ahu->Temperature.Solo.SEG_F)
   {
      SetBit(PORTA, 5);
   }
   else
   {
      ClrBit(PORTA, 5);
   }
   if (Ahu->Temperature.Solo.SEG_G)
   {
      SetBit(PORTA, 6);
   }
   else
   {
      ClrBit(PORTA, 6);
   }
   if (Ahu->Temperature.Solo.SEG_DP)
   {
      SetBit(PORTE, 5);
   }
   else
   {
      ClrBit(PORTE, 5);
   }
}


void RhDisplayScan(AHU_DEF *Ahu)
{
   if (Ahu->Humidity.Solo.SEG_A)                           
   {                                                       
      SetBit(PORTC, 2);                                    
   }                                                       
   else                                                    
   {                                                       
      ClrBit(PORTC, 2);                                    
   }                                                       
   if (Ahu->Humidity.Solo.SEG_B)                           
   {
      SetBit(PORTC, 3);
   }
   else
   {
      ClrBit(PORTC, 3);
   }
   if (Ahu->Humidity.Solo.SEG_C)
   {
      SetBit(PORTC, 4);
   }
   else
   {
      ClrBit(PORTC, 4);
   }
   if (Ahu->Humidity.Solo.SEG_D)
   {
      SetBit(PORTC, 5);
   }
   else
   {
      ClrBit(PORTC, 5);
   }
   if (Ahu->Humidity.Solo.SEG_E)
   {
      SetBit(PORTC, 6);
   }
   else
   {
      ClrBit(PORTC, 6);
   }
   if (Ahu->Humidity.Solo.SEG_F)
   {
      SetBit(PORTC, 1);
   }
   else
   {
      ClrBit(PORTC, 1);
   }
   if (Ahu->Humidity.Solo.SEG_G)
   {
      SetBit(PORTC, 0);
   }
   else
   {
      ClrBit(PORTC, 0);
   }
   if (Ahu->Humidity.Solo.SEG_DP)
   {
      SetBit(PORTE, 6);
   }
   else
   {
      ClrBit(PORTE, 6);
   }
}
		     
#if 1


const uint08 numbers[] =
{
   _FLAG_0,
   _FLAG_1,
   _FLAG_2,
   _FLAG_3,
   _FLAG_4,
   _FLAG_5,
   _FLAG_6,
   _FLAG_7,
   _FLAG_8,
   _FLAG_9,
   _FLAG_A,
   _FLAG_B,
   _FLAG_C,
   _FLAG_D,
   _FLAG_E,
   _FLAG_F,
};
		     
		     
void NumberDisplayScan(AHU_DEF *Ahu)
{
   static uint08 step = 0;
   TMEP_100_BIT_OFF();
   RH_100_BIT_OFF();
   TMEP_10_BIT_OFF();
   RH_10_BIT_OFF();
   TMEP_1_BIT_OFF();
   RH_1_BIT_OFF();
   if (step == 0)
   {
      TMEP_1_BIT_ON();
      RH_1_BIT_ON();
      step++;
   }
   else if (step == 1)
   {
      TMEP_10_BIT_ON();
      RH_10_BIT_ON();
      step++;
   }
   else if (step == 2)
   {
      TMEP_100_BIT_ON();
      RH_100_BIT_ON();
      step = 0;
   }
}
    
void DisplayNumber(uint16 num)
{
   if (num > 0)
   {
      Ahu1.Temperature.All = numbers[num / 100];
      Ahu1.Temperature.All = numbers[num/10%10];
      Ahu1.Temperature.All = numbers[num%10];
   }
}
 
 
#endif
