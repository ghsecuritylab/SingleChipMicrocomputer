



#include "includes.h"

Bit_165_def BIT1;

const uchar addrnum[] = 
{
0,1,2,3,7,6,5,4,8
};

uchar Deal_165Data(void)
{
   uchar i;
   uchar data_buf = 0;
   _165SCLK_0;
   for (i = 0; i < 8; i++)
   {
      data_buf = data_buf << 1;
      _165SCLK_1;
      if (PIND & BIT(5)) //读数据位
      {
	 data_buf |= 0x01;
      }
      _165SCLK_0;
   }
   return (data_buf);   //数据保存在data_buf
}

uchar Read_165Data(void)
{
   uchar Read_Buf;
   _165EN_1; //锁存并行输入数据
   nop;
   nop;
   Read_Buf = Deal_165Data(); //数据保存在Read_Buf
   nop; 
   nop;
   _165EN_0;
   return (Read_Buf);
}


void Scan_165_Deal(uchar keyaddr)
{
   uchar tmp;
   static uchar keyLastRec;
   static uchar keyOut;
   static uchar keyaddrCnt[_MAX_];
   if (!RunFlag.Solo._1ms)
   {
      return;
   }
   for (tmp = 0; addrnum[tmp] < _MAX_; tmp++)
   {
      if ((GetBit(keyaddr, tmp) ^ GetBit(keyLastRec, tmp)) != 0)
      {
         ClrBit(keyOut, addrnum[tmp]);
         keyaddrCnt[tmp] = 0;
      }
      else
      {
         keyaddrCnt[tmp]++;
         if (keyaddrCnt[tmp] >= 20)
         {
            if (GetBit(keyaddr, tmp) != 0)
            {
               SetBit(keyOut, addrnum[tmp]);
            }
            else
            {
               ClrBit(keyOut, addrnum[tmp]);
            }
         }
      }
   }
   keyLastRec = keyaddr;
   BIT1.All = keyOut;
}



