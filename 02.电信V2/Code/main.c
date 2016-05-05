

#include "includes.h"

DianXin_All_Def DianXin1;

void  Pin_Init(void)
{
   //拨码开关
   DDRB  = 0x00;
   PORTB = 0xff;
   //光耦隔离输入
   DDRC  = 0x00;
   PORTC = 0xff;
   //继电器输出
   SetBit(DDRD, 3); ClrBit(PORTD, 3);
   SetBit(DDRD, 4); ClrBit(PORTD, 4);
   SetBit(DDRD, 5); ClrBit(PORTD, 5);
   SetBit(DDRD, 6); ClrBit(PORTD, 6);
   //LED输出
   SetBit(DDRA, 4); ClrBit(PORTA, 4);
   SetBit(DDRA, 5); ClrBit(PORTA, 5);
   SetBit(DDRA, 6); ClrBit(PORTA, 6);
   SetBit(DDRA, 7); ClrBit(PORTA, 7);
   //AI输入
//   ClrBit(DDRA, 0); ClrBit(PORTA, 0);
//   ClrBit(DDRA, 1); ClrBit(PORTA, 1);
   ClrBit(DDRA, 2); ClrBit(PORTA, 2);
   ClrBit(DDRA, 3); ClrBit(PORTA, 3);
   //AO输出
   SetBit(DDRD, 7); SetBit(PORTD, 7);
   //485
   SetBit(DDRD, 2); ClrBit(PORTD, 2);
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
   Timer1_Init();
   Uart_AppInit();
   Uart_Init();
   MdTcbInit();
   Adc_Init(0);
   Timer2_Pwm_Init();
   EEpromSaveInit();
   TotalInterrupt();
   while (1)
   {
      TimerDeal(&Timer1);
      MdPoll();
      if (Timer1.Flags.Solo._1ms)
      {
         InputScan(InputGet(), &DianXin1);
         InputDeal(&DianXin1);
         InputAddr(&DianXin1);
         UartTimeOut(&UartAppData1);
         LedScan(&DianXin1);
         LedDispSet(&DianXin1);
      }
      if (Timer1.Flags.Solo._10ms)
      {
         OutputDeal(&DianXin1);
         EEpromTimeOut();
      }
      if (Timer1.Flags.Solo._30ms)
      {
	 AdcDeal(&DianXin1);
	 PWMDeal(&DianXin1);

      }
      if (Timer1.Flags.Solo._1000ms)
      {
         EEpromWrite();
//         TRACE("hello");
      }

      Timer1.Flags.Solo._1ms = 0;
      Timer1.Flags.Solo._10ms = 0;
      Timer1.Flags.Solo._30ms = 0;
      Timer1.Flags.Solo._100ms = 0;
      Timer1.Flags.Solo._1000ms = 0;

   }
}



















