#include <stdio.h>
#include "Includes.h"


//MdErrEnum MdRet;
void ClkCfg(void)
{
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_TIM8 | RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD\
                             | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE);
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3 | RCC_APB1Periph_UART4 | RCC_APB1Periph_UART5\
                             | RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5 | RCC_APB1Periph_TIM6, ENABLE);
}

void ComIOcfg(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   /*串口1，引脚功能*/
//    /* Configure USART1 Tx (PA.09) as alternate function push-pull */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//    /* Configure USART1 Rx (PA.10) as input floating */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

   /*串口2，引脚功能*/
   /* Configure USART2 Tx (PA.02) as alternate function push-pull */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   /* Configure USART2 Rx (PA.03) as input floating */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   /*串口3，引脚功能*/
   /* Configure USART3 Tx (PB.10) as alternate function push-pull */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   /* Configure USART3 Rx (PB.11) as input floating */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   /*串口4，引脚功能*/
   /* Configure USART3 Tx (PB.10) as alternate function push-pull */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   /* Configure USART3 Rx (PB.11) as input floating */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
   
   
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_Init(GPIOA, &GPIO_InitStructure);

   /*串口5，引脚功能*/
   /* Configure UART5 Tx (PC.12) as alternate function push-pull */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   /* Configure UART5 Rx (PD.02) as input floating */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void SDIOcfg(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   /*SDIO 管脚配置*/
   /* Configure PC.08, PC.09, PC.10, PC.11, PC.12 pin: D0, D1, D2, D3, CLK pin */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
   /* Configure PD.02 CMD line */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
   //power line
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}



void OutPutIOcfg(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;

   //GPIO REMAP
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD, ENABLE);
   // 1、打开复用时钟：
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
   // 2、调用重映射函数：
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //关闭jtag , 开启swd



   //GPIO A:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   //GPIO B:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 |\
      GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOB, &GPIO_InitStructure);


   //GPIO C:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   //GPIO D:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |\
      GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |\
      GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOD, &GPIO_InitStructure);

   //GPIO E:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 |\
      GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_15;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOE, &GPIO_InitStructure);


   //GPIO F:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 |\
      GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 |\
      GPIO_Pin_14 | GPIO_Pin_15;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOF, &GPIO_InitStructure);



   //GPIO G:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOG, &GPIO_InitStructure);
}

void InputIOcfg()
{

   GPIO_InitTypeDef GPIO_InitStructure;
   //GPIO A:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   //GPIO B:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   //GPIO F:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_Init(GPIOF, &GPIO_InitStructure);


}
void AdcIOcfg()
{

   GPIO_InitTypeDef GPIO_InitStructure;

   //GPIO A:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   //GPIO B:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   //GPIO C:
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
}








void USART_Configuration(USART_TypeDef *USARTx, uint32_t baud, uint16_t stopbit, uint16_t  parity)
{
   USART_InitTypeDef USART_InitStructure;
   USART_ClockInitTypeDef  USART_ClockInitStructure;
   USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
   USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
   USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
   USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
   /* Configure the USARTx synchronous paramters */
   USART_ClockInit(USARTx, &USART_ClockInitStructure);
   USART_InitStructure.USART_BaudRate = baud; //115200;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = stopbit;//USART_StopBits_1;
   USART_InitStructure.USART_Parity = parity;//USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   /* Configure USARTx basic and asynchronous paramters */
   USART_Init(USARTx, &USART_InitStructure);
   /* Enable USARTx Receive and Transmit interrupts */
   USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
   USART_ITConfig(USARTx, USART_IT_TC, DISABLE);
   USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
   /* Enable USARTx */
   USART_Cmd(USARTx, ENABLE);
}


void UartTimeOut(UartType *P2data)
{
   if (P2data->RxTimeout > 0)
   {
      P2data->RxTimeout--;
      if (P2data->RxTimeout == 0 && P2data->RecCnt > 0)
      {
         P2data->Flags.Solo.RecFlame = 1;
      }
   }
   if (P2data->MasterTimeout > 0)
   {
      P2data->MasterTimeout--;
   }


   if (P2data->MasterTime > 0)
   {
      P2data->MasterTime--;
   }

   
}


//10进制最多9位
//16进制最多8位
INT32 Asc2Int(char *TrgStr)
{
   INT32 RET = 0;
   UINT8 tmp = 0;
   UINT8 NumCnt = 0;
   UINT8 DealCnt = 0;
   UINT8 Nagative = 0;
   const UINT32 Decbuff[9] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };
   const UINT32 HexBuff[9] = { (0x01 << 0), (0x01 << 4), (0x01 << 8), (0x01 << 12), (0x01 << 16), (0x01 << 20), (0x01 << 24), (0x01 << 28), 0 };
   UINT8 Nums[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   //1,判断符号
   if (TrgStr[0] == '-')
   {
      DealCnt++;
      Nagative = 1;
   }
   //2,10进制或16进制
   if (TrgStr[DealCnt] == '0')
   {
      if (TrgStr[DealCnt + 1] == 'x' || TrgStr[DealCnt + 1] == 'X')
      {
         DealCnt++;
         for (tmp = 0; tmp < 8; tmp++)
         {
            DealCnt++;
            if (TrgStr[DealCnt] >= '0' && TrgStr[DealCnt] <= '9')
            {
               NumCnt++;
               Nums[tmp] = TrgStr[DealCnt] - '0';
            }
            else if (TrgStr[DealCnt] >= 'A' && TrgStr[DealCnt] <= 'F')
            {
               NumCnt++;
               Nums[tmp] = TrgStr[DealCnt] - 'A' + 10;
            }
            else if (TrgStr[DealCnt] >= 'a' && TrgStr[DealCnt] <= 'f')
            {
               NumCnt++;
               Nums[tmp] = TrgStr[DealCnt] - 'a' + 10;
            }
            else
            {
               break;
            }
         }
         //根据NumCnt确定位数和绝对值
         tmp = 0;
         while (NumCnt > 0)
         {
            NumCnt--;
            RET += HexBuff[tmp++] * Nums[NumCnt];
         }
         //再次判断符号
//            if(Nums[0]>=8)
//            {
//                Nagative ^=1;
//            }
//判断符号
         if (Nagative > 0)
         {
            RET = (-1 * RET);
         }
         return RET;
      }
   }

   //10进制处理
   {
      for (tmp = 0; tmp < 8; tmp++)
      {
         if (TrgStr[DealCnt] >= '0' && TrgStr[DealCnt] <= '9')
         {
            NumCnt++;
            Nums[tmp] = TrgStr[DealCnt] - '0';
         }
         else
         {
            break;
         }
         DealCnt++;
      }
      //根据NumCnt确定位数和绝对值
      tmp = 0;
      while (NumCnt > 0)
      {
         NumCnt--;
         RET += Decbuff[tmp++] * Nums[NumCnt];
      }
      //判断符号
      if (Nagative > 0)
      {
         RET = (-1 * RET);
      }
      return RET;
   }
}

uchar SpiltArgs(uchar *p2data, uint16 dlen, char *p2str[10])
{
   uchar tmp;
   uchar argcnt = 0;
   for (tmp = 0; tmp < dlen; tmp++)
   {
      if (p2data[tmp] == 0x20) //space key
      {
         p2data[tmp] = 0; //EOF
      }
      if (p2data[tmp] == 0x0D)
      {
         if (p2data[tmp + 1] == 0x0A)
         {
            p2data[tmp + 0] = 0; //EOF
            p2data[tmp + 1] = 0; //EOF
         }
      }
   }
   for (tmp = 0; tmp < dlen; tmp++)
   {
      if (p2data[tmp] != 0x00) //Start of a string
      {
         p2str[argcnt] = (char *)&p2data[tmp];
         for (tmp = tmp + 1; tmp < dlen; tmp++)
         {
            if (p2data[tmp] == 0x00) //End of a string
            {
               tmp = tmp - 1;
               break;
            }
         }
         argcnt = argcnt + 1;
      }
      if (argcnt >= 9)
      {
         break;
      }
   }
   p2data[dlen] = 0;
   return argcnt;
}


//void ShellProc2(void)
//{
//    UartType *P2data = UartAppData2;
//    static char *gbl_pp2char[10];
//    uchar args = 0;
//    while (1)
//    {
//        OSTimeDlyHMSM(0, 0, 0, 5);
//
//        if (P2data->Flags.Solo.RecFlame)
//        {
//            static uchar *p2udata ;
//             p2udata = (uchar *)HeapMemRequire(UART_BUFF_SIZE) ;
//            if(p2udata!=NULL)
//            {
//                memcpy(p2udata,P2data->TxRxBuf,UART_BUFF_SIZE);
//                args=SpiltArgs(p2udata,P2data->RecCnt,gbl_pp2char);
//                MasterFunctions(args,gbl_pp2char);
//                P2data->Flags.All = 0;
//                P2data->RecCnt = 0;
//                HeapMemFree(p2udata);
//            }
//            p2udata = NULL;
//        }
//    }
//}



void ShellProc1(void)
{
   static char *gbl_pp2char[10];
   static uchar *p2udata;
   uchar args = 0;
   UartType *P2data = &UartAppData1;
   if (P2data->Flags.Solo.RecFlame)
   {
      p2udata = (uchar *)rt_malloc(UART_BUFF_SIZE);
      if (p2udata != NULL)
      {
         memcpy(p2udata, P2data->TxRxBuf, UART_BUFF_SIZE);
         args = SpiltArgs(p2udata, P2data->RecCnt, gbl_pp2char);
         MasterFunctions(args, gbl_pp2char);
         P2data->Flags.All = 0;
         /*Echo back*/ /*for test*/
//          StartUartSend(USART1,P2data,(char *)P2data->TxRxBuf,P2data->RecCnt);
         P2data->RecCnt = 0;
         rt_free(p2udata);
      }
      p2udata = NULL;

   }
}

void ShellProc2(void)
{
   UartType *P2data = &UartAppData2;
   if (P2data->Flags.Solo.RecFlame)
   {
      StdMdTcpGetReady(&MdTcp1, P2data);
      MdRet = MdDataDeal(&MdTcp1);
      StdMdTcpRsp(&MdTcp1, P2data);
   }
//   if (YYJ1.OP.COM2poll != 0)
//   {
//      MdMasterPoll2();
//   }
}




void ShellProc3(void)
{
   UartType *P2data = &UartAppData3;
   if (P2data->Flags.Solo.RecFlame)
   {
      PolMdTcpGetReady(&MdTcp2, P2data);
      MdRet = MdDataDeal(&MdTcp2);
      PolMdTcpRsp(&MdTcp2, P2data);
   }
   if (YYJ1.OP.SysPar.SaveBit.Solo.MCU1_PLC0 != 0)
   {
      MdMasterPoll();
   }
}

void ShellProc4(void)
{
   UartType *P2data = &UartAppData4;
   if (YYJ1.OP.COM4Shield == 0)
   {
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOC, &GPIO_InitStructure);

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOC, &GPIO_InitStructure);

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
   }

   if (P2data->Flags.Solo.RecFlame)
   {
      StdMdTcpGetReady(&MdTcp4, P2data);
      MdRet = MdDataDeal(&MdTcp4);
      COM4MdTcpRsp(&MdTcp4, P2data);
   }
}
void ShellProc5(void)
{
//   static char *gbl_pp2char[10];
//   static uchar *p2udata;
//   uchar args = 0;
//   UartType *P2data = &UartAppData5;
//   if (P2data->Flags.Solo.RecFlame)
//   {
//      p2udata = (uchar *)rt_malloc(UART_BUFF_SIZE);
//      if (p2udata != NULL)
//      {
//         memcpy(p2udata, P2data->TxRxBuf, UART_BUFF_SIZE);
//         args = SpiltArgs(p2udata, P2data->RecCnt, gbl_pp2char);
//         MasterFunctions(args, gbl_pp2char);
//         P2data->Flags.All = 0;
//         /*Echo back*/ /*for test*/
//         StartUartSend(UART5, P2data, (char *)P2data->TxRxBuf, P2data->RecCnt + 10);
//         P2data->RecCnt = 0;
//         rt_free(p2udata);
//      }
//      p2udata = NULL;
//
//   }
}









