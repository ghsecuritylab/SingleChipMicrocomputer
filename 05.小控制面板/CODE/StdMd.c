
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


uint16 PDR(uint index)
{
   if (index == 52) //远程开机
   {
      return CTR1.Status.Ctrl.Solo.RemotePower;
   }
   if (index == 53) //远程值机
   {
      return CTR1.Status.Ctrl.Solo.RemoteStandby;
   }
   if (index == 54) //本地开机
   {
      return CTR1.Status.Ctrl.Solo.LocalPower;
   }
   if (index == 55) //本地值机
   {
      return CTR1.Status.Ctrl.Solo.LocalStandby;
   }
   if (index == 56) //16位LED
   {
      return CTR1.Status.LED_16bit;
   }
   if (index == 57) //485地址
   {
      return CTR1.Status.RS485addr ;
   }
   return 0;
} 

void PDW(uint index, uint Data)
{
   if (index == 52) //远程开机
   {
      CTR1.Status.Ctrl.Solo.RemoteORLocal = 1;
      CTR1.Status.Ctrl.Solo.RemotePower = Data;
   }
   if (index == 53) //远程值机
   {
      CTR1.Status.Ctrl.Solo.RemoteORLocal = 1;
      CTR1.Status.Ctrl.Solo.RemoteStandby = Data;
   }
   if (index == 54) //本地开机
   {
      CTR1.Status.Ctrl.Solo.RemoteORLocal = 0;
      CTR1.Status.Ctrl.Solo.LocalPower = Data;
   }
   if (index == 55) //本地值机
   {
      CTR1.Status.Ctrl.Solo.RemoteORLocal = 0;
      CTR1.Status.Ctrl.Solo.LocalStandby = Data;
   }
   if (index == 56) //16位LED
   {
     CTR1.Status.LED_16bit = Data;
   }

   if (index == 57) //485地址
   {
     CTR1.Status.RS485addr = Data;
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



