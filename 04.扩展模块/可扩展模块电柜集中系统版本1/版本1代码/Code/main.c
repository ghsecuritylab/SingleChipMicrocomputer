

#include "includes.h"

Module_All_Def MODE1;

void  Pin_Init(void)
{
   //input
   ClrBit(DDRC, 0); SetBit(PORTC, 0);
   ClrBit(DDRC, 1); SetBit(PORTC, 1);
   ClrBit(DDRC, 6); SetBit(PORTC, 6);
   ClrBit(DDRC, 7); SetBit(PORTC, 7);
   //output
   SetBit(DDRB, 0); ClrBit(PORTB, 0);
   SetBit(DDRB, 1); ClrBit(PORTB, 1);
   SetBit(DDRB, 2); ClrBit(PORTB, 2);
   SetBit(DDRB, 4); ClrBit(PORTB, 4);
   //pwm
   SetBit(DDRB, 3); ClrBit(PORTB, 3);
   SetBit(DDRD, 4); ClrBit(PORTD, 4);
   SetBit(DDRD, 5); ClrBit(PORTD, 5);
   SetBit(DDRD, 7); ClrBit(PORTD, 7);
   //adc
   ClrBit(DDRA, 0); ClrBit(PORTA, 0);
   ClrBit(DDRA, 1); ClrBit(PORTA, 1);
   ClrBit(DDRA, 2); ClrBit(PORTA, 2);
   ClrBit(DDRA, 3); ClrBit(PORTA, 3);
   //485
   SetBit(DDRD, 2); ClrBit(PORTD, 2);
   //test led
   SetBit(DDRD, 3); ClrBit(PORTD, 3);
   SetBit(DDRD, 6); ClrBit(PORTD, 6);
}

void ModuleOS1(void)
{

}

void ModuleOS2(void)
{

}

void ModuleOS3(void)
{

}

void ModuleOS4(void)
{

}

void ModuleOS5(void)
{

}

void ModuleOS6(void)
{

}

void ModuleChoose(Module_All_Def *mode)
{
   switch (mode->AI.Solo.AI5)
   {
   case MODULE_1: ModuleOS1();
      break;
   case MODULE_2: ModuleOS2();
      break;
   case MODULE_3: ModuleOS3();
      break;
   case MODULE_4: ModuleOS4();
      break;
   case MODULE_5: ModuleOS5();
      break;
   case MODULE_6: ModuleOS6();
      break;
   default:
   //#warning ADC Conversion data is not accurate!!!
      break;
   }
}

void TRACE(const char *fmt, ...)
{
   int nLen;
   va_list args;
   va_start(args, fmt);
   nLen = vsprintf((char *)&UartAppData1.TxRxBuf, fmt, args);
   va_end(args);
   StartUartSend(&UartAppData1, (char *)&UartAppData1.TxRxBuf, nLen);
}

void TotalInterrupt(void)
{
   SREG |= BIT(7);
}

void main(void)
{
   Pin_Init();
   //Timer0_Init();
   Timer1_Init();
   Uart_AppInit();
   Uart_Init();
   MdTcbInit();
   EEpromSaveInit();
   TotalInterrupt();
   //MODE1.Adress485 = 0x02;
   while (1)
   {
      TimerDeal(&Timer1);
      InputScan(InputGet(), &MODE1);
      InputDeal(&MODE1);
      UartTimeOut(&UartAppData1);
      OutputDeal(&MODE1);
      AdcDeal(&MODE1);
      PWMDeal(&MODE1);
      EEpromTimeOut();
      MdPoll();
//      TRACE("Input is %d", MODE1.AI.All[0]);
      Timer1.Flags.Solo._1ms = 0;
   }
}



















