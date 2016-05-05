
#include "includes.h"

Md_Tcp_Dep MdTcp1;


uint08 ReadBits(uint08 *p2data, uint08 index)
{
   uint08 tmp = index / 8;
   uint08 tmp2 = index % 8;

   if (GetBit(p2data[tmp], tmp2))
   {
      return 1;
   }
   else
   {
      return 0;
   }
}

void WriteBits(uint08 *p2data, uint08 index, uint08 bits)
{
   uint08 tmp = index / 8;
   uint08 tmp2 = index % 8;

   if (bits > 0)
   {
      SetBit(p2data[tmp], tmp2);
   }
   else
   {
      ClrBit(p2data[tmp], tmp2);
   }
}

MdErrEnum LengthCheck(uint16 trgaddr, uint16 length)
{
//   const uint16 ThisLength = 100;
//   if (trgaddr >= ThisLength)
//   {
//      return MD_TRG_ADDR_ERR;
//   }
//   if ((trgaddr + length) >= ThisLength)
//   {
//      return MD_TRG_LEN_ERR;
//   }
//   if (length > 120)
//   {
//      return MD_TRG_LEN_LMT_ERR;
//   }
   return MD_ERR_OK;
}



uint16 PDR(uint16 index)
{
#define _____________DI
//   uint16 tmp = 0;
   if (index == 0)
   {
      return DianXin1.DI.Solo.DI2;
   }
   if (index == 1)
   {
      return DianXin1.DI.Solo.DI5;
   }
   if (index == 2)
   {
      return DianXin1.DI.Solo.DI1;
   }
   if (index == 3)
   {
      return DianXin1.DI.Solo.DI6;
   }
   if (index == 4)
   {
      return DianXin1.DI.Solo.DI8;
   }
   if (index == 5)
   {
      return DianXin1.DI.Solo.DI7;
   }
#define _____________AI
   if (index == 6)
   {
      return DianXin1.AI.Solo.AI3;
//      tmp = DianXin1.AI.Solo.AI3;
//      return tmp;
   }
   if (index == 7)
   {
      return DianXin1.AI.Solo.AI4;
//      tmp = DianXin1.AI.Solo.AI4;
//      return tmp;
   }

   if (index == 8)
   {
      //return DianXin1.AI.Solo.AI1;
   }
   if (index == 9)
   {
     // return DianXin1.AI.Solo.AI2;
   }
#define _____________DO
   if (index == 10)
   {
      return DianXin1.DO.Solo.DO4;
   }
   if (index == 11)
   {
      return DianXin1.DO.Solo.DO3;
   }
   if (index == 12)
   {
      return DianXin1.DO.Solo.DO1;
   }
   if (index == 13)
   {
      return DianXin1.DO.Solo.DO2;
   }
#define _____________AO
   if (index == 14)
   {
      return DianXin1.AO.Solo.AO1;
   }

//   if (index == 20)
//   {
//      return DianXin1.Address;
//   }
   return 0;
} 

uint16 WriteOneData(uint16 Data)
{
   if (Data > 0)
   {
      return 1;
   }
   return 0;
}

void PDW(uint16 index, uint16 Data)
{
#define _____________DO
   if (index == 10)
   {
       DianXin1.DO.Solo.DO4 = WriteOneData(Data);
   }
   if (index == 11)
   {
       DianXin1.DO.Solo.DO3 = WriteOneData(Data);
   }
   if (index == 12)
   {
       DianXin1.DO.Solo.DO1 = WriteOneData(Data);
   }
   if (index == 13)
   {
       DianXin1.DO.Solo.DO2 = WriteOneData(Data);
   }
#define _____________AO
   if (index == 14)
   {
      if (Data > 1000)
      {
	 Data = 1000;
      }
      DianXin1.AO.Solo.AO1 = Data;
   }
}


void StdMdTcpInit(Md_Tcp_Dep *Tcp)
{
   Tcp->LenChkCheck = LengthCheck;
   Tcp->RdData = PDR;
   Tcp->WrData = PDW;
}

void StdMdTcpGetReady(Md_Tcp_Dep *Tcp, UartType *UartDataBlock)
{
   Tcp->RawDataLen = UartDataBlock->RecCnt;
   Tcp->RawData = UartDataBlock->TxRxBuf;
   Tcp->p2trg = UartDataBlock->TxRxBuf;
   Tcp->rePkglen = 0;
}


void StdMdTcpRsp(Md_Tcp_Dep *Tcp, UartType *UartDataBlock)
{
   if (Tcp->rePkglen > 0)
   {
      UartDataBlock->TxTimeout = 100;
      StartUartSend(UartDataBlock, (char *)Tcp->p2trg, Tcp->rePkglen);
   }
   UartDataBlock->Flags.All = 0;
   UartDataBlock->RecCnt = 0;
}

void MdTcbInit()
{
   StdMdTcpInit(&MdTcp1);
   StdMdTcpGetReady(&MdTcp1, &UartAppData1);
}


MdErrEnum MdRet;
void MdPoll(void)
{
   UartType *P2data = &UartAppData1;
   if (P2data->Flags.Solo.RecFlame)
   {
      StdMdTcpGetReady(&MdTcp1, P2data);
      MdRet = MdDataDeal(&MdTcp1);
      StdMdTcpRsp(&MdTcp1, P2data);
      P2data->Flags.Solo.RecFlame = 0;
      P2data->RecCnt = 0;
   }
}



