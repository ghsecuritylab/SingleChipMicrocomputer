
#ifndef AVRUART_H
#define AVRUART_H

#define REV_EN() {UCSRB_RXCIE = 1;}
#define REV_DIS() {UCSRB_RXCIE = 0;}
#define TXC_EN() {UCSRB_TXCIE = 1;}
#define TXC_DIS() {UCSRB_TXCIE = 0;}


#define UART_BYTE_PER_10mS 9
#define UART_BUFF_SIZE 256
#define UART_SHORT_LEN 8
typedef struct
{
   void (*EnTxPin)();
   void (*DisTxPin)();
   uchar TxRxBuf[UART_BUFF_SIZE];
   uchar SentCnt;
   uchar ToSend;
   uchar RecCnt;
   uchar RxTimeout;
   uchar PollCnt;
   uint16 LivingTime;
   uint16 MasterTime;
   union {
      uchar All;
      struct {
         uchar ShortFrame:1;
         uchar DoneShortFrame:1;
         uchar RecFlame:1;
         uchar FastBlink:1;
         uchar TxStart:1;
      } Solo;
   }Flags;
}UartType;

void rt_memcpy(void *dst, void *scr, uint16 len);
void Run_void(void (*ptask)());
void Uart1_Init(void);
void Uart2_Init(void);
void Uart1_AppInit(void);
void Uart2_AppInit(void);
void StartUart1Send(UartType *p2data, char *pBuf, uint16 Len);
void StartUart2Send(UartType *p2data, char *pBuf, uint16 Len);
void UART1_TXDIS(void);
void UART2_TXDIS(void);
void UartTimeOut(UartType *P2data);

extern UartType UartAppData1;
extern UartType UartAppData2;

#endif






















