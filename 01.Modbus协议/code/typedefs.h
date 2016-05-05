
#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H

typedef unsigned char   uint08, UINT08, uchar;
typedef unsigned short  uint16, UINT16;
typedef unsigned int    _uint16, _UINT16;
typedef unsigned long	uint32, UINT32;
typedef signed char     int08 , INT08 ;
typedef signed short    int16 , INT16 ;
typedef signed int      _int16 , _INT16 ;
typedef signed long     int32 , INT32 ;


typedef union
{
   uint08 All;
   struct
   {
      uint08 Bit0;
      uint08 Bit1;
      uint08 Bit2;
      uint08 Bit3;
      uint08 Bit4;
      uint08 Bit5;
      uint08 Bit6;
      uint08 Bit7;
   }Solo;
}BIT;



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






typedef struct
{

   Module_DO_Def DO;

}Module_All_Def;


extern Module_All_Def MODE1;


#endif
