
#ifndef TYPEDEF_H
#define TYPEDEF_H


// char,uchar
typedef char CHAR,INT8,int8,S8,*PCHAR,*pchar,*PINT8,*pint8,*PS8,*ps8,*LPSTR;
typedef const char *LPCSTR;
typedef unsigned char uchar,UCHAR,U8,UINT8,uint8,uint08,BYTE,*puchar,*PUCHAR,*PU8,*pu8,*PUINT8,*puint8,*PBYTE,*LPBYTE;
// short,ushort
typedef short SHORT,INT16,int16,*PSHORT,*pshort,*PINT16,*pint16,
*PWCHAR,*S16,*pwchar,*PWORD,*pword;
typedef unsigned short WORD,word,USHORT,ushort,UINT16,uint16,U16,*PUSHORT,*pushort,*PUINT16,*puint16,*PU16,*pu16;
// wchar
typedef unsigned short WCHAR;
// INT,uint
typedef int INT,*PINT,*pint;
typedef unsigned int UINT,uint,*PUINT,*puint,*PUINT32,*puint32,*PU32,*pu32;
// long,ulong
typedef long LONG,*PLONG,*plong,INT32,int32,S32,DWORD,dword,*PINT32,*pint32,*PS32,*ps32,*PDWORD,*pdword;
typedef unsigned long ULONG,ulong,*PULONG,*pulong,UINT32,uint32,U32;
// VOID
typedef void VOID,*PVOID,*LPVOID;
// convenience
typedef unsigned char BOOLEAN,BOOL,*PBOOL;


typedef union
{
    uchar All;
    struct
    {
        uchar Bit0:1;
        uchar Bit1:1;
        uchar Bit2:1;
        uchar Bit3:1;
        uchar Bit4:1;
        uchar Bit5:1;
        uchar Bit6:1;
        uchar Bit7:1;
    } Bits;
}Bitsdef;



typedef union
{
    UINT32 All;
    struct
    {
        UINT32 BYTE4:8;
        UINT32 BYTE3:8;
        UINT32 BYTE2:8;
        UINT32 BYTE1:8;
    } Bytes;
    struct
    {
        UINT16 LWORD:16;
        UINT16 HWORD:16;
    } Words;
}UINT32T04BYTE;











#define __25ms__ 25
#define __5ms__ 3


#endif
