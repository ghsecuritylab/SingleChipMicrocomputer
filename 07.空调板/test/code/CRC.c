
#include "includes.h"



__flash uint16 CRCtbl[16] =  /* CRCÓàÊ½±í */
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


