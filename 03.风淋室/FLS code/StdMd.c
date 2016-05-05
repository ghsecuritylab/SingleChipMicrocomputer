
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
   const uint16 ThisLength = 50;
   if (trgaddr >= ThisLength)
   {
      return MD_TRG_ADDR_ERR;
   }
   if ((trgaddr + length) >= ThisLength)
   {
      return MD_TRG_LEN_ERR;
   }
   if (length > 120)
   {
      return MD_TRG_LEN_LMT_ERR;
   }
   return MD_ERR_OK;
}



uint16 PDR(uint index)
{

   //   uint16 *p2data16;

//    if (index < 7)
//    {
//        return ReadBits(&FLS1.Voice.All,index);
//    }

   if (index == 1)
   {
      return FLS1.Voice.All;
   }
   if (index == 2)
   {
      return FLS1.Output.All;
   }
   if (index == 10)
   {
      return BIT1.All;
   }
   if (index == 25)
   {
      return FLS1.Par.FanRunningTime;
   }
   return 0;
//  if (index == 1)
//  {
//      p2data16 = (uint16 *)&FLS1.Voice.All;
//      return p2data16[index];
//  }
//  else if (index == 2)
//  {
//      p2data16 = (uint16 *)&FLS1.Output.All;
//      return p2data16[index];
//  }
//  else
//  {
//      return 0;
//  }
}

void PDW(uint index, uint Data)
{
   uint *p2data16;
//  if (index < 7)
//  {
//      WriteBits(&FLS1.Voice.All,index,Data);
//  }
   if (index == 1)
   {
      p2data16 =  &FLS1.Voice.All;
//        *p2data16 = Data;
      p2data16[index - 1] = Data;
   }
   if (index == 2)
   {
      p2data16 = &FLS1.Output.All;
      p2data16[index - 2] = Data;
   }
//  else if (index == 100)
//  {
//      p2data16 = (uint16*)&Leak1.State.Sys;
//      p2data16[index - 100] = Data;
//  }
//  else if (index == 101)
//  {
//      p2data16 = (uint16*)&Leak1.State.DI;
//      p2data16[index - 101] = Data;
//  }
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



