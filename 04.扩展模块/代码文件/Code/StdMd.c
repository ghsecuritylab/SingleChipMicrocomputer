
#include "includes.h"

MdErrEnum LengthCheck(uint16 trgaddr, uint16 length)
{
   const uint16 ThisLength = 200;
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
#define ______________________DI
   if (index == 0)
   {
      return MODE1.DI.Solo.DI1;
   }
   if (index == 1)
   {
      return MODE1.DI.Solo.DI2;
   }
   if (index == 2)
   {
      return MODE1.DI.Solo.DI3;
   }
   if (index == 3)
   {
      return MODE1.DI.Solo.DI4;
   }
#define ______________________AI
   if (index >= 4 && index <= 9)
   {
      return MODE1.AI.All[index-4];
   } 
#define ______________________DO
   if (index == 10)
   {
      return MODE1.DO.Solo.DO1;
   }
   if (index == 11)
   {
      return MODE1.DO.Solo.DO2;
   }
   if (index == 12)
   {
      return MODE1.DO.Solo.DO3;
   }
#define ______________________AO
   if (index >= 13 && index <= 16)
   {
      return MODE1.AO.All[index-13];
   }    
   if (index == 20)
   {
      return MODE1.SaveData.Addr485;
   }     
   if (index == 21)
   {
      return strlen(Str);
   }     
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
#define ______________________DO
   if (index == 10)
   {
      MODE1.DO.Solo.DO1 = WriteOneData(Data);
   }
   if (index == 11)
   {
      MODE1.DO.Solo.DO2 = WriteOneData(Data);
   }
   if (index == 12)
   {
      MODE1.DO.Solo.DO3 = WriteOneData(Data);
   }
#define ______________________AO
   if (index >= 13 && index <= 16)
   {
      if (Data >= 1000)
      {
	 Data = 1000;
      }
      MODE1.AO.All[index - 13] = Data;
   }   
   if (index == 20)
   {
      MODE1.SaveData.Addr485 = Data;
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



