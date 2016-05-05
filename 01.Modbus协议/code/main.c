
#include "includes.h"

Module_All_Def MODE1;

void  Pin_init(void)
{
   //input
   ClrBit(DDRC, 0); SetBit(PORTC, 0);
   ClrBit(DDRC, 1); SetBit(PORTC, 1);
   ClrBit(DDRD, 6); SetBit(PORTD, 6);
   ClrBit(DDRD, 7); SetBit(PORTD, 7);
   //output
   SetBit(DDRD, 3); ClrBit(PORTD, 3);
   SetBit(DDRD, 4); ClrBit(PORTD, 4);
   SetBit(DDRD, 5); ClrBit(PORTD, 5);
   //pwm
   SetBit(DDRB, 1); ClrBit(PORTB, 1);
   SetBit(DDRB, 2); ClrBit(PORTB, 2);
   SetBit(DDRB, 3); ClrBit(PORTB, 3);
   SetBit(DDRB, 4); ClrBit(PORTB, 4);
   //adc
   ClrBit(DDRA, 0); ClrBit(PORTA, 0);
   ClrBit(DDRA, 1); ClrBit(PORTA, 1);
   ClrBit(DDRA, 2); ClrBit(PORTA, 2);
   ClrBit(DDRA, 3); ClrBit(PORTA, 3);
   ClrBit(DDRA, 4); ClrBit(PORTA, 4);
   ClrBit(DDRA, 5); ClrBit(PORTA, 5);
   //485
   SetBit(DDRD, 2); ClrBit(PORTD, 2);
   //±¸ÓÃ
   SetBit(DDRB, 0); ClrBit(PORTB, 0);
   //test led
   SetBit(DDRC, 6); ClrBit(PORTC, 6);
   SetBit(DDRC, 7); ClrBit(PORTC, 7);
}
void OutputDeal(Module_All_Def *mode)
{
   if (mode->DO.Solo.DO3)
   {
      SetBit(PORTD, 3);
   }
   else
   {
      ClrBit(PORTD, 3);
   }
   if (mode->DO.Solo.DO2)
   {
      SetBit(PORTD, 4);
   }
   else
   {
      ClrBit(PORTD, 4);
   }
   if (mode->DO.Solo.DO1)
   {
      SetBit(PORTD, 5);
   }
   else
   {
      ClrBit(PORTD, 5);
   }

//----------------------------------
   if (mode->DO.Solo.LED1)
   {
      ClrBit(PORTC, 6);
   }
   else
   {
      SetBit(PORTC, 6);
   }
   if (mode->DO.Solo.LED2)
   {
      ClrBit(PORTC, 7);
   }
   else
   {
      SetBit(PORTC, 7);
   }
}


void PrintString(const char *fmt, ...)
{
   int nLen;
   va_list args;
   va_start(args, fmt);
   nLen = vsprintf((char *)&UartAppData1.TxRxBuff, fmt, args);
   va_end(args);
   StartUartSend(&UartAppData1, (char *)&UartAppData1.TxRxBuff, nLen);
}



void main()
{
   Pin_init();
   Timer1_Init();
   Uart_Init();

   while (1)
   {
      TimerDeal(&Timer1);
      OutputDeal(&MODE1);

      if (Timer1.Flags.Solo._1ms)
      {
	 UartTimeOut(&UartAppData1);
      }
      if (Timer1.Flags.Solo._5000ms)
      {
//	 PrintString("hello");
//	 StartUartSend(&UartAppData1,"hello\n",6);
      }
      SlaveModbus(&MdTcp1);
      Timer1.Flags.All[0] = 0x00;
      MODE1.DO.Solo.LED1 = Timer1.Flags.Solo.FastBlink;
   }
}
