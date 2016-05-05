
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


#define MODULE_1 100
#define MODULE_2 200
#define MODULE_3 300
#define MODULE_4 400
#define MODULE_5 500
#define MODULE_6 600

#define CRC_LEN (2)


typedef struct
{
   uint16 Save1;
   uint16 Addr485;
   uint16 Crc;
}Module_Save;


typedef union
{
   uint08 All;
   struct {
      uint08 DI1:1;
      uint08 DI2:1;
      uint08 DI3:1;
      uint08 DI4:1;
      uint08 nouse:4;
   }Solo;
}Module_DI_Def;

typedef union
{
   uint08 All;
   struct {
      uint08 DO1:1;
      uint08 DO2:1;
      uint08 DO3:1;
      uint08 DO4:1;
      uint08 LED1:1;
      uint08 LED2:1;
      uint08 nouse:2;
   }Solo;
}Module_DO_Def;

typedef union
{
   uint16 All[6];
   struct {
      uint16 AI1;
      uint16 AI2;
      uint16 AI3;
      uint16 AI4;
      uint16 AI5;
      uint16 AI6;
   }Solo;
}Module_AI_Def;

typedef union
{
   uint16 All[4];
   struct {
      uint16 AO1;
      uint16 AO2;
      uint16 AO3;
      uint16 AO4;
   }Solo;
}Module_AO_Def;




typedef struct
{
   Module_DI_Def DI;
   Module_DO_Def DO;
   Module_AI_Def AI;
   Module_AO_Def AO;
   Module_Save SaveData;
   uint08 Test;
}Module_All_Def;



extern Module_All_Def MODE1;
void PrintString(const char *fmt, ...);



#endif
