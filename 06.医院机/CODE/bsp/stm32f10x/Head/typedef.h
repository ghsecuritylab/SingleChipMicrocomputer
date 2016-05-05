
#ifndef _TYPE_DEF_H
#define _TYPE_DEF_H



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




#endif

