
#include "includes.h"


YYJ_DI_DEF POL_DI_Block;
#define LogicOut POL_DI_Block.uint08All
//u8 LogicOut[6];
u8 InputState[6];
u8 InputStateRec[6];
u8 InputCnt[48];


//将165的8 bit 并行输入 转为串口16进制输出
u8 InputChar()
{
   u8 tmp, result = 0x00;
   for (tmp = 0; tmp < 8; tmp++)
   {
      result <<= 1;    //0000 0010
      if (_165SDOis1)
      {
         result = result | 0x01;
      }
      _165CLKto0;  //下降沿有效
      _165CLKto0;
      _165CLKto1;
   }
   return result;
}



uchar  OtherDi()
{
   Bitsdef tmp;
   tmp.All = 0xFF;
   tmp.Bits.Bit0 = GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9); //急停
   tmp.Bits.Bit1 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0); //远负压
   tmp.Bits.Bit2 = GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_10); //手动冬季
   return (tmp.All);
}






void Input165()
{
   _165PLDto1;
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   InputState[0] = InputChar();
   InputState[1] = InputChar();
   InputState[2] = InputChar();     //和单片机相连的165
   InputState[3] = InputChar();
   InputState[4] = InputChar();
   InputState[5] = OtherDi(); //其它输入也一起处理了
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _nop_();
   _165PLDto0; //PLD为0时 并行置数禁止，串行传输开始
}


const volatile u8 LogicTable[48] =
{
   (1 * 8 + 6), (1 * 8 + 7), (1 * 8 + 4), (1 * 8 + 5), (4 * 8 + 3), (4 * 8 + 2), (4 * 8 + 1), (4 * 8 + 0),

   (5 * 8 + 1), (4 * 8 + 7), (3 * 8 + 4), (3 * 8 + 3), (3 * 8 + 2), (3 * 8 + 1), (5 * 8 + 0), (3 * 8 + 0),

   (5 * 8 + 5), (5 * 8 + 4), (2 * 8 + 7), (5 * 8 + 3), (4 * 8 + 6), (4 * 8 + 5), (4 * 8 + 4), (5 * 8 + 2),

   (1 * 8 + 2), (1 * 8 + 1), (2 * 8 + 4), (2 * 8 + 5), (2 * 8 + 0), (2 * 8 + 1), (2 * 8 + 2), (2 * 8 + 3),

   (0 * 8 + 5), (0 * 8 + 6), (1 * 8 + 0), (0 * 8 + 7), (0 * 8 + 3), (0 * 8 + 2), (0 * 8 + 1), (0 * 8 + 0),

   (0 * 8 + 4), (1 * 8 + 3), (2 * 8 + 6), (7 * 8 + 1), (7 * 8 + 2), (7 * 8 + 3), (7 * 8 + 4), (7 * 8 + 5),
};
//14  15  12  13  35  34  33  32
//41  39  28  27  26  25  40  24
//45  44  23  43  38  37  36  42
//10  09  20  21  16  17  18  19
//05  06  08  07  03  02  01  00
//04  11  22  /*57  58  59  60  61*/
//共43个DI  165有40个 mcu有3个















//extern uint08 ReadBits(uint08 *p2data, uint08 index);
//extern void WriteBits(uint08 *p2data, uint08 index, uint08 bits);


void InputDeal()
{
   u8 tmp = 0;
   u8 tmpbitRec = 0;
   u8 tmpbitNow = 0;

   for (tmp = 0; tmp < 48; tmp++)
   {
      tmpbitRec = ReadBits(InputStateRec, tmp);
      tmpbitNow = ReadBits(InputState, tmp);

      if (tmpbitRec != tmpbitNow)
      {
         InputCnt[tmp] = 0;
      }
      else if (InputCnt[tmp] < 100)
      {
         InputCnt[tmp]++;
      }

      if (InputCnt[tmp] > 15)
      {
         if (tmpbitRec == 0)
         {
            tmpbitRec = 1;
         }
         else
         {
            tmpbitRec = 0;
         }

         WriteBits((u8 *)LogicOut, LogicTable[tmp], tmpbitRec);
      }
   }
   //冬夏转换运算
   if (POL_DI_Block.Solo.SEL_SEASON_WINTER)
   {
      POL_DI_Block.Solo.INPUT_WATER_SENSOR = 1;
   }
   if (POL_DI_Block.Solo.SEL_SEASON_SUMMER)
   {
      POL_DI_Block.Solo.INPUT_WATER_SENSOR = 0;
   }
   InputStateRec[0] = InputState[0];
   InputStateRec[1] = InputState[1];
   InputStateRec[2] = InputState[2];
   InputStateRec[3] = InputState[3];
   InputStateRec[4] = InputState[4];
   InputStateRec[5] = InputState[5];
}















