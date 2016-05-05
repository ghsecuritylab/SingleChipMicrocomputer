
#ifndef UART_H
#define UART_H



#define UART_BUFF_SIZE 256
#define UART_SHORT_LEN 8


typedef struct
{
   void (*EnTxPin)(); 
   void (*DisTxPin)();
   uint08 TxRxBuf[UART_BUFF_SIZE]; //发送接收数据缓冲区
   uint08 SentCnt;                 //已经发送的数据计数
   uint08 ToSend;                  //总共要发送的字节数
   uint08 RecCnt;                  //已经接收的数据计数
   uint08 RxTimeout;               //接收超时
   uint16 LivingTime;
   union 
   {
      uint08 All;
      struct
      {
         uint08 ShortFrame:1;     //短数据帧
         uint08 DoneShortFrame:1; //完成短帧
         uint08 RecFlame:1;       //接收到一帧数据
         uint08 FastBlink:1;      //快闪
         uint08 TxStart:1;        //开始发送标志位
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
