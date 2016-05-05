#include "includes.h"





void UART1_TXEN(void)
{
   SetBit(PORTD, 1);
}
void UART1_TXDIS(void)
{
   ClrBit(PORTD, 1);
}

void UART2_TXEN(void)
{
   SetBit(PORTE, 2);
}
void UART2_TXDIS(void)
{
   ClrBit(PORTE, 2);
}

void Uart_Init(void)
{
   //UCSRB = 0x00; //允许发送接受中断和使能
   UCSR1A = 0x01; //异步正常模式
// UCSRA = 0x03; //异步bs模式
   UCSR1B = 0xB8; //允许发送接受中断和使能
                  //UCSRB = 0xF8; //允许发送接受中断和使能
   UCSR1C = 0x86; //8位数据
   UBRR1L = (SYS_OSC / 9600 / 16 - 1) % 256;
   UBRR1H = (SYS_OSC / 9600 / 16 - 1) / 256;
}
void Uart2_Init(void)
{
   //UCSRB = 0x00; //允许发送接受中断和使能
   UCSR0A = 0x01; //异步正常模式
// UCSRA = 0x03; //异步bs模式
   UCSR0B = 0xB8; //允许发送接受中断和使能
                  //UCSRB = 0xF8; //允许发送接受中断和使能
   UCSR0C = 0x86; //8位数据
   UBRR0L = (SYS_OSC / 9600 / 16 - 1) % 256;
   UBRR0H = (SYS_OSC / 9600 / 16 - 1) / 256;
}
void Uart_AppInit(void)
{
   UartAppData1.EnTxPin = UART1_TXEN;
   UartAppData1.DisTxPin = UART1_TXDIS;
   UART1_TXDIS();
}
void Uart2_AppInit(void)
{
   UartAppData2.EnTxPin = UART2_TXEN;
   UartAppData2.DisTxPin = UART2_TXDIS;
   UART2_TXDIS();
}


#define ___UART1__

#pragma vector = USART1_RXC_vect
__interrupt void UART0_RX_ISR(void)
{
   UCHAR ucChar;
   UartType *P2data = &UartAppData1;
   ucChar = UDR1;
   P2data->LivingTime = 1000;
// P2data->LivingTime = 2000;
   if (!P2data->Flags.Solo.RecFlame)
   {
      P2data->RxTimeout = __5ms__;
      if (P2data->RecCnt < (UART_BUFF_SIZE - 1))
      {
         P2data->TxRxBuf[P2data->RecCnt] = ucChar;
         P2data->RecCnt++;
         if (P2data->RecCnt == 8)
         {
            P2data->Flags.Solo.ShortFrame = 1;
         }
         if (P2data->RecCnt == UART_BUFF_SIZE - 1)
         {
            P2data->Flags.Solo.RecFlame = 1;
         }
      }
   }
}

#pragma vector = USART1_UDRE_vect
__interrupt void UART_TX_ISR(void)
{
   UartType *P2data = &UartAppData1;
   if (P2data->SentCnt <  P2data->ToSend)
   {
      UCSR1A_TXC1 = 0;
      UDR1 = P2data->TxRxBuf[P2data->SentCnt];
      P2data->SentCnt++;
   }
   else
   {
      UCSR1B_UDRIE1 = 0;
      UCSR1B_TXCIE1 = 1;
   }
}
#pragma vector = USART1_TXC_vect
__interrupt void UART_TXC_ISR(void)
{
   UartType *P2data = &UartAppData1;
   P2data->Flags.Solo.TxStart = 0;
   Run_void(P2data->DisTxPin);
   UCSR1B_TXCIE1 = 0;
}


#define ___UART2__

#pragma vector = USART0_RXC_vect
__interrupt void UART2_RX_ISR(void)
{
   UCHAR ucChar;
   UartType *P2data = &UartAppData2;
   ucChar = UDR0;
   P2data->LivingTime = 1000;
// P2data->LivingTime = 2000;
   if (!P2data->Flags.Solo.RecFlame)
   {
      P2data->RxTimeout = __5ms__;
      if (P2data->RecCnt < (UART_BUFF_SIZE - 1))
      {
         P2data->TxRxBuf[P2data->RecCnt] = ucChar;
         P2data->RecCnt++;
         if (P2data->RecCnt == 8)
         {
            P2data->Flags.Solo.ShortFrame = 1;
         }
         if (P2data->RecCnt == UART_BUFF_SIZE - 1)
         {
            P2data->Flags.Solo.RecFlame = 1;
         }
      }
   }
}

#pragma vector = USART0_UDRE_vect
__interrupt void UART2_TX_ISR(void)
{
   UartType *P2data = &UartAppData2;
   if (P2data->SentCnt <  P2data->ToSend)
   {
      UCSR0A_TXC0 = 0;
      UDR0 = P2data->TxRxBuf[P2data->SentCnt];
      P2data->SentCnt++;
   }
   else
   {
      UCSR0B_UDRIE0 = 0;
      UCSR0B_TXCIE0 = 1;
   }
}
#pragma vector = USART0_TXC_vect
__interrupt void UART2_TXC_ISR(void)
{
   UartType *P2data = &UartAppData2;
   P2data->Flags.Solo.TxStart = 0;
   Run_void(P2data->DisTxPin);
   UCSR0B_TXCIE0 = 0;
}




//UartApp
void Run_void(void (*ptask)())
{
   if (ptask != NULL)
   {
      (*ptask)();
   }
}

UartType UartAppData1;
UartType UartAppData2;
void StartUartSend(UartType *p2data, char *pBuf, uint16 Len)
{
   if (!p2data->Flags.Solo.TxStart)
   {
      p2data->Flags.Solo.TxStart = 1;
      Run_void(p2data->EnTxPin);

      p2data->ToSend  = 0;
      p2data->SentCnt = 0;
      if ((p2data->ToSend + Len) > UART_BUFF_SIZE)
      {
         Len = UART_BUFF_SIZE - p2data->ToSend;
      }
      rt_memcpy(&p2data->TxRxBuf[p2data->ToSend], &pBuf[0], Len); 
      p2data->ToSend  = Len;
      UCSR1A_TXC1 = 0;
      UCSR1B_UDRIE1 = 1;
//    UDR1 = p2data->TxRxBuf[0];
   }
   else
   {
      if ((p2data->ToSend + Len) > UART_BUFF_SIZE)
      {
         Len = UART_BUFF_SIZE - p2data->ToSend;
      }
      rt_memcpy(&p2data->TxRxBuf[p2data->ToSend], pBuf, Len);
      p2data->ToSend += Len;
   }
}
void StartUart2Send(UartType *p2data, char *pBuf, uint16 Len)
{
   if (!p2data->Flags.Solo.TxStart)
   {
      p2data->Flags.Solo.TxStart = 1;
      Run_void(p2data->EnTxPin);

      p2data->ToSend  = 0;
      p2data->SentCnt = 0;
      if ((p2data->ToSend + Len) > UART_BUFF_SIZE)
      {
         Len = UART_BUFF_SIZE - p2data->ToSend;
      }
      rt_memcpy(&p2data->TxRxBuf[p2data->ToSend], &pBuf[0], Len);
      p2data->ToSend  = Len;
      UCSR0A_TXC0 = 0;
      UCSR0B_UDRIE0 = 1;
//    UDR0 = p2data->TxRxBuf[0];
   }
   else
   {
      if ((p2data->ToSend + Len) > UART_BUFF_SIZE)
      {
         Len = UART_BUFF_SIZE - p2data->ToSend;
      }
      rt_memcpy(&p2data->TxRxBuf[p2data->ToSend], pBuf, Len);
      p2data->ToSend += Len;
   }
}

void UartTimeOut(UartType *P2data)
{
   if (P2data->RxTimeout > 0)
   {
      P2data->RxTimeout--;
      if (P2data->RxTimeout == 0 && P2data->RecCnt > 0)
      {
         P2data->Flags.Solo.RecFlame = 1;
      }
   }
   if (P2data->LivingTime > 0)
   {
      P2data->LivingTime--;
   }
}



void rt_memcpy(void *dst, void *scr, uint16 len)
{
   uint8 *dst1 = dst;
   uint8 *scr1 = scr;
   if (scr == NULL)
   {
      return;
   }
   if (dst == NULL)
   {
      return;
   }
   while (len > 0)
   {
      *dst1++ = *scr1++;
      len--;
   }
}















