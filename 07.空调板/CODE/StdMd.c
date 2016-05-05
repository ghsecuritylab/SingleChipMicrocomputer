
#include "includes.h"

#define MD_POLL_MAX 0x02

Md_Tcp_Dep MdTcp1;
Md_Tcp_Dep MdTcp2;


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
   const uint16 ThisLength = 100;
   if(trgaddr>= ThisLength)
   {
      return MD_TRG_ADDR_ERR;
   }
   if((trgaddr+length)>=ThisLength)
   {
      return MD_TRG_LEN_ERR;
   }
   if(length>120)
   {
      return MD_TRG_LEN_LMT_ERR;
   }
   return MD_ERR_OK;
}


#define ___________Uart1App_____

uint16 PDR1(uint16 index)
{
   if (index == 0)
   {
      return 10;
   }
   return 0;
}
void PDW1(uint16 index, uint16 Data)
{

}


void StdMdTcpInit1(Md_Tcp_Dep *Tcp)
{
   Tcp->LenChkCheck = LengthCheck;
   Tcp->RdData = PDR1;
   Tcp->WrData = PDW1;
}

#define ___________Uart2App_____


uint16 PDR2(uint16 index)
{
   if (index == 0)
   {
      return 10;
   }
   return 0;
}
void PDW2(uint16 index, uint16 Data)
{
 
}


void StdMdTcpInit2(Md_Tcp_Dep *Tcp)
{
   Tcp->LenChkCheck = LengthCheck;
   Tcp->RdData = PDR2;
   Tcp->WrData = PDW2;
}

//////////////////////////////////////////////////////////


void StdMdTcpGetReady(Md_Tcp_Dep *Tcp, UartType *UartDataBlock)
{
   Tcp->RawDataLen = UartDataBlock->RecCnt;
   Tcp->RawData = UartDataBlock->TxRxBuf;
   Tcp->p2trg = UartDataBlock->TxRxBuf;
   Tcp->rePkglen = 0;
}


void StdMdTcpRsp1(Md_Tcp_Dep *Tcp, UartType *UartDataBlock)
{
   if (Tcp->rePkglen > 0)
   {
      StartUart1Send(UartDataBlock, (char *)Tcp->p2trg, Tcp->rePkglen);
   }
   UartDataBlock->Flags.All = 0;
   UartDataBlock->RecCnt = 0;
}
void StdMdTcpRsp2(Md_Tcp_Dep *Tcp, UartType *UartDataBlock)
{
   if (Tcp->rePkglen > 0)
   {
      StartUart2Send(UartDataBlock, (char *)Tcp->p2trg, Tcp->rePkglen);
   }
   UartDataBlock->Flags.All = 0;
   UartDataBlock->RecCnt = 0;
}

void MdTcbInit1()
{
   StdMdTcpInit1(&MdTcp1);
   StdMdTcpGetReady(&MdTcp1, &UartAppData1);
}

void MdTcbInit2()
{
   StdMdTcpInit2(&MdTcp2);
   StdMdTcpGetReady(&MdTcp2, &UartAppData2);
}

MdErrEnum MdRet;
void MdPoll01(void)
{
   UartType *P2data = &UartAppData1;
   if (P2data->Flags.Solo.RecFlame)
   {
      StdMdTcpGetReady(&MdTcp1, P2data);
      MdRet = MdDataDeal(&MdTcp1);
      StdMdTcpRsp1(&MdTcp1, P2data);
      P2data->Flags.Solo.RecFlame = 0;
      P2data->RecCnt = 0;
   }
}

void MdPoll02(void)
{
   UartType *P2data = &UartAppData2;
   if (P2data->Flags.Solo.RecFlame)
   {
      StdMdTcpGetReady(&MdTcp2, P2data);
      MdRet = MdDataDeal(&MdTcp2);
      StdMdTcpRsp2(&MdTcp2, P2data);
      P2data->Flags.Solo.RecFlame = 0;
      P2data->RecCnt = 0;
   }
}


MdErrEnum MdPoll2(void)
{
   UartType *P2data = &UartAppData2;
   if (P2data->Flags.Solo.RecFlame)
   {
      StdMdTcpGetReady(&MdTcp2, P2data);
      MdRet = MdDataDeal(&MdTcp2);
      StdMdTcpRsp2(&MdTcp2, P2data);
      return MdRet;
   }
   return MD_NULL;
}


__flash Poll_Def Poll[MD_POLL_MAX] =
{
   //addr, flag, datlen, addr
   { 0xFF, MD_POLL_RD, 4, 0 },
   { 0xFF, MD_POLL_WR, 16, 6 }
};


void MdMasterPoll()
{
   UartType *P2data = &UartAppData2;
   if (P2data->MasterTime == 0)
   {
      P2data->MasterTime = 50;
      MdTcp2.NowPoll = Poll[P2data->PollCnt];
      //Poll Next
      if (++P2data->PollCnt >= MD_POLL_MAX)
      {
         P2data->PollCnt = 0;
      }
      StdMdTcpGetReady(&MdTcp2, P2data);
      MdTcp2.rePkglen = Master_ModbusDataSetup(&MdTcp2);
//     P2data->PollCnt = 250;
      StdMdTcpRsp2(&MdTcp2, P2data);
   }
   else
   {
      if (MdPoll2() == MD_ERR_OK)
      {
//	 P2data->MasterTime = 50;
      }
   }

}

