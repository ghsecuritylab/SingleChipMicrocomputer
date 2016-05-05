
#include "includes.h"



Md_Tcp_Dep MdTcp2;
uint16 PolMdTimeOutTimer;



MdErrEnum PolAddrCheck(Md_Tcp_Dep *Tcp)
{
   while ((*Tcp->RawData) != 0xF1 && (*Tcp->RawData) != 0xF2 &&
          (*Tcp->RawData) != 0xF3 && (*Tcp->RawData) != 0xF4 &&
          (*Tcp->RawData) != 0xF5 && (*Tcp->RawData) != 0xF6 &&
          (*Tcp->RawData) != 0xF7 && (*Tcp->RawData) != YYJ1.OP.My485Addr)
   {
      Tcp->RawData++;
      Tcp->RawDataLen--;
      if (Tcp->RawDataLen < 8)
      {
         break;
      }
   }
   if (Tcp->RawDataLen >= 8)
   {
      return MD_ERR_OK;
   }
   else
   {
      return MD_DEV_ADDR_ERR;
   }
}


MdErrEnum PolLengthCheck(uint16 trgaddr, uint16 length, uint08 Station)
{
   uint16 ThisLength = 0;
   if (Station == 0xF7 || Station == YYJ1.Small.Solo.SmallAddr)
   {
      ThisLength = _0XF7_MAX_DATA_LEN;
   }
   else
   {
      if (Station == YYJ1.OP.My485Addr)
      {
         ThisLength = _0XALL_MAX_DATA_LEN;
      }
      switch (Station)
      {
      case 0xF1:
      case 0xE1:
         ThisLength = _0XF1_MAX_DATA_LEN;
         break;
      case 0xF2:
      case 0xE2:
         ThisLength = _0XF2_MAX_DATA_LEN;
         break;
      case 0xF3:
      case 0xE3:
         ThisLength = _0XF3_MAX_DATA_LEN;
         break;
      case 0xF4:
      case 0xE4:
         ThisLength = _0XF4_MAX_DATA_LEN;
         break;
      case 0xF5:
      case 0xE5:
         ThisLength = _0XF5_MAX_DATA_LEN;
         break;
      case 0xF6:
      case 0xE6:
         ThisLength = _0XF6_MAX_DATA_LEN;
         break;
      case 0xF7:
      case 0xE7:
         ThisLength = _0XF7_MAX_DATA_LEN;
         break;
      default:
         break;
      }
   }
   return MD_ERR_OK;
}


uint16 PolPDR(uint16 index, uint08 Station)
{
   uint16 FullData = 0;
   if (Station == 0xF7 || Station == YYJ1.Small.Solo.SmallAddr)
   {
      if (index < _0XF7_MAX_DATA_LEN)
      {
         return YYJ_Read_SmallPanel(&YYJ1, index);
      }
   }
   else
   {
      if (Station == YYJ1.OP.My485Addr)
      {
         if (index < 100)
         {
            Station = 0xF1 + index / 10;
            index = index % 10;
            FullData  = 1;
         }
         if (index >= 100 && index <= 124)
         {
            return YYJ_ReadPID(&YYJ1.OP, index - 100);
         }
         if (index >= 125 && index <= 199)
         {
            return YYJ_ReadPar(&YYJ1.OP, index - 125);
         }
         if (index >= 200 && index <= 214)
         {
            return YYJ_Adjust_Read(&YYJ1, index - 200);
         }
	 if (index == 215)
	 {
	    return YYJ1.OP.COM4Shield;
	 }
	 if (index == 216)
	 {
	    return YYJ1.OP.COM2poll;
	 }
         if (index >= 500)
         {
            return YYJ_Communication_Read(&YYJ1, index - 500);
         }
      }
      switch (Station)
      {
      case 0xF1:
      case 0xE1:
         if (index < _0XF1_MAX_DATA_LEN)
         {
            return POL_DI_Block.uint16All[index];
         }
         else
         {
            return 0;
         }
         break;
      case 0xF2:
      case 0xE2:
         if (index < _0XF2_MAX_DATA_LEN)
         {
            return Relays.uint16All[index];
         }
         else
         {
            return 0;
         }
         break;
      case 0xF3:
      case 0xE3:
         if (index < _0XF3_MAX_DATA_LEN)
         {
            if (FullData == 1)
            {
               return POL_AI_Block.All[index]; //4096
            }
            else
            {
               return POL_AI_Block.All[index] / 4; //1024
            }
         }
         else
         {
            return 0;
         }
         break;
      case 0xF4:
      case 0xE4:
         if (index < _0XF4_MAX_DATA_LEN)
         {
            if (FullData == 1)
            {
               return POL_AO_Block.All[index]; //1024
            }
            else
            {
               return POL_AO_Block.All[index] / 4; //256
            }
         }
         else
         {
            return 0;
         }
         break;
      case 0xF5:
      case 0xE5:
         if (index < _0XF5_MAX_DATA_LEN)
         {
            return Lamps.uint16All[index];
         }
         else
         {
            return 0;
         }
         break;
      case 0xF6:
      case 0xE6:
         if (index < _0XF6_MAX_DATA_LEN)
         {
//	    if (YYJ1.OP.SysPar.SaveBit.Solo.MCU1_PLC0 == 0)
//	    {
//	       return
//	    }
//	    else
	    {
               return YYJ_Communication_Read(&YYJ1, index);
            }
         }
         break;
      default:
         break;
      }
   }
   return 0;
}

void PolPDW(uint16 index, uint16 Data, uint08 Station)
{
   uint16 FullData = 0;
   if (Station == 0xF7 || Station == YYJ1.Small.Solo.SmallAddr)
   {
      if (index < _0XF7_MAX_DATA_LEN)
      {
         YYJ_Write_SmallPanel(&YYJ1, index, Data);
      }
   }
   else
   {
      if (Station == YYJ1.OP.My485Addr)
      {
         if (index < 100)
         {
            Station = 0xF1 + index / 10;
            index = index % 10;
            FullData  = 1;
         }
         if (index >= 100 && index <= 124)
         {
            YYJ_WritePID(&YYJ1.OP, index - 100, Data);
         }
         if (index >= 125 && index <= 199)
         {
            YYJ_WritePar(&YYJ1.OP, index - 125, Data);
         }
         if (index >= 200 && index <= 214)
         {
            YYJ_Adjust_Write(&YYJ1, index - 200, Data);
         }
         if (index == 215)
         {
            YYJ1.OP.COM4Shield = Data;
         } 	 
	 if (index == 216)
	 {
	    YYJ1.OP.COM2poll = Data;
	 }        
         if (index >= 500)
         {
            YYJ_Communication_Write(&YYJ1, index - 500, Data);
         }
      }
      switch (Station)
      {
      case 0xF1:
      case 0xE1:
         if (index < _0XF1_MAX_DATA_LEN)
         {
            POL_DI_Block.uint16All[index] = Data;
         }
         break;
      case 0xF2:
      case 0xE2:
         if (index < _0XF2_MAX_DATA_LEN)
         {
            Relays.uint16All[index] = Data;
         }
         break;
      case 0xF3:
      case 0xE3:
         if (index < _0XF3_MAX_DATA_LEN)
         {
            if (FullData == 1)
            {
               POL_AI_Block.All[index] = Data;
            }
            else
            {
               POL_AI_Block.All[index] = Data * 4;
            }
         }
         break;
      case 0xF4:
      case 0xE4:
         if (index < _0XF4_MAX_DATA_LEN)
         {
            if (FullData == 1)
            {
               POL_AO_Block.All[index] = Data;
            }
            else
            {
               POL_AO_Block.All[index] = Data * 4;
            }
         }
         break;
      case 0xF5:
      case 0xE5:
         if (index < _0XF5_MAX_DATA_LEN)
         {
            Lamps.uint16All[index] = Data;
         }
         break;
      case 0xF6:
      case 0xE6:
         if (index < _0XF6_MAX_DATA_LEN)
         {
            {
               YYJ_Communication_Write(&YYJ1, index, Data);
            }
         }
         break;
      default:
         break;
      }
   }
}


void PolMdTcpInit(Md_Tcp_Dep *Tcp)
{
   Tcp->AddrCheck = (MdErrEnum(*)(Md_Tcp_SameDep *))PolAddrCheck;
   Tcp->LenChkCheck = PolLengthCheck;
   Tcp->RdData = PolPDR;
   Tcp->WrData = PolPDW;
}

void PolMdTcpGetReady(Md_Tcp_Dep *Tcp, UartType *UartDataBlock)
{
   Tcp->RawDataLen = UartDataBlock->RecCnt;
   Tcp->RawData = UartDataBlock->TxRxBuf;
   Tcp->p2trg = UartDataBlock->TxRxBuf;
   Tcp->rePkglen = 0;
}


void PolMdTcpRsp(Md_Tcp_Dep *Tcp, UartType *UartDataBlock)
{
   if (Tcp->rePkglen > 0)
   {
      UartDataBlock->MasterTimeout = 100;
      PolMdTimeOutTimer = 200 * 5;
      StartUartSend(USART3, UartDataBlock, (char *)Tcp->p2trg, Tcp->rePkglen);
   }
   UartDataBlock->Flags.All = 0;
   UartDataBlock->RecCnt = 0;
}

void PolMdTcbInit()
{
   PolMdTcpInit(&MdTcp2);
}


void PolMdTimeOut()
{
   if (PolMdTimeOutTimer > 0)
   {
      PolMdTimeOutTimer--;
      if (PolMdTimeOutTimer == 0)
      {
         //DO
         Relays.uint16All[0] = 0;
         Relays.uint16All[1] = 0;
         Relays.uint16All[2] = 0;
         Relays.uint16All[3] = 0;
         //AO
         POL_AO_Block.All[0] = 0;
         POL_AO_Block.All[1] = 0;
         POL_AO_Block.All[2] = 0;
         POL_AO_Block.All[3] = 0;
         POL_AO_Block.All[4] = 0;
         POL_AO_Block.All[5] = 0;
         POL_AO_Block.All[6] = 0;
         //Light
         Lamps.uint16All[0] = 0;
      }
   }
}




MdErrEnum MdRet;




#define MD_POLL_MAX 0x02

const Poll_Def Poll[MD_POLL_MAX] =
{
   //addr, flag, datlen, addr
   { 0xF7, MD_POLL_RD, 4, 52 },
   { 0xF7, MD_POLL_WR, 2, 56 }
};

void MdMasterPoll()
{
   UartType *P2data = &UartAppData3;
   if (P2data->MasterTime == 0)
   {
      P2data->MasterTime = 50;
      //Poll Next
      if (++P2data->PollCnt >= MD_POLL_MAX)
      {
         P2data->PollCnt = 0;
      }
      MdTcp2.NowPoll = Poll[P2data->PollCnt];
      PolMdTcpGetReady(&MdTcp2, P2data);
      MdTcp2.rePkglen = Master_ModbusDataSetup(&MdTcp2);
      PolMdTcpRsp(&MdTcp2, P2data);
   }
}



