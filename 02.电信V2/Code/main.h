
#ifndef MAIN_H
#define MAIN_H

typedef unsigned char uchar,UCHAR,U8,UINT8,uint08,BYTE,*puchar,*PUCHAR,*PU8,*pu8,*PUINT8,*puint8,*PBYTE,*LPBYTE;
typedef unsigned int  uint16;
typedef unsigned long uint32;
typedef void VOID,*PVOID,*LPVOID;

#define BIT(x)         (1 << x )
#define SetBit(x,y)    (x |= BIT(y)  ) 
#define ClrBit(x,y)    (x &= ~BIT(y) ) 
#define GetBit(x,y)    (x & BIT(y)   ) 


#define CRC_LEN (2)


typedef union
{
   uint16 All[2];
   struct
   {
      uint16 SaveTest;
      uint16 Crc;
   }Solo;
}SaveData;


typedef union
{
   uint16 All;
   struct
   {
      uint16 button4:1;
      uint16 button5:1;
      uint16 button6:1;
      uint16 button7:1;
      uint16 button8:1;
      uint16 button1:1;
      uint16 button2:1;
      uint16 button3:1;
      uint16 DI5 :1;
      uint16 DI6 :1;
      uint16 DI7 :1;
      uint16 DI8 :1;
      uint16 DI1 :1;
      uint16 DI2 :1;
      uint16 DI3 :1;
      uint16 DI4 :1;
   }Solo;
}DI_Def;



typedef union
{
   uint08 All;
   struct
   {
      uint08 DO1:1;
      uint08 DO2:1;
      uint08 DO3:1;
      uint08 DO4:1;
      uint08 nouse1:1;
      uint08 nouse2:1;
      uint08 nouse3:1;
      uint08 nouse4:1;
   }Solo;
}DO_Def;

typedef union
{
   uint08 All[2];
   struct
   {
      uint08 LED_DO_1:1;
      uint08 LED_DO_2:1;
      uint08 LED_DO_3:1;
      uint08 LED_DO_4:1;
      uint08 LED_AO_1:1;
      uint08 LED_AI_2:1;
      uint08 LED_AI_1:1;
      uint08 LED_RUN:1;
      uint08 LED_DI_5:1;
      uint08 LED_DI_6:1;
      uint08 LED_RXD:1;
      uint08 LED_TXD:1;
      uint08 LED_DI_4:1;
      uint08 LED_DI_3:1;
      uint08 LED_DI_2:1;
      uint08 LED_DI_1:1;
   }Solo;
}LED_Def;

typedef union
{
   uint16 All[4];
   struct
   {
      uint16 AI1;
      uint16 AI2;
      uint16 AI3;
      uint16 AI4;
   }Solo;
}AI_Def;

typedef union
{
   uint16 All;
   struct
   {
      uint16 AO1;
   }Solo;
}AO_Def;




typedef struct
{
    DI_Def DI;
    DO_Def DO;
    AI_Def AI;
    AO_Def AO;
    LED_Def Leds;
    SaveData Save;
    uint08 Address;
}DianXin_All_Def;



extern DianXin_All_Def DianXin1;

#endif
