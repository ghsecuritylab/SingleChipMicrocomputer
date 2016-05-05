

#include "includes.h"

#define SYS_OSC 8000000
#define Boad 9600
#define __5ms__ 5

UartType UartAppData1;


void UART1_TXEN(void)
{
   SetBit(PORTD, 2);
}

void UART1_TXDIS(void)
{
   ClrBit(PORTD, 2);
}

void Run_void(void (*ptask)())
{
   if (ptask != NULL)
   {
      (*ptask)();
   }
}

void Uart_AppInit(void)
{
   UartAppData1.EnTxPin = UART1_TXEN;
   UartAppData1.DisTxPin = UART1_TXDIS;
   UART1_TXDIS();
}

void Uart_Init(void)
{
   UCSRA = 0x01; //�첽����ģʽ
   UCSRB = 0xB8; //�����ͽ����жϺ�ʹ��
   UCSRC = 0x86; //8λ����
   UBRRL = (SYS_OSC / Boad / 16 - 1) % 256;
   UBRRH = (SYS_OSC / Boad / 16 - 1) / 256;
}
 
/*���ݽ��ս����ж�����*/
#pragma vector = USART_RXC_vect
__interrupt void UART0_RX_ISR(void)
{
   uint08 ucChar;
   UartType *P2data = &UartAppData1;
   ucChar = UDR;//������
   P2data->LivingTime = 2000;
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


/*���ݼĴ������ж�����*/
#pragma vector = USART_UDRE_vect
__interrupt void UART_TX_ISR(void)
{
   UartType *P2data = &UartAppData1;
   if (P2data->SentCnt <  P2data->ToSend)
   {
      UCSRA_TXC = 0; //Send data before cleared
      UDR = P2data->TxRxBuf[P2data->SentCnt];
      P2data->SentCnt++;
   }
   else
   {
      UCSRB_UDRIE = 0;
      UCSRB_TXCIE = 1; //���ͽ����ж�ʹ��
   }
}

/*���ݷ��ͽ����ж�����*/
#pragma vector = USART_TXC_vect
__interrupt void UART_TXC_ISR(void)
{
   UartType *P2data = &UartAppData1;
   P2data->Flags.Solo.TxStart = 0;
   Run_void(P2data->DisTxPin);
   UCSRB_TXCIE = 0;
}

void StartUartSend(UartType *p2data, char *pBuf, uint16 Len)
{
   if (!p2data->Flags.Solo.TxStart) //��ʼ��������
   {
      p2data->Flags.Solo.TxStart = 1;
      Run_void(p2data->EnTxPin);

      p2data->ToSend  = 0;
      p2data->SentCnt = 0;
      if ((p2data->ToSend + Len) > UART_BUFF_SIZE)
      {
         Len = UART_BUFF_SIZE - p2data->ToSend; //�������
      }
      memcpy(&p2data->TxRxBuf[p2data->ToSend], &pBuf[0], Len); //memcpy�������� ����Դ�ڴ�pBuf������Ŀ���ڴ�TxRxBuf
      p2data->ToSend  = Len;
      UCSRA_TXC = 0;
      UCSRB_UDRIE = 1;
      UDR = p2data->TxRxBuf[0];
   }
   else
   {
      if ((p2data->ToSend + Len) > UART_BUFF_SIZE)
      {
         Len = UART_BUFF_SIZE - p2data->ToSend;
      }
      memcpy(&p2data->TxRxBuf[p2data->ToSend], pBuf, Len);
      p2data->ToSend += Len;
   }
}

void UartTimeOut(UartType *P2data)
{
   if (Timer1.Flags.Solo._1ms == 0)
   {
      return;
   }

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




