
#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef char CHAR,INT8,int8,S8,*PCHAR,*pchar,*PINT8,*pint8,*PS8,*ps8,*LPSTR;
typedef const char *LPCSTR;
typedef unsigned char uchar,UCHAR,U8,UINT8,uint8,uint08,BYTE,*puchar,*PUCHAR,*PU8,*pu8,*PUINT8,*puint8,*PBYTE,*LPBYTE;
typedef short SHORT,INT16,int16,*PSHORT,*pshort,*PINT16,*pint16,*PWCHAR,*S16,*pwchar,*PWORD,*pword;
typedef unsigned short WORD,word,USHORT,ushort,UINT16,uint16,U16,*PUSHORT,*pushort,*PUINT16,*puint16,*PU16,*pu16;
typedef unsigned short WCHAR;
typedef int INT,*PINT,*pint;
typedef unsigned int UINT,uint,*PUINT,*puint,*PUINT32,*puint32,*PU32,*pu32;
typedef long LONG,*PLONG,*plong,INT32,int32,S32,DWORD,dword,*PINT32,*pint32,*PS32,*ps32,*PDWORD,*pdword;
typedef unsigned long ULONG,ulong,*PULONG,*pulong,UINT32,uint32,U32;
typedef void VOID,*PVOID,*LPVOID;
typedef unsigned char BOOLEAN,BOOL,*PBOOL;


typedef union
{
   uint08 All[2];
   struct {
      uint08 _1msFlag   :1;
      uint08 _5msFlag   :1;
      uint08 _10msFlag  :1;
      uint08 _20msFlag  :1;
      uint08 _50msFlag  :1;
      uint08 _100msFlag :1;
      uint08 _1000msFlag:1;
      uint08 _5000msFlag:1;
      uint08 Blink      :1;
      uint08 FastBlink  :1;
      uint08 nouse      :6;
   }Solo;
}TimerFlags;


typedef union
{
   uint08 All;
   struct {
      uint08 LedRunning:1;
      uint08 LedStadby:1;
      uint08 LedError:1;
      uint08 LedEfficient:1;
      uint08 LedNgt:1;
      uint08 Lednouse:3;
   }Solo;
}LedShow;


typedef union
{
   uint16 All;
   struct {
      uint16 KeyRun:1;
      uint16 KeyStadby:1;
      uint16 KeyNgt:1;
      uint16 KeyBackup:1;
      uint16 KeyTmepAdd:1;
      uint16 KeyTmepSub:1;
      uint16 KeyRhAdd:1;
      uint16 KeyRhSub:1;
      uint16 KeySetting:1;
      uint16 KeyNouse:7;
   }Solo;
}KeyState;


typedef union
{
   uint08 All;
   struct {
      uint08 SEG_A:1;
      uint08 SEG_B:1;
      uint08 SEG_C:1;
      uint08 SEG_D:1;
      uint08 SEG_E:1;
      uint08 SEG_F:1;
      uint08 SEG_G:1;
      uint08 SEG_DP:1;
   }Solo;
}NumberValue;



typedef struct
{
   TimerFlags    Times;
   NumberValue   Temperature;
   NumberValue   Humidity;
   LedShow       Led;
   KeyState	 Key;
   KeyState	 KeyCheck;
   KeyState	 State;
}AHU_DEF;


extern AHU_DEF Ahu1;


#endif
