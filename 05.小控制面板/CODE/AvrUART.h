
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
    void (* EnTxPin)(); //ָ��void���͵ĺ���ָ��
    void (* DisTxPin)();
	uchar TxRxBuf[UART_BUFF_SIZE];//���ͽ������ݻ�����
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






















