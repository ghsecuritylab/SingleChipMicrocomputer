

#include "includes.h"


Md_Tcp_Dep MdTcp1;

//MdErrEnum MdAddrCheck(void *pData)
//{
//  Md_Tcp_Dep *Tcp = pData;
//  while (Tcp->RawData[0] != 1)
//   {
//      Tcp->RawData++;
//      Tcp->RawDataLen--;
//      if (Tcp->RawDataLen < 8)
//      {
//         break;
//      }
//   }
//   if (Tcp->RawDataLen >= 8)
//   {
//      return MD_ERR_OK;
//   }
//   else
//   {
//      return MD_DEV_ADDR_ERR;
//   }
//}
uint08 MdRegArea(Md_Tcp_Dep *Tcp)
{
   if (Tcp->RawData[1] == 0x01 || Tcp->RawData[1] == 0x05 || Tcp->RawData[1] == 0x0f)
   {
      return 1;
   }
   if (Tcp->RawData[1] == 0x02)
   {
      return 2;
   }
   if (Tcp->RawData[1] == 0x04)
   {
      return 3;
   }
   if (Tcp->RawData[1] == 0x03 || Tcp->RawData[1] == 0x06 || Tcp->RawData[1] == 0x10)
   {
      return 4;
   }
   return 0;
}

MdErrEnum MdDataDeal(Md_Tcp_Dep *Tcp)
{
   MdErrEnum ret;
   //1. ��ַ�ж�
#define MD_DEV_ADDR_CHK
   if (Tcp->RawData[0] != 0x01 && Tcp->RawData[0] != 0x02)
   {
      return MD_DEV_ADDR_ERR;
   }
   //2. �ж������Լ����ڼĴ�����
#define MD_CMD_CHK
   if (Tcp->RawData[1] != 0x01 && Tcp->RawData[1] != 0x02 &&
       Tcp->RawData[1] != 0x03 && Tcp->RawData[1] != 0x04 &&
       Tcp->RawData[1] != 0x05 && Tcp->RawData[1] != 0x06 &&
       Tcp->RawData[1] != 0x0f && Tcp->RawData[1] != 0x10)
   {
       return MD_CMD_ERR;
   }
   else
   {
      Tcp->RegArea = MdRegArea(Tcp);
   }
//3. �ж�CRC
#define MD_CRC_CHK
   if (1)
   {
      uint16 tmpCRC1 = GetCRC16(Tcp->RawData, Tcp->RawDataLen - 2);
      uint16 tmpCRC2 = Tcp->RawData[Tcp->RawDataLen - 1] * 256 + Tcp->RawData[Tcp->RawDataLen - 2];
      if (tmpCRC1 != tmpCRC2)
      {
         return  MD_CRC_ERR;
      }
   }
   //4. �жϰ��ܳ���
   if (Tcp->RawData[1] == 0x05 || Tcp->RawData[1] == 0x06 ||
       Tcp->RawData[1] == 0x10 || Tcp->RawData[1] == 0x0F)
   {
#define MD_WRITINGING_TOTAL_CHK
      if (Tcp->RawDataLen == 8)
      {
         ; //Wirte One Data 0x05 0x06
      }
      else if (Tcp->RawDataLen == (9 + Tcp->RawData[6]) && (Tcp->RawData[6] == (Tcp->RawData[5] * 2)))
      {
         ; //Witer More Data 0x10
      }
      else if ((Tcp->RawDataLen == (9 + Tcp->RawData[6])) &&
               (Tcp->RawData[5] <= (Tcp->RawData[6] * 8)) &&
               (Tcp->RawData[5] >  (Tcp->RawData[5] * 8)))
      {
         ; //Witer More Data 0x0F
      }
      else
      {
         return  MD_WRITE_TOTAL_LEN_ERR;
      }
   }
#define MD_READING_TOTAL_CHK
   else
   {
      if (Tcp->RawDataLen == 8)
      {
         ; //Return Read One Data
      }
      else if (Tcp->RawDataLen == (5 + Tcp->RawData[2]))
      {
         ; //Return Read More Data
      }
      else
      {
         return  MD_READ_TOTAL_LEN_ERR;
      }
   }
   //5. �ж������
#define MD_LEN_CHK_SHORT
   if (Tcp->RawDataLen == 8) //������ʱ����д��̶�����Ϊ8,д����ʱ�ӻ�Ӧ��̶�����Ϊ8
   {
      if (Tcp->RawData[1] == 0x01 || Tcp->RawData[1] == 0x02 ||
          Tcp->RawData[1] == 0x03 || Tcp->RawData[1] == 0x04)
      {
         Tcp->rePkglen = Slave_ModbusDataSetup(Tcp);
         return MD_ERR_OK;
      }
      if (Tcp->RawData[1] == 0x05 || Tcp->RawData[1] == 0x06 ||
	  Tcp->RawData[1] == 0x0F || Tcp->RawData[1] == 0x10)
      {
	 ;
      }
   }
   //6. ����Ҫ�ظ�
#define MD_LEN_CHK_LONG
   if (Tcp->RawData[1] == 0x05 || Tcp->RawData[1] == 0x06 ||
       Tcp->RawData[1] == 0x0F || Tcp->RawData[1] == 0x10)
   {
#define SLAVE_DATA_DEAL
      uint16 trgaddr   = Tcp->RawData[2] * 256 + Tcp->RawData[3];
      uint16 length     = Tcp->RawData[4] * 256 + Tcp->RawData[5];
      ret = (*Tcp->LenChkCheck)(trgaddr, length);
      if (ret != MD_ERR_OK)
      {
         return ret;
      }
      //���ݴ���
#define DATA_WRITING
      if (Tcp->RawData[1] == 0x05 || Tcp->RawData[1] == 0x06)
      {
         uint16 itmp;
         uint16 tmpindex = 4;
         uint08 tmp = 0;
         itmp = Tcp->p2trg[tmpindex++] * 256;
         itmp += Tcp->p2trg[tmpindex++];
         (*Tcp->WrData)((trgaddr + tmp), itmp);
      }
      if (Tcp->RawData[1] == 0x0F || Tcp->RawData[1] == 0x10)
      {
         uint16 itmp;
         uint16 tmpindex = 7;
         uint08 tmp;
         for (tmp = 0; tmp < length; tmp++)
         {
            itmp = Tcp->p2trg[tmpindex++] * 256;
            itmp += Tcp->p2trg[tmpindex++];
            (*Tcp->WrData)((trgaddr + tmp), itmp);
         }
      }
      //����,д����,�ظ�һ���̻ظ�
      Tcp->rePkglen = Slave_ModbusDataSetup(Tcp);
      return  MD_ERR_OK;
   }
   else
   {
#if 1
      //����,����������,����Ҫ�ظ�
//    if (Tcp->RawData[0] != Tcp->Poll.AddrID)
//    {
//       return  MD_LEN_ERR;
//    }
//      if (1)
//      {
//         ;
//      }
      return  MD_ERR_OK;
#else


#endif
   }
}

uint16  Slave_ModbusDataSetup(Md_Tcp_Dep *Tcp)
{
   uint08 tmp;
   uint08 tmpindex;
   uint16 itmp;
   uint08 tmpBit = 0;
   //  1. �������
#if 0
   for (itmp = 0; itmp < MD_UART_MAX_LEN; itmp++)
   {
      Tcp->p2trg[itmp] = 0;
   }
#endif
   //  2. �ж�����
#define _MODBUSANSWER_0X01
#define _MODBUSANSWER_0x02
   if (Tcp->RawData[1] == 0x01 || Tcp->RawData[1] == 0x02)
   {
      uint16 trgaddr = Tcp->RawData[2] * 256 + Tcp->RawData[3];
      uint16 length  = Tcp->RawData[5];
      Tcp->p2trg[0] = Tcp->RawData[0];
      Tcp->p2trg[1] = Tcp->RawData[1];
      if (length % 8 == 0)
      {
         Tcp->p2trg[2] = length / 8;
      }
      else
      {
         Tcp->p2trg[2] = length / 8 + 1;
      }
      tmpindex = 3;
      for (tmp = 0; tmp < length; tmp++)
      {
         itmp = (*Tcp->RdData)(trgaddr + tmp);
         if (itmp > 0)
         {
            SetBit(Tcp->p2trg[tmpindex], tmpBit);
         }
         if (++tmpBit >= 8)
         {
            tmpBit = 0;
            tmpindex++;
            Tcp->p2trg[tmpindex] = 0;
         }
      }
      if (tmpBit != 0)
      {
         tmpindex++;
      }
      itmp = GetCRC16(Tcp->p2trg, tmpindex);
      Tcp->p2trg[tmpindex++] = itmp % 256;
      Tcp->p2trg[tmpindex++] = itmp / 256;
      return tmpindex;
   }
#define _MODBUSANSWER_0X03
#define _MODBUSANSWER_0X04
   if (Tcp->RawData[1] == 0x03 || Tcp->RawData[1] == 0x04)
   {
      uint16 trgaddr = Tcp->RawData[2] * 256 + Tcp->RawData[3];
      uint16 length  = Tcp->RawData[5];
      if (Tcp->RawData[1] == 1)
      {
         return 0;
      }
      Tcp->p2trg[0] = Tcp->RawData[0];
      Tcp->p2trg[1] = Tcp->RawData[1];
      Tcp->p2trg[2] = Tcp->RawData[5] * 2;

      tmpindex = 3;
      for (tmp = 0; tmp < length; tmp++)
      {
         itmp = (*Tcp->RdData)(trgaddr + tmp);
         Tcp->p2trg[tmpindex++] = itmp / 256;
         Tcp->p2trg[tmpindex++] = itmp % 256;
      }
      itmp = GetCRC16(Tcp->p2trg, tmpindex);
      Tcp->p2trg[tmpindex++] = itmp % 256;
      Tcp->p2trg[tmpindex++] = itmp / 256;
      return tmpindex;
   }
#define _MODBUSANSWER_0X05
#define _MODBUSANSWER_0x06
#define _MODBUSANSWER_0x0F
#define _MODBUSANSWER_0x10
   if (Tcp->RawData[1] == 0x05 || Tcp->RawData[1] == 0x06 ||
       Tcp->RawData[1] == 0x0F || Tcp->RawData[1] == 0x10)
   {
      Tcp->p2trg[0] = Tcp->RawData[0]; //ջID
      Tcp->p2trg[1] = Tcp->RawData[1]; //������
      Tcp->p2trg[2] = Tcp->RawData[2]; //�Ĵ�����λ��ַ
      Tcp->p2trg[3] = Tcp->RawData[3]; //�Ĵ�����λ��ַ
      Tcp->p2trg[4] = Tcp->RawData[4]; //�Ĵ���������λ
      Tcp->p2trg[5] = Tcp->RawData[5]; //�Ĵ���������λ
      itmp = GetCRC16(Tcp->p2trg, 6); //����CRCֵ
      Tcp->p2trg[6] = itmp % 256;      //CRC ��λ��ǰ
      Tcp->p2trg[7] = itmp / 256;      //CRC ��λ��ǰ
      return 8;
   }
   return MD_NULL_ERROR;
}


//uint16  Master_ModbusDataSetup(Md_Tcp_Dep *Tcp)
//{
//   uint16 tmp;
//   uint16 tmpindex;
//   uint16 itmp;
//   uint16 length;
//   //  1. �������
//#if 0
//   for (itmp = 0; itmp < MD_UART_MAX_LEN; itmp++)
//   {
//      Tcp->p2trg[itmp] = 0;
//   }
//#endif
//   //  2. �ж�����
//   //WR1RD0
//#define _MODBUS_MASTER_0X03
//
//   if (Tcp->Poll.Flags.Solo.WR1RD0)
//   {
//      Tcp->p2trg[0] = Tcp->Poll.AddrID;        //��ַ
//      Tcp->p2trg[1] = 0x03;                    //����
//      Tcp->p2trg[2] = Tcp->Poll.AddrReg / 256; //�Ĵ�����ַ��λ
//      Tcp->p2trg[3] = Tcp->Poll.AddrReg % 256; //�Ĵ�����ַ��λ
//      Tcp->p2trg[4] = Tcp->Poll.RegNum / 256;  //�Ĵ���������λ
//      Tcp->p2trg[5] = Tcp->Poll.RegNum % 256;  //�Ĵ���������λ
//      itmp = GetCRC16(Tcp->p2trg, 6);         //CRCУ��
//      Tcp->p2trg[6] = itmp % 256;              //CRC��λ��ǰ
//      Tcp->p2trg[7] = itmp / 256;              //CRC��λ��ǰ
//      return 8;
//   }
//
//#define _MODBUS_MASTER_0X10
//   else
//   {
//      Tcp->p2trg[0] = Tcp->Poll.AddrID;         //��ַ
//      Tcp->p2trg[1] = 0x10;                     //����
//      Tcp->p2trg[2] = Tcp->Poll.AddrReg / 256;  //
//      Tcp->p2trg[3] = Tcp->Poll.AddrReg % 256;  //
//      Tcp->p2trg[4] = Tcp->Poll.RegNum / 256;   //
//      Tcp->p2trg[5] = Tcp->Poll.RegNum % 256;   //
//      Tcp->p2trg[6] = Tcp->Poll.RegNum;         //
//
////      length = Tcp->p2trg[5];
////      tmpindex = 7;
////      if (Tcp->RdData != NULL)
////      {
////         for (tmp = 0; tmp < length; tmp++)
////         {
////            itmp = Tcp->RdData(Tcp->NowPoll.StartAddr + tmp,Tcp->RawData[MD_DEV_ADDR_INDEX]);
////            Tcp->p2trg[tmpindex++] = itmp / 256;
////            Tcp->p2trg[tmpindex++] = itmp % 256;
////         }
////      }
////      else
////      {
////         Tcp->p2trg[tmpindex++] = 0 / 256;
////         Tcp->p2trg[tmpindex++] = 0 % 256;
////      }
////      itmp = GetCRC16(Tcp->p2trg, tmpindex);
////      Tcp->p2trg[tmpindex++] = itmp % 256; //CRC ��λ��ǰ
////      Tcp->p2trg[tmpindex++] = itmp / 256; //CRC ��λ��ǰ
////      return tmpindex;
//   }
//
//}


