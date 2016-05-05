#include "Includes.h"





void TIM3_IRQHandler(void)
{
    rt_interrupt_enter();
    if ( TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET )                     //判断发生中断的信息
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);                                  // 清除中断标志
        ScanLed();
    }
    rt_interrupt_leave();  
}











void USART2_IRQHandler(void)
{


    //用户程序..
    UartType *P2data = &UartAppData2;

    /* enter interrupt */
    rt_interrupt_enter();
    if ( USART_GetITStatus(USART2, USART_IT_RXNE) != RESET )
    {
        UCHAR ucChar;    
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        ucChar = USART_ReceiveData(USART2);

        if ( !P2data->Flags.Solo.RecFlame )
        {
            P2data->RxTimeout = __25ms__;
            if ( P2data->RecCnt < (UART_BUFF_SIZE-1) )
            {
                P2data->TxRxBuf[P2data->RecCnt] = ucChar;
                P2data->RecCnt++;
                if ( P2data->RecCnt == 8 )
                {
                    P2data->Flags.Solo.ShortFrame =1;
                }
                if ( P2data->RecCnt == UART_BUFF_SIZE-1 )
                {
                    P2data->Flags.Solo.RecFlame =1;
                }
                //if (P2data->RecCnt == UART_SHORT_LEN)
                //{
                //    P2data->Flags->Solo->ShortFrame =1;
                //}
            }
        }

    }
    else if ( USART_GetITStatus(USART2,USART_IT_TXE) )
    {
        USART_ClearITPendingBit(USART2,USART_IT_TXE);
        USART_ClearFlag(USART2,USART_FLAG_TC);
        if ( P2data->SentCnt <  P2data->ToSend )
        {
            USART_SendData(USART2,P2data->TxRxBuf[P2data->SentCnt++]);        
        }
        else
        {
            USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
            USART_ITConfig(USART2, USART_IT_TC,  ENABLE);
        }
    }
    else if ( USART_GetITStatus(USART2,USART_IT_TC) )
    {
        P2data->Flags.Solo.TxStart = 0;
        Run_void(P2data->DisTxPin);
        USART_ITConfig(USART2, USART_IT_TC,  DISABLE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}


void USART3_IRQHandler(void)
{

    //用户程序..
    UartType *P2data = &UartAppData3;

    /* enter interrupt */
    rt_interrupt_enter();
    if ( USART_GetITStatus(USART3, USART_IT_RXNE) != RESET )
    {
        UCHAR ucChar;    
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
        ucChar = USART_ReceiveData(USART3);

        if ( !P2data->Flags.Solo.RecFlame )
        {
            P2data->RxTimeout = __25ms__;
            if ( P2data->RecCnt < (UART_BUFF_SIZE-1) )
            {
                P2data->TxRxBuf[P2data->RecCnt] = ucChar;
                P2data->RecCnt++;
                if ( P2data->RecCnt == 8 )
                {
                    P2data->Flags.Solo.ShortFrame =1;
                }
                if ( P2data->RecCnt == UART_BUFF_SIZE-1 )
                {
                    P2data->Flags.Solo.RecFlame =1;
                }
                //if (P2data->RecCnt == UART_SHORT_LEN)
                //{
                //    P2data->Flags->Solo->ShortFrame =1;
                //}
            }
        }

    }
    else if ( USART_GetITStatus(USART3,USART_IT_TXE) )
    {
        USART_ClearITPendingBit(USART3,USART_IT_TXE);
        USART_ClearFlag(USART3,USART_FLAG_TC);
        if ( P2data->SentCnt <  P2data->ToSend )
        {
            USART_SendData(USART3,P2data->TxRxBuf[P2data->SentCnt++]);        
        }
        else
        {
            USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
            USART_ITConfig(USART3, USART_IT_TC,  ENABLE);
        }
    }
    else if ( USART_GetITStatus(USART3,USART_IT_TC) )
    {
        P2data->Flags.Solo.TxStart = 0;
        Run_void(P2data->DisTxPin);
        USART_ITConfig(USART3, USART_IT_TC,  DISABLE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}


void UART4_IRQHandler(void)
{

    //用户程序..
    UartType *P2data = &UartAppData4;
    /* enter interrupt */
    rt_interrupt_enter();
    if ( USART_GetITStatus(UART4, USART_IT_RXNE) != RESET )
    {
        UCHAR ucChar;    
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);
        ucChar = USART_ReceiveData(UART4);

        if ( !P2data->Flags.Solo.RecFlame )
        {
            P2data->RxTimeout = __25ms__;
            if ( P2data->RecCnt < (UART_BUFF_SIZE-1) )
            {
                P2data->TxRxBuf[P2data->RecCnt] = ucChar;
                P2data->RecCnt++;
                if ( P2data->RecCnt == 8 )
                {
                    P2data->Flags.Solo.ShortFrame =1;
                }
                if ( P2data->RecCnt == UART_BUFF_SIZE-1 )
                {
                    P2data->Flags.Solo.RecFlame =1;
                }
                //if (P2data->RecCnt == UART_SHORT_LEN)
                //{
                //    P2data->Flags->Solo->ShortFrame =1;
                //}
            }
        }

    }
    else if ( USART_GetITStatus(UART4,USART_IT_TXE) )
    {
        USART_ClearITPendingBit(UART4,USART_IT_TXE);
        USART_ClearFlag(UART4,USART_FLAG_TC);
        if ( P2data->SentCnt <  P2data->ToSend )
        {
            USART_SendData(UART4,P2data->TxRxBuf[P2data->SentCnt++]);        
        }
        else
        {
            USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
            USART_ITConfig(UART4, USART_IT_TC,  ENABLE);
        }
    }
    else if ( USART_GetITStatus(UART4,USART_IT_TC) )
    {
        P2data->Flags.Solo.TxStart = 0;
        Run_void(P2data->DisTxPin);
        USART_ITConfig(UART4, USART_IT_TC,  DISABLE);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}


#define ________________________NOCAN____________________________________
void UART5_IRQHandler(void)
{

    //用户程序..
    UartType *P2data = &UartAppData5;
    /* enter interrupt */
    rt_interrupt_enter();
    if ( USART_GetITStatus(UART5, USART_IT_RXNE) != RESET )
    {
        UCHAR ucChar;    
        USART_ClearITPendingBit(UART5, USART_IT_RXNE);
        ucChar = USART_ReceiveData(UART5);

        if ( !P2data->Flags.Solo.RecFlame )
        {
            P2data->RxTimeout = __25ms__;
            if ( P2data->RecCnt < (UART_BUFF_SIZE-1) )
            {
                P2data->TxRxBuf[P2data->RecCnt] = ucChar;
                P2data->RecCnt++;
                if ( P2data->RecCnt == 8 )
                {
                    P2data->Flags.Solo.ShortFrame =1;
                }
                if ( P2data->RecCnt == UART_BUFF_SIZE-1 )
                {
                    P2data->Flags.Solo.RecFlame =1;
                }
                //if (P2data->RecCnt == UART_SHORT_LEN)
                //{
                //    P2data->Flags->Solo->ShortFrame =1;
                //}
            }
        }

    }
    else if ( USART_GetITStatus(UART5,USART_IT_TXE) )
    {
        USART_ClearITPendingBit(UART5,USART_IT_TXE);
        USART_ClearFlag(UART5,USART_FLAG_TC);
        if ( P2data->SentCnt <  P2data->ToSend )
        {
            USART_SendData(UART5,P2data->TxRxBuf[P2data->SentCnt++]);        
        }
        else
        {
            USART_ITConfig(UART5, USART_IT_TXE, DISABLE);
            USART_ITConfig(UART5, USART_IT_TC,  ENABLE);
        }
    }
    else if ( USART_GetITStatus(UART5,USART_IT_TC) )
    {
        P2data->Flags.Solo.TxStart = 0;
        Run_void(P2data->DisTxPin);
        USART_ITConfig(UART5, USART_IT_TC,  DISABLE);
    }
    /* leave interrupt */
   rt_interrupt_leave();
}











