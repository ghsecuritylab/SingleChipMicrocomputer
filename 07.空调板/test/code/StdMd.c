
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
//  const uint16 ThisLength = 50;
//  if(trgaddr>= ThisLength)
//  {
//     return MD_TRG_ADDR_ERR;
//  }
//  if((trgaddr+length)>=ThisLength)
//  {
//     return MD_TRG_LEN_ERR;
//  }
//  if(length>120)
//  {
//     return MD_TRG_LEN_LMT_ERR;
//  }
   return MD_ERR_OK;
}



ulong maxSpeed = 1300;
ulong currentSpeedsET;
#define ___________Uart1App_____

uint16 PDR(uint16 index)
{
   uint16 *p2data16;
   if (index <= 23)
   {
      p2data16 = (uint16 *)&FC1.Run;
      return p2data16[index];
   }
   else if (index >= 24 && index <= 28)
   {
      p2data16 = (uint16 *)&FC1.Buff;
      return p2data16[index - 24];
   }
   else if (index == 29)
   {
       return nTimeSpeed;
   } 
   else if (index >= 30 && index <= 43)
   {
      p2data16 = (uint16 *)&FC1.FCpid;
      return p2data16[index - 30];
   }
   else if (index == 45)
   {
      return nowSolenoidValve *10 / 9;
   }
   else if (index == 46)
   {
      return maxSpeed;
   }
   else if (index == 47)
   {
      return speedPerMin;
   }
   else if (index == 48)
   {
      return currentSpeedsET;
   }
//  else if (index  == 22)
//  {
//      return testCRC2;
//  }
//  else if (index  == 23)
//  {
//      return testCRC3;
//  }
//  else if (index  == 24)
//  {
//      return testCRC4;
//  }
   else if (index == 100)
   {
      return FC1.State.Sys.All;
   }
   else if (index == 101)
   {
      return FC1.State.DI.All;
   }
   return 0;
}
void PDW(uint16 index, uint16 Data)
{
   uint16 *p2data16;
   if (index == 0)
   {
      p2data16 = (uint16 *)&FC1.Buff.MasterSetTemp;
      p2data16[index] = Data;
//    FC1.Buff.MasterFlag.solo.MasterSetTemp = 1;
      FC1.Buff.LastMasterSetTemp = FC1.Run.SetTemp;
   }
   else if (index == 1)
   {
      p2data16 = (uint16 *)&FC1.Buff.MasterSetFanlvl;
      p2data16[index - 1] = Data;
      FC1.Buff.LastMasterSetFanlvl = FC1.Run.FanLvlSet;
   }
   else if (index == 2)
   {
      p2data16 = (uint16 *)&FC1.Buff.MasterSetMode;
      p2data16[index - 2] = Data;
      FC1.Buff.LastMasterSetMode = FC1.Run.ModeSet;
   }
   else if (index >= 3 && index <= 23)
   {
      p2data16 = (uint16 *)&FC1.Run.SetTime;
      p2data16[index - 3] = Data;
   }
   else if (index >= 24 && index <= 28)
   {
      p2data16 = (uint16 *)&FC1.Buff;
      p2data16[index - 24] = Data;
   }
   else if (index == 29)
   {
       nTimeSpeed = Data;
   } 
   else if (index == 46)
   {
      maxSpeed = Data;
   }
   else if (index == 48)
   {
      currentSpeedsET = Data;
   }
   else if (index == 100)
   {
      p2data16 = (uint16 *)&FC1.Buff.MasterStarted;
      p2data16[index - 100] = Data & 0x0001;
      FC1.Buff.LastMasterStarted = (FC1.State.Sys.All & 0x0001);
   }
   else if (index == 101)
   {
      p2data16 = (uint16 *)&FC1.State.DI;
      p2data16[index - 101] = Data;
   }
}


void StdMdTcpInit(Md_Tcp_Dep *Tcp)
{
   Tcp->LenChkCheck = LengthCheck;
   Tcp->RdData = PDR;
   Tcp->WrData = PDW;
}

#define ___________Uart2App_____


uint16 PDR2(uint16 index)
{
   if (index == 6)
   {
      return FC1.Buff.RoomTemp;
   }
   else if (index == 7)
   {
      return FC1.Run.SetTempMax;
   }
   else if (index == 8)
   {
      return FC1.Run.SetTempMin;
   }
   else if (index == 9)
   {
      return FC1.Run.BackLightDelay;
   }
   else if (index == 10)
   {
       if (FC1.Buff.MasterSetTemp != FC1.Buff.LastMasterSetTemp)   
       {
//         FC1.Buff.LastMasterSetTemp = FC1.Buff.MasterSetTemp;
           return FC1.Buff.MasterSetTemp; 
       }
       else
       {
           return 0;
       }
   }
   else if (index == 11)
   {
       if (FC1.Buff.MasterSetFanlvl != FC1.Buff.LastMasterSetFanlvl)   
       {
//         FC1.Buff.LastMasterSetTemp = FC1.Buff.MasterSetTemp;
           return FC1.Buff.MasterSetFanlvl; 
       }
       else
       {
           return 5;
       }
   }
   else if (index == 12)
   {
       if (FC1.Buff.MasterSetMode != FC1.Buff.LastMasterSetMode)   
       {
//         FC1.Buff.LastMasterSetTemp = FC1.Buff.MasterSetTemp;
           return FC1.Buff.MasterSetMode; 
       }
       else
       {
           return 5;
       }
   }
   else if (index == 13)
   {
       if ((FC1.Buff.MasterStarted & 0x0001) != (FC1.Buff.LastMasterStarted & 0x0001))   
       {
//         FC1.Buff.LastMasterSetTemp = FC1.Buff.MasterSetTemp;
           return FC1.Buff.MasterStarted & 0x0001; 
       }
       else
       {
           return 5;
       }
   }
   return 0;
}
void PDW2(uint16 index, uint16 Data)
{
   uint16 *p2data16;
   if (index <= 2)
   {
      p2data16 = (uint16 *)&FC1.Run;
      p2data16[index] = Data;

       if (FC1.Run.SetTemp == FC1.Buff.MasterSetTemp)    //判断副控设置温度与主控设置温度是否相同
       {
           FC1.Buff.LastMasterSetTemp = FC1.Run.SetTemp;
       }
       if (FC1.Run.FanLvlSet == FC1.Buff.MasterSetFanlvl)    //判断副控设置温度与主控设置温度是否相同
       {
           FC1.Buff.LastMasterSetFanlvl = FC1.Run.FanLvlSet;
       }
       if (FC1.Run.ModeSet == FC1.Buff.MasterSetMode)    //判断副控设置温度与主控设置温度是否相同
       {
           FC1.Buff.LastMasterSetMode = FC1.Run.ModeSet;
       }
   }
   else if (index == 3)
   {
      p2data16 = (uint16 *)&FC1.State.Sys;
      p2data16[index - 3] = p2data16[index - 3] & 0xFFFE | (Data & 0x0001);
       if ((FC1.State.Sys.All & 0x0001) == (FC1.Buff.MasterStarted & 0x0001))    //判断副控设置温度与主控设置温度是否相同
       {
           FC1.Buff.LastMasterStarted = (FC1.State.Sys.All & 0x0001);
       }
   }
//  else if (index == 4)
//  {
//      p2data16 = (uint16*)&FC1.State.DI;
//      p2data16[index - 4] = Data;
//  }
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


void StdMdTcpRsp(Md_Tcp_Dep *Tcp, UartType *UartDataBlock)
{
   if (Tcp->rePkglen > 0)
   {
      StartUartSend(UartDataBlock, (char *)Tcp->p2trg, Tcp->rePkglen);
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

void MdTcbInit()
{
   StdMdTcpInit(&MdTcp1);
   StdMdTcpGetReady(&MdTcp1, &UartAppData1);
}

void MdTcbInit2()
{
   StdMdTcpInit2(&MdTcp2);
   StdMdTcpGetReady(&MdTcp2, &UartAppData2);
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
//__flash Poll_Def Poll[MD_POLL_MAX] =
//{
//   //addr, flag, datlen, addr
//   { 1, MD_POLL_RD, 4, 0 },
//   { 1, MD_POLL_WR, 8, 6 }
//};


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
//    P2data->MasterTime = 150;
      }
   }

}

