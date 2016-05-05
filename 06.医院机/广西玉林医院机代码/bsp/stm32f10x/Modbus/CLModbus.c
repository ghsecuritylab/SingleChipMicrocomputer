#include "Includes.h"



uint16 MyMdAddr = 0x33;
MdErrEnum MdDataDeal(Md_Tcp_Dep *Tcp)
{

   MdErrEnum ret;
//  1. ��ַ�ж�
#define MD_DEV_ADDR_CHK
   ret = (*Tcp->AddrCheck)((Md_Tcp_SameDep *)Tcp);
   if (ret != MD_ERR_OK)
   {
      return ret;
   }
//  2. �ж�����
#define MD_CMD_CHK
   if (Tcp->RawData[MD_DEV_CMD_INDEX] != MD_CMD_WRP &&
       Tcp->RawData[MD_DEV_CMD_INDEX] != MD_CMD_WR &&
       Tcp->RawData[MD_DEV_CMD_INDEX] != MD_CMD_RD)
   {
      return MD_CMD_ERR;
   }
//  3. �ж�CRC
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
//  3. �жϰ��ܳ���
   if (Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_WRP ||
       Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_WR)
   {
#define MD_WRITINGING_TOTAL_CHK
      if (Tcp->RawDataLen == MD_SHORT_CMD_LEN)
      {
         ;
      }
      else if (Tcp->RawDataLen == (MD_0X10_EXTRA_BYTE + Tcp->RawData[MD_0X03_TRG_NUM_INDEX]) &&
               (Tcp->RawData[MD_0X03_TRG_NUM_INDEX] == (Tcp->RawData[MD_0X03_TRG_NUM_INDEX - 1] * 2)))
      {
         ;
      }
      else
      {
         return  MD_WRITE_TOTAL_LEN_ERR;
      }
   }
   else
   {
#define MD_READING_TOTAL_CHK
      if (Tcp->RawDataLen == MD_SHORT_CMD_LEN)
      {
         ;
      }
      else if (Tcp->RawDataLen == (MD_0X03_EXTRA_BYTE + Tcp->RawData[MD_0X03_RSP_NUM_INDEX]))
      {
         ;
      }
      else
      {
         return  MD_READ_TOTAL_LEN_ERR;
      }
   }



//  4. �ж������
#define MD_LEN_CHK_SHORT
   if (Tcp->RawDataLen == MD_SHORT_CMD_LEN)
   {
      if (Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_WRP ||
          Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_WR)
      {
         //NO ECHO
	 return  MD_ERR_OK;
      }
      else
      {
#define MD_READING_RSP
         uint16 trgaddr   = Tcp->RawData[MD_0X10_TRG_ADDR_INDEX] * 256 + Tcp->RawData[MD_0X10_TRG_ADDR_INDEX + 1];
         uint16 length     = Tcp->RawData[MD_0X10_TRG_LEN_INDEX + 1];

         ret = (*Tcp->LenChkCheck)(trgaddr, length,Tcp->RawData[MD_DEV_ADDR_INDEX]);
                 if(ret != MD_ERR_OK)
                 {
                    return ret;
                 }

         // Data Setup
         Tcp->rePkglen = Slave_ModbusDataSetup(Tcp);
         return  MD_ERR_OK;
      }
   }

//  5. ����Ҫ�ظ�
#define MD_LEN_CHK_LONG
   if (Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_WRP ||
       Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_WR)
   {
      //slave data deal
#define SLAVE_DATA_DEAL

      uint16 trgaddr   = Tcp->RawData[MD_0X10_TRG_ADDR_INDEX] * 256 + Tcp->RawData[MD_0X10_TRG_ADDR_INDEX + 1]; //2,3��ַ
      uint16 length     = Tcp->RawData[MD_0X10_TRG_LEN_INDEX] * 256 + Tcp->RawData[MD_0X10_TRG_LEN_INDEX + 1]; // 4,5д�Ĵ���������

      ret = (*Tcp->LenChkCheck)(trgaddr, length,Tcp->RawData[MD_DEV_ADDR_INDEX]);
      if (ret != MD_ERR_OK)
      {
         return ret;
      }
      //���ݴ���
      #define DATA_WRITING
      if (Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_WRP)
      {
         uint16 itmp;
         uint16 tmpindex = MD_MST_DATA_INDEX;
         uint08 tmp;
         for (tmp = 0; tmp < length; tmp++) //����
         {
            itmp = Tcp->p2trg[tmpindex++] * 256;
            itmp += Tcp->p2trg[tmpindex++];
            (*Tcp->WrData)((trgaddr + tmp), itmp,Tcp->RawData[MD_DEV_ADDR_INDEX]);
         }
      }
      
/***************************************************/
      if (Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_WR)
      {
         (*Tcp->WrData)(trgaddr, length,Tcp->RawData[MD_DEV_ADDR_INDEX]);
      }
/***************************************************/
      //����,д����,�ظ�һ���̻ظ�
      Tcp->rePkglen = Slave_ModbusDataSetup(Tcp);
      return  MD_ERR_OK;
   }
   else
   {
      //����,������,����Ҫ�ظ�
      //����,����������,����Ҫ�ظ�
      //�ж��ǲ����Լ��շ���ȥ�Ķ�����
      if (Tcp->RawData[MD_DEV_ADDR_INDEX] != Tcp->NowPoll.Addr)
      {
         return  MD_ERR_RSP_ID_ERR;
      }
      if (Tcp->RawData[MD_DEV_RSP_DATA_LEN_INDEX] != (Tcp->NowPoll.DataToRead) * 2)
      {
         return  MD_ERR_RSP_DATALEN_ERR;
      }

      if (1)
      {
         uint16 itmp;
         uint08 tmp;
         uint16 tmpindex = MD_MST_RSP_DATA_INDEX;
         uint16 trgaddr = Tcp->NowPoll.StartAddr;
         uint16 length = Tcp->RawData[MD_DEV_RSP_DATA_LEN_INDEX] / 2;

         for (tmp = 0; tmp < length; tmp++)
         {
            itmp = Tcp->RawData[tmpindex++] * 256;
            itmp += Tcp->RawData[tmpindex++];
            Tcp->WrData(trgaddr + tmp, itmp,Tcp->RawData[MD_DEV_ADDR_INDEX]);
         }
      }

      return  MD_ERR_OK;
   }
}

uint16  Slave_ModbusDataSetup(Md_Tcp_Dep *Tcp)
{
   uint08 tmp;
   uint08 tmpindex;
   uint16 itmp;

   //  1. �������
#if 0
   for (itmp = 0; itmp < MD_UART_MAX_LEN; itmp++)
   {
      Tcp->p2trg[itmp] = 0;
   }
#endif
   //  2. �ж�����
#define _MODBUSANSWER_0X10
   if (Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_WRP)
   {
      Tcp->p2trg[0] = Tcp->RawData[0]; //ջID
      Tcp->p2trg[1] = Tcp->RawData[1]; //������
      Tcp->p2trg[2] = Tcp->RawData[2]; //��ַ��λ
      Tcp->p2trg[3] = Tcp->RawData[3]; //��ַ��λ
      Tcp->p2trg[4] = Tcp->RawData[4]; //д�Ĵ���������λ
      Tcp->p2trg[5] = Tcp->RawData[5]; //д�Ĵ���������λ
      itmp = GetCRC16(Tcp->p2trg, 6);
      Tcp->p2trg[6] = itmp % 256;        //CRC ��λ��ǰ
      Tcp->p2trg[7] = itmp / 256;        //CRC ��λ��ǰ
      return MD_SHORT_CMD_LEN;
   }
/****************************************/

#define _MODBUSANSWER_0X06
   if (Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_WR) //06
   {
      Tcp->p2trg[0] = Tcp->RawData[0]; //ջID
      Tcp->p2trg[1] = Tcp->RawData[1]; //������
      Tcp->p2trg[2] = Tcp->RawData[2]; //��ַ��λ
      Tcp->p2trg[3] = Tcp->RawData[3]; //��ַ��λ
      Tcp->p2trg[4] = Tcp->RawData[4]; //д������ݸ�λ
      Tcp->p2trg[5] = Tcp->RawData[5]; //д������ݵ�λ
      itmp = GetCRC16(Tcp->p2trg, 6);
      Tcp->p2trg[6] = itmp % 256;
      Tcp->p2trg[7] = itmp / 256;
      return MD_SHORT_CMD_LEN;
   }




/****************************************/
#define _MODBUSANSWER_0X03
   if (Tcp->RawData[MD_DEV_CMD_INDEX] == MD_CMD_RD)
   {
      uint16 trgaddr   = Tcp->RawData[MD_0X10_TRG_ADDR_INDEX] * 256 + Tcp->RawData[MD_0X10_TRG_ADDR_INDEX + 1]; //��ַ�ߵ�λ
      uint16 length     = Tcp->RawData[MD_0X10_TRG_LEN_INDEX + 1]; //���Ĵ���������

      Tcp->p2trg[0] = Tcp->RawData[0]; //ջID
      Tcp->p2trg[1] = Tcp->RawData[1]; //������
      Tcp->p2trg[2] = Tcp->RawData[MD_0X03_TRG_LEN_INDEX + 1] * 2; //���Ĵ���������*2=���ݳ���

      tmpindex = 3;
      for (tmp = 0; tmp < length; tmp++) //���ؼĴ�����ֵ
      {
         itmp = (*Tcp->RdData)(trgaddr + tmp,Tcp->RawData[MD_DEV_ADDR_INDEX]);
         Tcp->p2trg[tmpindex++] = itmp / 256;
         Tcp->p2trg[tmpindex++] = itmp % 256;
      }
      itmp = GetCRC16(Tcp->p2trg, tmpindex);
      Tcp->p2trg[tmpindex++] = itmp % 256; //CRC ��λ��ǰ
      Tcp->p2trg[tmpindex++] = itmp / 256; ; //CRC ��λ��ǰ
      return tmpindex;
   }
   return MD_NULL_ERROR;
}




uint16  Master_ModbusDataSetup(Md_Tcp_Dep *Tcp)
{
   uint16 tmp;
   uint16 tmpindex;
   uint16 itmp;
   uint16 length;
   //  1. �������
   //
   //  2. �ж�����
   //WR1RD0
#define _MODBUS_MASTER_0X03

   if (Tcp->NowPoll.Flags & MD_POLL_RD)
   {
      Tcp->p2trg[0] = Tcp->NowPoll.Addr;           //��ַ
      Tcp->p2trg[1] = MD_CMD_RD;                   //����
      Tcp->p2trg[2] = Tcp->NowPoll.StartAddr / 256;
      Tcp->p2trg[3] = Tcp->NowPoll.StartAddr % 256;
      Tcp->p2trg[4] = 0x00;
      Tcp->p2trg[5] = Tcp->NowPoll.DataToRead;
      itmp = GetCRC16(Tcp->p2trg, 6);
      Tcp->p2trg[6] = itmp % 256; //CRC ��λ��ǰ
      Tcp->p2trg[7] = itmp / 256;; //CRC ��λ��ǰ
      return MD_SHORT_CMD_LEN;
   }

#define _MODBUS_MASTER_0X10
   else
   {
      Tcp->p2trg[0] = Tcp->NowPoll.Addr; //��ַ
      Tcp->p2trg[1] = MD_CMD_WRP;            //����
      Tcp->p2trg[2] = Tcp->NowPoll.StartAddr / 256;
      Tcp->p2trg[3] = Tcp->NowPoll.StartAddr % 256;
      Tcp->p2trg[4] = 0x00;
      Tcp->p2trg[5] = Tcp->NowPoll.DataToRead;
      Tcp->p2trg[6] = Tcp->NowPoll.DataToRead * 2;

      length = Tcp->p2trg[5];
      tmpindex = 7;
      if (Tcp->RdData != NULL)
      {
         for (tmp = 0; tmp < length; tmp++)
         {
            itmp = Tcp->RdData(Tcp->NowPoll.StartAddr + tmp,Tcp->RawData[MD_DEV_ADDR_INDEX]);
            Tcp->p2trg[tmpindex++] = itmp / 256;
            Tcp->p2trg[tmpindex++] = itmp % 256;
         }
      }
      else
      {
         Tcp->p2trg[tmpindex++] = 0 / 256;
         Tcp->p2trg[tmpindex++] = 0 % 256;
      }
      itmp = GetCRC16(Tcp->p2trg, tmpindex);
      Tcp->p2trg[tmpindex++] = itmp % 256; //CRC ��λ��ǰ
      Tcp->p2trg[tmpindex++] = itmp / 256; //CRC ��λ��ǰ
      return tmpindex;
   }
//   return 0;
}

































