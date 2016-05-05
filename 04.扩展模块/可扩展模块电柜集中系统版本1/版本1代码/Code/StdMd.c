
#include "includes.h"

MdErrEnum LengthCheck(uint16 trgaddr, uint16 length)
{
//   const uint16 ThisLength = 200;
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




uint16 PDR(uint16 index)
{
   if (index < 5)
   {
      return MODE1.AI.All[index];
   }
   if (index == 7)
   {
     return ADCSRA_ADSC;
   }
   if (index == 8)
   {
     return MODE1.AI.Solo.ADCBuff;
   }
   if (index == 9)
   {
      return 22;
   }   
   if (index > 9 && index < 14)
   {
      return MODE1.AO.All[index-10];
   }   
   if (index == 18)
   {
      return 22;
   }
   if (index == 19)
   {
      return MODE1.SaveData.Solo.Save1;
   }
   return 0;
} 

void PDW(uint16 index, uint16 Data)
{
   if (MdTcp1.RegArea == 2 ||  MdTcp1.RegArea == 3)
   {
      return;
   }
   if (index > 9 && index < 14)
   {
       MODE1.AO.All[index-10] = Data;
   }
   if (index == 19)
   {
      MODE1.SaveData.Solo.Save1 = Data;
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



