
#ifndef UART_H
#define UART_H

#if 1


#define RS485_ON()  SetBit(PORTD, 2)
#define RS485_OFF() ClrBit(PORTD, 2)


#define UART_BUFF_SIZE 256

typedef struct
{
   uint08 TxRxBuff[UART_BUFF_SIZE];  //���ͽ������ݻ�����
   uint08 RxdCount;                  //���ռ���
   uint08 TxdCount;                  //���ͼ���
   uint08 TxdDataLen;                //���͵����ݳ���
   uint08 RxTimeout;                 //���յ�һ֡ʱ��
   uint16 MasterTime;
   union 
   {
      uint08 All;
      struct
      {
         uint08 RecFlame:1;       //���յ�һ֡����
         uint08 FastBlink:1;      //����
         uint08 StartTxdData:1;       //��ʼ���ͱ�־λ
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
    void (* EnTxPin)(); //ָ��void���͵ĺ���ָ��
    void (* DisTxPin)();
	uchar TxRxBuff[UART_BUFF_SIZE];//���ͽ������ݻ�����
	uchar SentCnt;//�Ѿ����͵����ݼ���
	uchar ToSend;//�ܹ�Ҫ���͵��ֽ���
	uchar RecCnt;//�Ѿ����յ����ݼ���
	uchar RxTimeout;//��ʱ��һ֡����
	uint16 LivingTime;//
	union
	{
		uchar All;
		struct
		{
			uchar ShortFrame:1;//������֡
			uchar DoneShortFrame:1;//��ɶ�֡
			uchar RecFlame:1;//���յ�һ֡����
			uchar FastBlink:1;//����
			uchar TxStart:1;//��ʼ���ͱ�־λ
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
