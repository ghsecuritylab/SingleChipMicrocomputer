
#include "includes.h"

ModbusTcp MdTcp1;
ModbusErrorEnum Err = NONE_ERR;

__flash uint16 CRCtbl[16] =
{
   0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401,
   0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400
};

uint16 GetCRC16(uint08 *ptr, uint16 len)
{
   uint16 crc = 0xffff;
   uint08  tmp;

   while (len-- != 0)
   {
      tmp = crc ^ *ptr;
      crc >>= 4;
      crc ^= CRCtbl[tmp & 0x0f];
      tmp = crc ^ ((*ptr) >> 4);
      crc >>= 4;
      crc ^= CRCtbl[tmp & 0x0f];
      ptr++;
   }
   return (crc);
}

uint16 RegisterStartAddress(ModbusTcp *Tcp)
{
   return Tcp->ReadData[2] * 256 + Tcp->ReadData[3];
}


uint16 RegsisterNumber(ModbusTcp *Tcp)
{
   return Tcp->ReadData[4] * 256 + Tcp->ReadData[5];
}

uint16 ModbusRead(uint16 index)
{
   if (index == 0)
   {
      return 10;
   }
   if (index == 1)
   {
      return 20;
   }
   if (index == 9)
   {
      return MODE1.DO.Solo.LED2;
   }
   return 0;
}

void ModbusWrite(uint16 index, uint16 data)
{
   if (index == 9)
   {
      MODE1.DO.Solo.LED2 = data;
   }
}

ModbusErrorEnum CheckAddress(ModbusTcp *Tcp)
{
   if (Tcp->ReadData[0] != 0x01 && Tcp->ReadData[1] != 0x02)
   {
      return ID_ERR;
   }
   return NONE_ERR;
}

ModbusErrorEnum CheckCommand(ModbusTcp *Tcp)
{
   if (Tcp->ReadData[1] == 0x01 || Tcp->ReadData[1] == 0x02 ||
       Tcp->ReadData[1] == 0x03 || Tcp->ReadData[1] == 0x04)
   {
      Tcp->Flags.Read0_Write1 = 0;
      return NONE_ERR;
   }
   else if (Tcp->ReadData[1] == 0x05 || Tcp->ReadData[1] == 0x06 ||
            Tcp->ReadData[1] == 0x0F || Tcp->ReadData[1] == 0x10)
   {
      Tcp->Flags.Read0_Write1 = 1;
      return NONE_ERR;
   }
   else
   {
      return CMD_ERR;
   }
}

ModbusErrorEnum CheckLength(ModbusTcp *Tcp)
{
   if (Tcp->Flags.Read0_Write1)
   {
      if (Tcp->ReadDataLen == 8) //write one
      {
         return NONE_ERR;
      }
      else if (Tcp->ReadDataLen == (9 + Tcp->ReadData[6]) && (Tcp->ReadData[6] == (Tcp->ReadData[5] * 2))) //write more
      {
         return NONE_ERR;
      }
      else if ((Tcp->ReadDataLen == (9 + Tcp->ReadData[6])) && (Tcp->ReadData[5] <= (Tcp->ReadData[6] * 8)) &&\
                  (Tcp->ReadData[5] > (Tcp->ReadData[5] * 8))) //write more
      {
         return NONE_ERR;
      }
      else
      {
         return LENGTH_WRITE_ERR;
      }
   }
   else
   {
      if (Tcp->ReadDataLen == 8) //read one
      {
         return NONE_ERR;
      }
      else if (Tcp->ReadDataLen == (5 + Tcp->ReadData[2])) //read more
      {
         return NONE_ERR;
      }
      else
      {
         return  LENGTH_READ_ERR;
      }
   }
}

ModbusErrorEnum CheckCrc(ModbusTcp *Tcp)
{
   uint16 tmpCRC1 = GetCRC16(Tcp->ReadData, Tcp->ReadDataLen - 2);
   uint16 tmpCRC2 = Tcp->ReadData[Tcp->ReadDataLen - 1] * 256 + Tcp->ReadData[Tcp->ReadDataLen - 2];
   if (tmpCRC1 != tmpCRC2)
   {
      return CRC_ERR;
   }
   return NONE_ERR;
}

ModbusErrorEnum ReadWriteLengthAddressLimit(ModbusTcp *Tcp, uint08 SetLength)
{
   if (Tcp->Flags.Read0_Write1)
   {
      uint16 trgaddr = RegisterStartAddress(Tcp);
      uint16 length  = RegsisterNumber(Tcp);
      if (trgaddr > SetLength)
      {
         return REG_ADDR_BEYOND_ERR;
      }
      if (length > SetLength)
      {
         return REG_LEN_BEYOND_ERR;
      }
      return NONE_ERR;
   }
   else
   {
      return NONE_ERR;
   }
}

ModbusErrorEnum SendErrorRepot(ModbusTcp *Tcp)
{
   Err = CheckAddress(Tcp);
   if (Err != NONE_ERR)
   {
      return Err;
   }
   Err = CheckCommand(Tcp);
   if (Err != NONE_ERR)
   {
      return Err;
   }
   Err = CheckLength(Tcp);
   if (Err != NONE_ERR)
   {
      return Err;
   }
   Err = CheckCrc(Tcp);
   if (Err != NONE_ERR)
   {
      return Err;
   }
   return NONE_ERR;
}

uint08 SlaveAnswerDataDeal(ModbusTcp *Tcp)
{
   uint08 tmp = 0;
   uint08 tmpBit = 0;
   uint08 tmpindex = 0;
   uint16 itmp = 0;
   uint16 Address = RegisterStartAddress(Tcp);
   uint16 Number  = RegsisterNumber(Tcp);
#define _MODBUSANSWER_0X01
#define _MODBUSANSWER_0X02

   if (Tcp->ReadData[1] == CMD_0x01 || Tcp->ReadData[1] == CMD_0x02)
   {
      Tcp->SendData[0] = Tcp->ReadData[0];
      Tcp->SendData[1] = Tcp->ReadData[1];
      if (Number % 8 == 0)
      {
         Tcp->SendData[2] = Number / 8;
      }
      else
      {
         Tcp->SendData[2] = Number / 8 + 1;
      }
      tmpindex = 3;
      for (tmp = 0; tmp < Number; tmp++)
      {
         itmp = ModbusRead(Address + tmp);
         if (itmp > 0)
         {
            SetBit(Tcp->SendData[tmpindex], tmpBit);
         }
         if (++tmpBit >= 8)
         {
            tmpBit = 0;
            tmpindex++;
            Tcp->SendData[tmpindex] = 0;
         }
      }
      if (tmpBit != 0)
      {
         tmpindex++;
      }
      itmp = GetCRC16(Tcp->SendData, tmpindex);
      Tcp->SendData[tmpindex++] = itmp % 256;
      Tcp->SendData[tmpindex++] = itmp / 256;
   }

#define _MODBUSANSWER_0X03
#define _MODBUSANSWER_0X04

   else if (Tcp->ReadData[1] == CMD_0x03 || Tcp->ReadData[1] == CMD_0x04)
   {
      tmpindex = 3;
      Tcp->SendData[0] = Tcp->ReadData[0];
      Tcp->SendData[1] = Tcp->ReadData[1];
      Tcp->SendData[2] = Tcp->ReadData[5] * 2; //返回数据的字节数
      for (tmp = 0; tmp < Number; tmp++)
      {
         itmp = ModbusRead(Address + tmp);
         Tcp->SendData[tmpindex++] = itmp / 256;
         Tcp->SendData[tmpindex++] = itmp % 256;
      }
      itmp = GetCRC16(Tcp->SendData, tmpindex);
      Tcp->SendData[tmpindex++] = itmp % 256;
      Tcp->SendData[tmpindex++] = itmp / 256;
   }

#define _MODBUSANSWER_0X05
#define _MODBUSANSWER_0X06

   else if (Tcp->ReadData[1] == CMD_0x05 || Tcp->ReadData[1] == CMD_0x06)
   {
      tmpindex = 4;
      itmp = Tcp->ReadData[tmpindex++] * 256;
      itmp += Tcp->ReadData[tmpindex++];
      ModbusWrite(Address, itmp);
      tmpindex = 0;
      Tcp->SendData[tmpindex++] = Tcp->ReadData[0]; //栈ID
      Tcp->SendData[tmpindex++] = Tcp->ReadData[1]; //功能码
      Tcp->SendData[tmpindex++] = Tcp->ReadData[2]; //寄存器高位地址
      Tcp->SendData[tmpindex++] = Tcp->ReadData[3]; //寄存器低位地址
      Tcp->SendData[tmpindex++] = Tcp->ReadData[4]; //寄存器数量高位
      Tcp->SendData[tmpindex++] = Tcp->ReadData[5]; //寄存器数量低位
      itmp = GetCRC16(Tcp->SendData, 6);           //计算CRC值
      Tcp->SendData[tmpindex++] = itmp % 256;       //CRC 低位在前
      Tcp->SendData[tmpindex++] = itmp / 256;       //CRC 高位在前
      Tcp->SendDataLen = tmpindex;
   }

#define _MODBUSANSWER_0X0F
#define _MODBUSANSWER_0X10

   else if (Tcp->ReadData[1] == CMD_0x0F || Tcp->ReadData[1] == CMD_0x10)
   {
      tmpindex = 4;
      for (tmp = 0; tmp < Number; tmp++)
      {
         itmp = Tcp->ReadData[tmpindex++] * 256; //第七个开始为数据的高位
         itmp += Tcp->ReadData[tmpindex++];
         ModbusWrite((Address + tmp), itmp);
      }
      tmpindex = 0;
      Tcp->SendData[tmpindex++] = Tcp->ReadData[0]; //栈ID
      Tcp->SendData[tmpindex++] = Tcp->ReadData[1]; //功能码
      Tcp->SendData[tmpindex++] = Tcp->ReadData[2]; //寄存器高位地址
      Tcp->SendData[tmpindex++] = Tcp->ReadData[3]; //寄存器低位地址
      Tcp->SendData[tmpindex++] = Tcp->ReadData[4]; //寄存器数量高位
      Tcp->SendData[tmpindex++] = Tcp->ReadData[5]; //寄存器数量低位
      itmp = GetCRC16(Tcp->SendData, 6);           //计算CRC值
      Tcp->SendData[tmpindex++] = itmp % 256;       //CRC 低位在前
      Tcp->SendData[tmpindex++] = itmp / 256;       //CRC 高位在前
   }
   return tmpindex;
}

void SlaveModbus(ModbusTcp *Tcp)
{
   UartType *P2data = &UartAppData1;
   ModbusErrorEnum Err = NONE_ERR;
   if (P2data->Flags.Solo.RecFlame)
   {
      Tcp->ReadDataLen = P2data->RxdCount;
      Tcp->ReadData    = P2data->TxRxBuff;
      Tcp->SendData    = P2data->TxRxBuff;
      Tcp->SendDataLen = SlaveAnswerDataDeal(Tcp);
//      if (Err != SendErrorRepot(Tcp))
//      {
//         return;
//      }
      if (Tcp->SendDataLen > 0)
      {
         StartUartSend(P2data, (char *)Tcp->SendData, Tcp->SendDataLen);
      }
      P2data->RxdCount = 0;
      P2data->Flags.All = 0;
   }
}




#if 0
void ReadCommand_01H_02H(ModbusTcp *Tcp)
{
   uint08 tmp = 0;
   uint08 tmpBit = 0;
   uint08 tmpindex = 0;
   uint16 itmp = 0;
   uint16 Address   = RegisterStartAddress(Tcp);
   uint16 Number    = RegsisterNumber(Tcp);
   Tcp->SendData[0] = Tcp->ReadData[0];
   Tcp->SendData[1] = Tcp->ReadData[1];
   if (Number % 8 == 0)
   {
      Tcp->SendData[2] = Number / 8;
   }
   else
   {
      Tcp->SendData[2] = Number / 8 + 1;
   }
   tmpindex = 3;
   for (tmp = 0; tmp < Number; tmp++)
   {
      itmp = ModbusRead(Address + tmp);
      if (itmp > 0)
      {
         SetBit(Tcp->SendData[tmpindex], tmpBit);
      }
      if (++tmpBit >= 8)
      {
         tmpBit = 0;
         tmpindex++;
         Tcp->SendData[tmpindex] = 0;
      }
   }
   if (tmpBit != 0)
   {
      tmpindex++;
   }
   itmp = GetCRC16(Tcp->SendData, tmpindex);
   Tcp->SendData[tmpindex++] = itmp % 256;
   Tcp->SendData[tmpindex++] = itmp / 256;
}

void ReadCommand_03H_04H(ModbusTcp *Tcp)
{
   uint08 tmp = 0;
   uint08 tmpindex = 3;
   uint16 itmp = 0;
   uint16 Address = RegisterStartAddress(Tcp);
   uint16 Number  = RegsisterNumber(Tcp);
   Tcp->SendData[0] = Tcp->ReadData[0];
   Tcp->SendData[1] = Tcp->ReadData[1];
   Tcp->SendData[2] = Tcp->ReadData[5] * 2; //返回数据的字节数
   for (tmp = 0; tmp < Number; tmp++)
   {
      itmp = ModbusRead(Address + tmp);
      Tcp->SendData[tmpindex++] = itmp / 256;
      Tcp->SendData[tmpindex++] = itmp % 256;
   }
   itmp = GetCRC16(Tcp->SendData, tmpindex);
   Tcp->SendData[tmpindex++] = itmp % 256;
   Tcp->SendData[tmpindex++] = itmp / 256;
   Tcp->SendDataLen = tmpindex;
}

void WriteCommand_05H_06H(ModbusTcp *Tcp)
{
   uint16 itmp = 0;
   uint08 tmpindex = 4;
   uint16 Address = RegisterStartAddress(Tcp);
   uint16 Number  = RegsisterNumber(Tcp);
   itmp = Tcp->ReadData[tmpindex++] * 256;
   itmp += Tcp->ReadData[tmpindex++];
   ModbusWrite(Address, itmp);
   tmpindex = 0;
   Tcp->SendData[tmpindex++] = Tcp->ReadData[0]; //栈ID
   Tcp->SendData[tmpindex++] = Tcp->ReadData[1]; //功能码
   Tcp->SendData[tmpindex++] = Tcp->ReadData[2]; //寄存器高位地址
   Tcp->SendData[tmpindex++] = Tcp->ReadData[3]; //寄存器低位地址
   Tcp->SendData[tmpindex++] = Tcp->ReadData[4]; //寄存器数量高位
   Tcp->SendData[tmpindex++] = Tcp->ReadData[5]; //寄存器数量低位
   itmp = GetCRC16(Tcp->SendData, 6);           //计算CRC值
   Tcp->SendData[tmpindex++] = itmp % 256;       //CRC 低位在前
   Tcp->SendData[tmpindex++] = itmp / 256;       //CRC 高位在前
   Tcp->SendDataLen = tmpindex;
}

void WriteCommand_0FH_10H(ModbusTcp *Tcp)
{
   uint08 tmp = 0;
   uint08 tmpindex = 7;
   uint16 itmp = 0;
   uint16 Address = RegisterStartAddress(Tcp);
   uint16 Number  = RegsisterNumber(Tcp);
   for (tmp = 0; tmp < Number; tmp++)
   {
      itmp = Tcp->ReadData[tmpindex++] * 256; //第七个开始为数据的高位
      itmp += Tcp->ReadData[tmpindex++];
      ModbusWrite((Address + tmp), itmp);
   }
   tmpindex = 0;
   Tcp->SendData[tmpindex++] = Tcp->ReadData[0]; //栈ID
   Tcp->SendData[tmpindex++] = Tcp->ReadData[1]; //功能码
   Tcp->SendData[tmpindex++] = Tcp->ReadData[2]; //寄存器高位地址
   Tcp->SendData[tmpindex++] = Tcp->ReadData[3]; //寄存器低位地址
   Tcp->SendData[tmpindex++] = Tcp->ReadData[4]; //寄存器数量高位
   Tcp->SendData[tmpindex++] = Tcp->ReadData[5]; //寄存器数量低位
   itmp = GetCRC16(Tcp->SendData, 6);           //计算CRC值
   Tcp->SendData[tmpindex++] = itmp % 256;       //CRC 低位在前
   Tcp->SendData[tmpindex++] = itmp / 256;       //CRC 高位在前
   Tcp->SendDataLen = tmpindex;
}

void ModbusDataDeal(ModbusTcp *Tcp)
{
   ModbusErrorEnum Err = NONE_ERR;
   if (Err != SendErrorRepot(Tcp))
   {
      return;
   }
   switch (Tcp->ReadData[1])
   {
   case CMD_0x01:
   case CMD_0x02:
      ReadCommand_01H_02H(Tcp);
      break;
   case CMD_0x03:
   case CMD_0x04:
      ReadCommand_03H_04H(Tcp);
      break;
   case CMD_0x05:
   case CMD_0x06:
      WriteCommand_05H_06H(Tcp);
      break;
   case CMD_0x0F:
   case CMD_0x10:
      WriteCommand_0FH_10H(Tcp);
      break;
   default:
      break;
   }
}


void SlaveModbus(ModbusTcp *Tcp)
{
   UartType *P2data = &UartAppData1;
   if (P2data->Flags.Solo.RecFlame)
   {
      Tcp->ReadDataLen = P2data->RxdCount;
      Tcp->ReadData    = P2data->TxRxBuff;
      Tcp->SendData    = P2data->TxRxBuff;
      Tcp->SendDataLen = 0;
      ModbusDataDeal(Tcp);
      if (Tcp->SendDataLen > 0)
      {
         StartUartSend(P2data, (char *)Tcp->SendData, Tcp->SendDataLen);
      }
      P2data->RxdCount = 0;
      P2data->Flags.All = 0;
   }
}

#define  ___________________master

void modbus(ModbusTcp *Tcp)
{
   if (Tcp->Poll.Flags.Read0Write1)
   {
      switch (Tcp->Poll.Command)
      {
      case CMD_0x01:
         break;
      case CMD_0x02:
         break;
      case CMD_0x03:
         break;
      case CMD_0x04:
         break;
      }
   }
   else
   {
      switch (Tcp->Poll.Command)
      {
      case CMD_0x05:
         break;
      case CMD_0x06:
         break;
      case CMD_0x0F:
         break;
      case CMD_0x10:
         break;
      }
   }
}

void PollModbus(ModbusTcp *Tcp)
{
   UartType *P2data = &UartAppData1;
   if (P2data->MasterTime == 0)
   {
      P2data->MasterTime = 100;

   }
}

#endif
