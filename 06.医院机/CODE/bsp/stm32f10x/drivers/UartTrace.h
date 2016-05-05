#ifndef __UART_TRACE_H__
#define __UART_TRACE_H__



#define UART_BUFF_SIZE 256
#define UART_SHORT_LEN 8
typedef struct 
{
    void (* EnTxPin)();
    void (* DisTxPin)();
	uchar TxRxBuf[UART_BUFF_SIZE];
	uchar SentCnt;
	uchar ToSend;
	uchar RecCnt;
	uchar RxTimeout;
	uchar MasterAddr;
	uchar MasterPlace;
	uchar MasterNum;
	uchar MasterTimeout;
	uchar PollCnt;
	uint16 LivingTime;
	uint16 MasterTime;
	union
	{
		uchar All;
		struct
		{
			uchar ShortFrame:1;
			uchar DoneShortFrame:1;
			uchar RecFlame:1;
			uchar FastBlink:1;
			uchar TxStart:1;
		} Solo;
	}Flags;
}UartType;



void UART1_TXDIS();
void UART1_TXEN();
void UART2_TXDIS();
void UART2_TXEN();
void UART3_TXDIS();
void UART3_TXEN();
void UART4_TXDIS();
void UART4_TXEN();
void UART5_TXDIS();
void UART5_TXEN();
void StartUartSend(USART_TypeDef *USARTx ,UartType *p2data,char *pBuf,uint16 Len);
void UartPcbsInit();
void TRACEDATA(const char* pszPrompt,PVOID pData,int nSize);
//void TRACE(const char *fmt, ...);


#endif



