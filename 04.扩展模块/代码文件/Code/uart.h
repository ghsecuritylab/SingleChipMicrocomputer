
#ifndef UART_H
#define UART_H



#define UART_BUFF_SIZE 256
#define UART_SHORT_LEN 8


typedef struct
{
   void (*EnTxPin)(); 
   void (*DisTxPin)();
   uint08 TxRxBuf[UART_BUFF_SIZE]; //���ͽ������ݻ�����
   uint08 SentCnt;                 //�Ѿ����͵����ݼ���
   uint08 ToSend;                  //�ܹ�Ҫ���͵��ֽ���
   uint08 RecCnt;                  //�Ѿ����յ����ݼ���
   uint08 RxTimeout;               //���ճ�ʱ
   uint16 LivingTime;
   union 
   {
      uint08 All;
      struct
      {
         uint08 ShortFrame:1;     //������֡
         uint08 DoneShortFrame:1; //��ɶ�֡
         uint08 RecFlame:1;       //���յ�һ֡����
         uint08 FastBlink:1;      //����
         uint08 TxStart:1;        //��ʼ���ͱ�־λ
         uint08 Nouse:3;
      }Solo;
   }Flags;
}UartType;


void Run_void(void (*ptask)());
void Uart_Init (void);
void Uart_AppInit(void);
void StartUartSend(UartType *p2data,char *pBuf,uint16 Len);
void UART1_TXDIS(void);
void UartTimeOut(UartType *P2data);

extern UartType UartAppData1;
extern char *Str;
extern char *StrBuff;
extern uint08 Addr;
extern uint08 Addrflags;

void AppleAddr();
#endif
