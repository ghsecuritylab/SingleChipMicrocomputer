
#ifndef UART_H
#define UART_H

#if 1


#define RS485_ON()  SetBit(PORTD, 2)
#define RS485_OFF() ClrBit(PORTD, 2)


#define UART_BUFF_SIZE 256

typedef struct
{
   uint08 TxRxBuff[UART_BUFF_SIZE];  //发送接收数据缓冲区
   uint08 RxdCount;                  //接收计数
   uint08 TxdCount;                  //发送计数
   uint08 TxdDataLen;                //发送的数据长度
   uint08 RxTimeout;                 //接收到一帧时间
   uint16 MasterTime;
   union 
   {
      uint08 All;
      struct
      {
         uint08 RecFlame:1;       //接收到一帧数据
         uint08 FastBlink:1;      //快闪
         uint08 StartTxdData:1;       //开始发送标志位
         uint08 Nouse:3;
      }Solo;
   }Flags;
}UartType;




void Uart_Init (void);
void StartUartSend(UartType *p2data,char *pBuf,uint16 Len);
void UartTimeOut(UartType *P2data);

extern UartType UartAppData1;



#else


#define UART_BYTE_PER_10mS 9
#define UART_BUFF_SIZE 256
#define UART_SHORT_LEN 8
typedef struct 
{
    void (* EnTxPin)(); //指向void类型的函数指针
    void (* DisTxPin)();
	uchar TxRxBuff[UART_BUFF_SIZE];//发送接收数据缓冲区
	uchar SentCnt;//已经发送的数据计数
	uchar ToSend;//总共要发送的字节数
	uchar RecCnt;//已经接收的数据计数
	uchar RxTimeout;//超时算一帧数据
	uint16 LivingTime;//
	union
	{
		uchar All;
		struct
		{
			uchar ShortFrame:1;//短数据帧
			uchar DoneShortFrame:1;//完成短帧
			uchar RecFlame:1;//接收到一帧数据
			uchar FastBlink:1;//快闪
			uchar TxStart:1;//开始发送标志位
		} Solo;
	}Flags;
}UartType;

void rt_memcpy(void *dst,void *scr,uint16 len);
void Run_void(void (*ptask)());
void Uart_Init (void);
void Uart_AppInit(void);
extern UartType UartAppData1;
void StartUartSend(UartType *p2data,char *pBuf,uint16 Len);
void UART1_TXDIS(void);
void UartTimeOut(UartType *P2data);

#endif

#endif
