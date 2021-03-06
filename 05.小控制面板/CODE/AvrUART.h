
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
    void (* EnTxPin)(); //指向void类型的函数指针
    void (* DisTxPin)();
	uchar TxRxBuf[UART_BUFF_SIZE];//发送接收数据缓冲区
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






















