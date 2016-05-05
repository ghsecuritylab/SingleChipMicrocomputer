
#include "Includes.h"




uint16 GetCRC16(uint08 *ptr, uint08 len)
{
   uint16 crc = 0xffff;
   uint08  tmp;
   const uint16 CRCtbl[16] =  /* CRC余式表 */
   {
      0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401,
      0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400
   };

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

//STM32的CRC
uint32 GetCRC32(uint08 *pBuf, uint16 nSize)
{
   uint32 index = 0;
   UINT32T04BYTE tmp;
   CRC_ResetDR();        //复位CRC


   for (index = nSize; index >= 4;)
   {
      tmp.Bytes.BYTE1 = *pBuf++;
      tmp.Bytes.BYTE2 = *pBuf++;
      tmp.Bytes.BYTE3 = *pBuf++;
      tmp.Bytes.BYTE4 = *pBuf++;
      CRC->DR = tmp.All;
      index = index - 4;
   }

   if (index == 3)
   {
      tmp.Bytes.BYTE1 = *pBuf++;
      tmp.Bytes.BYTE2 = *pBuf++;
      tmp.Bytes.BYTE3 = *pBuf++;
      tmp.Bytes.BYTE4 = 0x00;
      CRC->DR = tmp.All;
   }
   else if (index == 2)
   {
      tmp.Bytes.BYTE1 = *pBuf++;
      tmp.Bytes.BYTE2 = *pBuf++;
      tmp.Bytes.BYTE3 = 0x00;
      tmp.Bytes.BYTE4 = 0x00;
      CRC->DR = tmp.All;
   }
   else if (index == 1)
   {
      tmp.Bytes.BYTE1 = *pBuf++;
      tmp.Bytes.BYTE2 = 0x00;
      tmp.Bytes.BYTE3 = 0x00;
      tmp.Bytes.BYTE4 = 0x00;
      CRC->DR = tmp.All;
   }

   return (CRC->DR);
}
