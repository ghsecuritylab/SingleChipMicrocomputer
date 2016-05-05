
#include "includes.h"
#include <rtthread.h>

#ifndef NO_TRACE
#define  TRACE rt_kprintf 




uint16 Gbl_Dbg_Lvl=0;
char szBuffer[256];

void UART1_TXEN()
{
    _nop_();
}
void UART1_TXDIS()
{
    _nop_();
}

void UART2_TXEN()
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void UART2_TXDIS()
{
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void UART3_TXEN()
{
    GPIO_ResetBits(GPIOE,GPIO_Pin_15);
}
void UART3_TXDIS()
{
    GPIO_SetBits(GPIOE,GPIO_Pin_15);
}

void UART4_TXEN()
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_15);
    _nop_();
}
void UART4_TXDIS()
{
    GPIO_SetBits(GPIOA,GPIO_Pin_15);
    _nop_();
}

void UART5_TXEN()
{
    _nop_();
}
void UART5_TXDIS()
{
    _nop_();
}


void UartPcbsInit()
{
      UartAppData2.EnTxPin=UART2_TXEN;
      UartAppData2.DisTxPin=UART2_TXDIS;
      UartAppData3.EnTxPin=UART3_TXEN;
      UartAppData3.DisTxPin=UART3_TXDIS;
      UartAppData4.EnTxPin=UART4_TXEN;
      UartAppData4.DisTxPin=UART4_TXDIS;
      UartAppData5.EnTxPin=UART5_TXEN;
      UartAppData5.DisTxPin=UART5_TXDIS;
}





void StartUartSend(USART_TypeDef *USARTx ,UartType *p2data,char *pBuf,uint16 Len)
{
    if(!p2data->Flags.Solo.TxStart)
    {
        p2data->Flags.Solo.TxStart = 1;
        Run_void(p2data->EnTxPin);

        p2data->ToSend  = 0;
        p2data->SentCnt = 0;
        if((p2data->ToSend+Len) > UART_BUFF_SIZE)
        {
            Len = UART_BUFF_SIZE-p2data->ToSend;
        }
        rt_memcpy(&p2data->TxRxBuf[p2data->ToSend],&pBuf[0],Len);
        p2data->ToSend  = Len;
        //USART_SendData(USARTx, *pBuf);  
        USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);          
    }
    else
    {
        if((p2data->ToSend+Len) > UART_BUFF_SIZE)
        {
            Len = UART_BUFF_SIZE-p2data->ToSend;
        }
        rt_memcpy(&p2data->TxRxBuf[p2data->ToSend],pBuf,Len);  
        p2data->ToSend += Len;
    }
}

//格式化打印输出函数
//void printf(const char * fmt,...)
//int __std_printf(int dbgLevel, const char * format,...)
//{
//    int nLen;
//    va_list args;//char* args
//
//    if(dbgLevel<Gbl_Dbg_Lvl)
//    {
//        return FALSE;
//    }
//
//
//    va_start(args, format);
//    nLen = vsprintf(szBuffer, format, args);
//    va_end(args);
//    StartUartSend(CONSOLE_UART,&CONSOLE_UART_TCB,szBuffer,nLen);
//
//    return TRUE;
//}


#define ___TRACE___
//void TRACE(const char *fmt, ...)
//{
//    int nLen;
//    va_list args;
//    va_start(args, fmt);
//    nLen = vsprintf(szBuffer, fmt, args);
//    va_end(args);
//    StartUartSend(CONSOLE_UART,&CONSOLE_UART_TCB,szBuffer,nLen);
//}



void TRACEDATA(const char* pszPrompt,PVOID pData,int nSize)//串口查看数据显示
{
    PBYTE p;
    int i;

    TRACE("%s (%d B):\r\n",pszPrompt,nSize);//%s  按字符串的方式输出  回车换行
    //例子: TRACEDATA("Input165 is",InputStateRec,6);
    //Input165 is (6 B):
    for (i=0,p=(PBYTE)(pData);i<nSize;i+=16,p+=16)
    {
        if (i+16<=nSize)
        {
            TRACE("\t%04d: 0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X\r\n",
                  i,p[0],p[1],p[2],p[3], p[4],p[5],p[6],p[7], p[8],p[9],p[10],p[11], p[12],p[13],p[14],p[15]);
        } 
        //0000: 0x00,0x00,0x00,0x00,0x00,0x00,
        else
        {
            int j;

            TRACE("\t%04d: ",i);
            for (j=0;j<nSize-i;j++)
            {
                TRACE("0x%02X,",p[j]);
            }
            TRACE("\r\n");
        }
    }
}

#endif // NO_TRACE



