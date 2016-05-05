
#include "includes.h"



StdAirDataBase *StdAirBlock1;
Md_Tcp_Dep MdTcp1;

Md_Tcp_Dep MdTcp4;


//modbus地址从0开始
//数据计数从1开始
const uint08 PanelDataStr[57][2] =
{
   BITTYPE, 1,  //4001
   BITTYPE, 2,  //4002
   BITTYPE, 3,  //4003
   BITTYPE, 4,  //4004
   BITTYPE, 5,  //4005
   BITTYPE, 6,  //4006
   BITTYPE, 7,  //4007
   BITTYPE, 8,  //4008
   BITTYPE, 9,  //4009
   BITTYPE, 10,  //4010
   BITTYPE, DEF_INDEX,  //4011
   BITTYPE, DEF_INDEX,  //4012
   BITTYPE, DEF_INDEX,  //4013
   BITTYPE, DEF_INDEX,  //4014
   BYTETYPE, 1,  //4015
   BYTETYPE, 2,  //4016
   WORDTYPE, 1,  //4017
   WORDTYPE, 2,  //4018
   WORDTYPE, 3,  //4019
   WORDTYPE, 4,  //4020
   WORDTYPE, 5,  //4021
   WORDTYPE, 6,  //4022
   WORDTYPE, 7,  //4023
   WORDTYPE, 8,  //4024
   WORDTYPE, DEF_INDEX,  //4025
   WORDTYPE, DEF_INDEX,  //4026
   WORDTYPE, DEF_INDEX,  //4027
   WORDTYPE, DEF_INDEX,  //4028
   BITTYPE, 17,  //4029
   BITTYPE, 18,  //4030
   BITTYPE, 19,  //4031
   BITTYPE, 20,  //4032
   BYTETYPE, 3,  //4033
   BYTETYPE, 4,  //4034
   BITTYPE, 21,  //4035
   BITTYPE, 22,  //4036
   BITTYPE, 23,  //4037
   BITTYPE, 24,  //4038
   BYTETYPE, 5,  //4039
   BYTETYPE, 6,  //4040
   BITTYPE, 25,  //4041
   BITTYPE, 26,  //4042
   BITTYPE, 27,  //4043
   BITTYPE, 28,  //4044
   BYTETYPE, 7,  //4045
   BYTETYPE, 8,  //4046
   BITTYPE, 29,  //4047
   BITTYPE, 30,  //4048
   BITTYPE, 31,  //4049
   BITTYPE, 32,  //4050
   BYTETYPE, 9,  //4051
   BYTETYPE, 10, //4052
   WORDTYPE, DEF_INDEX,  //4053
   WORDTYPE, DEF_INDEX,  //4054
   WORDTYPE, DEF_INDEX,  //4055
   WORDTYPE, DEF_INDEX,  //4056
};



uint08 ReadBits(uint08 *p2data, uint08 index)
{
   uint08 tmp = index / 8;
   uint08 tmp2 = index % 8;

   if (testbit(p2data[tmp], tmp2))
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
   uint16 tmp = index / 8;
   uint16 tmp2 = index % 8;

   if (bits > 0)
   {
      setbit(p2data[tmp], tmp2);
   }
   else
   {
      clrbit(p2data[tmp], tmp2);
   }
}





uint16 PanelDataRead(StdAirDataBase *DataBase, uint16 index)
{
   uint08 tmptype =   PanelDataStr[index][0];
   uint08 tmpindex = PanelDataStr[index][1];

   if (tmpindex == DEF_INDEX)
   {
      return (0);
   }
   //对齐
   tmpindex--;
   if (tmptype == BITTYPE)
   {
      if (tmpindex < BIT_LEN_MAX)
      {
         return (ReadBits(DataBase->Solo.Bits.All, tmpindex));
      }
   }
   if (tmptype == BYTETYPE)
   {
      if (tmpindex < BYTE_LEN_MAX)
      {
         return DataBase->Solo.Bytes.All[tmpindex];
      }
   }
   if (tmptype == WORDTYPE)
   {
      if (tmpindex < WORD_LEN_MAX)
      {
         return DataBase->Solo.Words.All[tmpindex];
      }
   }
   return (0);
}




void PanelDataWrite(StdAirDataBase *DataBase, uint16 index, uint16 Data)
{
   uint08 tmptype =   PanelDataStr[index][0];
   uint08 tmpindex =  PanelDataStr[index][1];
   if (tmpindex == DEF_INDEX)
   {
      return;
   }
   tmpindex--;
   if (tmptype == BITTYPE)
   {
      if (tmpindex < BIT_LEN_MAX)
      {
         WriteBits(DataBase->Solo.Bits.All, tmpindex, Data);
      }
   }
   else if (tmptype == BYTETYPE)
   {
      if (tmpindex < BYTE_LEN_MAX)
      {
         DataBase->Solo.Bytes.All[tmpindex] = Data % 256;
      }
   }
   else if (tmptype == WORDTYPE)
   {
      if (tmpindex < WORD_LEN_MAX)
      {
         DataBase->Solo.Words.All[tmpindex] = Data;
      }
   }
}

MdErrEnum StdAirAddrCheck(Md_Tcp_Dep *Tcp)
{
   while ((*Tcp->RawData) != 0x01 && (*Tcp->RawData) != 0xF1 &&
          (*Tcp->RawData) != 0xF2 && (*Tcp->RawData) != 0xF3 &&
          (*Tcp->RawData) != 0xF4 && (*Tcp->RawData) != 0xF5 &&
          (*Tcp->RawData) != 0xF6 && (*Tcp->RawData) != 0xF7 &&
          (*Tcp->RawData) != YYJ1.OP.My485Addr)
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

MdErrEnum StdAirLengthCheck(uint16 trgaddr, uint16 length, uint08 Station)
{
   uint16 ThisLength = 0;
   if (Station == 1)
   {
      ThisLength = _0X01_MAX_DATA_LEN;
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



uint16 PDR(uint16 index, uint08 Station)
{

   uint16 FullData = 0;
//   if ((Station == 0x01) && (YYJ1.OP.COM2poll != 0))
//   {
//      if (index < 15)
//      {
//         return ReadCOM2(&YYJ1, index);
//      }
//   }

   if (Station == 1)
   {
      if (index < _0X01_MAX_DATA_LEN)
      {
         return YYJ_Communication_Read(&YYJ1, index);
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
            {
               return YYJ_Communication_Read(&YYJ1, index);
            }
         }
         break;
      case 0xF7:
      case 0xE7:
         if (index < _0XF7_MAX_DATA_LEN)
         {
            return YYJ_Read_SmallPanel(&YYJ1, index);
         }
         break;
      default:
         break;
      }
   }
   return 0;
}

void PDW(uint16 index, uint16 Data, uint08 Station)
{
   uint16 FullData = 0;
//   if ((Station == 0x01) && (YYJ1.OP.COM2poll != 0))
//   {
//      if (index < 15)
//      {
//         WriteCOM2(&YYJ1, index, Data);
//      }
//   }
   if (Station == 1)
   {
      if (index < _0X01_MAX_DATA_LEN)
      {
         {
            YYJ_Communication_Write(&YYJ1, index, Data);
         }
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
      case 0xF7:
      case 0xE7:
         if (index < _0XF7_MAX_DATA_LEN)
         {
            YYJ_Write_SmallPanel(&YYJ1, index, Data);
         }
         break;
      default:
         break;
      }
   }
}


void StdMdTcpInit(Md_Tcp_Dep *Tcp)
{
   Tcp->AddrCheck = (MdErrEnum(*)(Md_Tcp_SameDep *))StdAirAddrCheck;
   Tcp->LenChkCheck = StdAirLengthCheck;
   rt_kprintf("!!!!Stdmd %s--%s!!!!\r\n", __DATE__, __TIME__);
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
      UartDataBlock->MasterTimeout = 100;
      StartUartSend(USART2, UartDataBlock, (char *)Tcp->p2trg, Tcp->rePkglen);
   }
   UartDataBlock->Flags.All = 0;
   UartDataBlock->RecCnt = 0;
}

void COM4MdTcpRsp(Md_Tcp_Dep *Tcp, UartType *UartDataBlock)
{
   if (Tcp->rePkglen > 0)
   {
      UartDataBlock->MasterTimeout = 100;
      StartUartSend(UART4, UartDataBlock, (char *)Tcp->p2trg, Tcp->rePkglen);
   }
   UartDataBlock->Flags.All = 0;
   UartDataBlock->RecCnt = 0;
}

void MdTcbInit()
{
   StdAirBlock1 = (StdAirDataBase *)rt_malloc(sizeof(StdAirDataBase)); //HeapMemRequire
   rt_memset((uchar *)StdAirBlock1, 0, (sizeof(StdAirDataBase))); //ZeroMemory

   StdMdTcpInit(&MdTcp1);
   StdMdTcpInit(&MdTcp4);
}


const Poll_Def Poll2[2] =
{
   //addr, flag, datlen, addr
   { 0x01, MD_POLL_RD, 3, 0 },
   { 0x01, MD_POLL_WR, 5, 9 }
};

void MdMasterPoll2()
{
   UartType *P2data = &UartAppData2;
   if (P2data->MasterTime == 0)
   {
      P2data->MasterTime = 50;
      //Poll Next
      if (++P2data->PollCnt >= 2)
      {
         P2data->PollCnt = 0;
      }
      MdTcp1.NowPoll = Poll2[P2data->PollCnt];
      StdMdTcpGetReady(&MdTcp1, P2data);
      MdTcp1.rePkglen = Master_ModbusDataSetup(&MdTcp1);
      StdMdTcpRsp(&MdTcp1, P2data);
   }
}

















