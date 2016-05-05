

#include "includes.h"

#define SYS_OSC 8000000
#define Boad 9600
#define __5ms__ 5
#define EnableUartSend()   {UCSRB_TXEN = 1;UCSRB_TXCIE = 1;}
#define DisallowUartSend() {UCSRB_TXEN = 0;UCSRB_TXCIE = 0;}




#if 1
UartType UartAppData1;


void Uart_Init(void)
{
   UCSRA = 0x01;
   UCSRB = 0xB8;
   UCSRC = 0x86;
   UBRRL = (SYS_OSC / Boad / 16 - 1) % 256;
   UBRRH = (SYS_OSC / Boad / 16 - 1) / 256;
}

#pragma vector = USART_RXC_vect
__interrupt void UART0_RX_ISR(void)
{
   UartType *P2data;
   uint08 RxdBuff;
   RxdBuff = UDR;
   P2data = &UartAppData1;
   P2data->RxTimeout = __5ms__;
   P2data->TxRxBuff[P2data->RxdCount] = RxdBuff;
   P2data->RxdCount++;
   if (P2data->RxdCount == UART_BUFF_SIZE - 1)
   {
      P2data->Flags.Solo.RecFlame = 1;
   }
}

#pragma vector = USART_UDRE_vect
__interrupt void UART_TX_ISR(void)
{
   UartType *P2data = &UartAppData1;
   if (P2data->TxdCount <  P2data->TxdDataLen)
   {
      UDR = P2data->TxRxBuff[P2data->TxdCount];
      P2data->TxdCount++;
   }
   else
   {
      UCSRB_UDRIE = 0;
      UCSRB_TXCIE = 1;//使能发送中断
   }
}


#pragma vector = USART_TXC_vect
__interrupt void UART_TXC_ISR(void)
{
   UartType *P2data = &UartAppData1;
   P2data->Flags.Solo.StartTxdData = 0;
   RS485_OFF();
   UCSRB_TXCIE = 0;
}


void StartUartSend(UartType *p2data, char *pBuf, uint16 Len)
{
   if (!p2data->Flags.Solo.StartTxdData)
   {
      p2data->Flags.Solo.StartTxdData = 1;
      RS485_ON();
      p2data->TxdCount = 0;
      p2data->TxdDataLen  = 0;
      memcpy(p2data->TxRxBuff, pBuf, Len);
      p2data->TxdDataLen  = Len;
      UCSRB_UDRIE = 1;//使能UDRE中断
   }
}

void UartTimeOut(UartType *P2data)
{
   if (P2data->RxTimeout > 0)
   {
      P2data->RxTimeout--;
      if (P2data->RxTimeout == 0 && P2data->RxdCount > 0)
      {
         P2data->Flags.Solo.RecFlame = 1;
      }
   }
}


#else




#include "includes.h"



UartType UartAppData1;


void UART1_TXEN(void)
{
   SetBit(PORTD, 2);
}
void UART1_TXDIS(void)
{
   ClrBit(PORTD, 2);
}

void Uart_Init(void)
{
   UCSRA = 0x01; //异步正常模式
   UCSRB = 0xB8; //允许发送接受中断和使能
   UCSRC = 0x86; //8位数据
   UBRRL = (SYS_OSC / 9600 / 16 - 1) % 256;
   UBRRH = (SYS_OSC / 9600 / 16 - 1) / 256;
}

void Uart_AppInit(void)
{
   UartAppData1.EnTxPin = UART1_TXEN;
   UartAppData1.DisTxPin = UART1_TXDIS;
   UART1_TXDIS();
}



#pragma vector = USART_RXC_vect
__interrupt void UART0_RX_ISR(void) //串口接收中断
{
   uchar ucChar;
   UartType *P2data = &UartAppData1;
   ucChar = UDR; //缓冲区
   P2data->LivingTime = 2000;
   if (!P2data->Flags.Solo.RecFlame)
   {
      P2data->RxTimeout = __5ms__;
      if (P2data->RecCnt < (UART_BUFF_SIZE - 1))
      {
         P2data->TxRxBuff[P2data->RecCnt] = ucChar;
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

#pragma vector = USART_UDRE_vect
__interrupt void UART_TX_ISR(void) //数据寄存器
{
   UartType *P2data = &UartAppData1;
   if (P2data->SentCnt <  P2data->ToSend) //发送的数据 <
   {
      UCSRA_TXC = 0; //产生发送结束中断
      UDR = P2data->TxRxBuff[P2data->SentCnt];
      P2data->SentCnt++;
   }
   else
   {
      UCSRB_UDRIE = 0; //置位后使能UDRE中断
      UCSRB_TXCIE = 1; //发送结束中断使能
   }
}
#pragma vector = USART_TXC_vect
__interrupt void UART_TXC_ISR(void) 
{
   UartType *P2data = &UartAppData1;
   P2data->Flags.Solo.TxStart = 0;
   Run_void(P2data->DisTxPin); //485接收
   UCSRB_TXCIE = 0; //TXCIE置位后使能TXD中断
}


//UartApp
void Run_void(void (*ptask)())
{
   if (ptask != NULL)
   {
      (*ptask)();
   }
}

void StartUartSend(UartType *p2data, char *pBuf, uint16 Len)
{
   if (!p2data->Flags.Solo.TxStart) //开始发送数据
   {
      p2data->Flags.Solo.TxStart = 1;
      Run_void(p2data->EnTxPin); //

      p2data->ToSend  = 0;
      p2data->SentCnt = 0;
      if ((p2data->ToSend + Len) > UART_BUFF_SIZE)
      {
         Len = UART_BUFF_SIZE - p2data->ToSend;
      }
      rt_memcpy(&p2data->TxRxBuff[p2data->ToSend], &pBuf[0], Len);
      p2data->ToSend  = Len;
      UCSRA_TXC = 0;
      UCSRB_UDRIE = 1;
      UDR = p2data->TxRxBuff[0];
   }
   else
   {
      if ((p2data->ToSend + Len) > UART_BUFF_SIZE)
      {
         Len = UART_BUFF_SIZE - p2data->ToSend;
      }
      rt_memcpy(&p2data->TxRxBuff[p2data->ToSend], pBuf, Len);
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
   uchar *dst1 = dst;
   uchar *scr1 = scr;
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


#endif













