
#include "includes.h"
#define LogicOut ((uint08 *)&FC1.Buff.DiIn)

//#define PA1_FLOAT_IN do{DDRA &= ~(BIT(1));PORTA &= ~(BIT(1));}while(0)
//#define PA1_PULL_OUT do{PORTA |= (BIT(1));DDRA |= (BIT(1));}while(0)
//#define PA2_FLOAT_IN do{DDRA &= ~(BIT(2));PORTA &= ~(BIT(2));}while(0)
//#define PA2_PULL_OUT do{PORTA |= (BIT(2));DDRA |= (BIT(2));}while(0)

#define PA1_FLOAT_IN do{PORTA_PORTA1 = 0;DDRA_DDA1 = 0;}while(0)
#define PA1_PULL_OUT do{PORTA_PORTA1 = 1;DDRA_DDA1 = 1;}while(0)
#define PA2_FLOAT_IN do{PORTA_PORTA2 = 0;DDRA_DDA2 = 0;}while(0)
#define PA2_PULL_OUT do{PORTA_PORTA2 = 1;DDRA_DDA2 = 1;}while(0)

#define _MAX_DI_ 16
uint08 InputState[2];
uint08 InputStateRec[2];
uint08 InputCnt[8];

void delay_1us(void)
{
   asm("nop");
}

void delay_us(uint16 n)
{
   uint16 i;
   for (i = 0; i < n; i++)
   {
      delay_1us();
   }
}


__flash uint08 LogicTable[_MAX_DI_] =
{
//~~1~~~~2~~~~~3~~~~4~~~~5~~~~~6~~~~7~~~~8~~~
   (0 * 8 + 0), (0 * 8 + 1), (0 * 8 + 2), (0 * 8 + 3), (0 * 8 + 4), (0 * 8 + 5), (0 * 8 + 6), (0 * 8 + 7),
//~~1~~~~2~~~~~3~~~~4~~~~5~~~~~6~~~~7~~~~8~~~
   (1 * 8 + 0), (1 * 8 + 1), (1 * 8 + 2), (1 * 8 + 3), (1 * 8 + 4), (1 * 8 + 5), (1 * 8 + 6), (1 * 8 + 7),
//  (1*8+1),(0*8+6),(1*8+0),(0*8+7),(0*8+5),(1*8+2),(0*8+4),(1*8+3),
//~~1~~~~2~~~~~3~~~~4~~~~5~~~~~6~~~~7~~~~8~~~
//  (2*8+0),(2*8+6),(2*8+5),(2*8+4),(2*8+1),(2*8+2),(2*8+3),(2*8+7),
//~~1~~~~2~~~~~3~~~~4~~~~5~~~~~6~~~~7~~~~8~~~
//  (3*8+4),(3*8+5),(3*8+6),(3*8+7),(3*8+3),(3*8+2),(3*8+1),(3*8+0),
//~~1~~~~2~~~~~3~~~~4~~~~5~~~~~6~~~~7~~~~8~~~
//  (4*8+0),(4*8+1),(4*8+2),(4*8+3),(4*8+4),(4*8+5),(4*8+6),(4*8+7),
};

uchar  OtherDi()
{
   Bitsdef tmp;
   tmp.All = 0;
   tmp.Bits.Bit7 = PINC_PINC5; //8 Addr Input
   tmp.Bits.Bit6 = PINC_PINC4;
   tmp.Bits.Bit5 = PINC_PINC3;
   tmp.Bits.Bit4 = PINC_PINC2;
   tmp.Bits.Bit3 = PINC_PINC1;
   tmp.Bits.Bit2 = PINC_PINC0;
   tmp.Bits.Bit1 = PING_PING1;
   tmp.Bits.Bit0 = PING_PING0;
   return (tmp.All);
}


uchar  OtherDi2()
{
   Bitsdef tmp;
   tmp.All = 0;
   tmp.Bits.Bit7 = PINB_PINB6; //L
   tmp.Bits.Bit6 = PINB_PINB4; //M
// tmp.Bits.Bit5 = PINB_PINB0; //H
//  tmp.Bits.Bit4 = PINC_PINC1;
//  tmp.Bits.Bit3 = PINC_PINC0;
//  tmp.Bits.Bit2 = PIND_PIND6;
//  tmp.Bits.Bit1 = PIND_PIND4;
//  tmp.Bits.Bit0 = PIND_PIND3;
   return (tmp.All);
}

uint08 InputCntDeal(uint08 chnr)
{
   uint08 tmp = chnr;
   if ((chnr & 0x3F) >= _MAX_DI_)
   {
      return 0;
   }
   if (tmp & INPUT_CLR) //clr
   {
      tmp = (chnr & 0x3F);
      if (!GetBit(tmp, 0)) //LowHalfByte
      {
         InputCnt[tmp / 2] &= 0xF0;
      }
      else
      {
         InputCnt[tmp / 2] &= 0x0F;
      }
   }
   else if (tmp & INPUT_INQ) //inquiring
   {
      tmp = chnr & 0x3F;
      if (GetBit(tmp, 0) == 0x00) //LowHalfByte
      {
         tmp = (InputCnt[tmp / 2] & 0x0F);
      }
      else
      {
         tmp = (InputCnt[tmp / 2] / 16);
      }

      //result
      if (tmp > 10)
      {
         return 1;
      }
      else
      {
         return 0;
      }
   }
   else //+1
   {
      tmp = chnr & 0x3F;
      if (!GetBit(chnr, 0)) //LowHalfByte
      {
         if ((InputCnt[tmp / 2] & 0x0F) < 15)
         {
            InputCnt[tmp / 2]++;
         }
      }
      else
      {
         if (InputCnt[tmp / 2] < 240)
         {
            InputCnt[tmp / 2] += 16;
         }
      }
   }
   return 0;
}

void InputDeal()
{
   uint08 tmp1 = 0;
   uint08 tmp2 = 0;
   uint08 tmp3 = 0;
   uint08 tmp4 = 0;
   uint08 tmp5 = 0;
   InputState[0] =  OtherDi();
   InputState[1] =  OtherDi2();
   for (tmp1 = 0; tmp1 < _MAX_DI_; tmp1++)
   {
      tmp2 = tmp1 / 8;
      tmp3 = tmp1 % 8;
      tmp4 = InputState[tmp2] & (1 << tmp3);
      tmp5 = InputStateRec[tmp2] & (1 << tmp3);
      if (tmp5 == tmp4)
      {
         //ADD
         InputCntDeal(tmp1);
      }
      else
      {
         InputCntDeal(tmp1 | INPUT_CLR);
      }

      if (InputCntDeal(tmp1 | INPUT_INQ) > 0)
      {
         if (tmp5 == 0)
         {
            tmp2 = 1;
         }
         else
         {
            tmp2 = 0;
         }
         WriteBits(LogicOut, LogicTable[tmp1], tmp2);
      }
   }
   InputStateRec[0] = InputState[0];
   InputStateRec[1] = InputState[1];
   FC1.State.DI = FC1.Buff.DiIn;
}





















