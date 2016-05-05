





#ifndef _74LS165_H
#define _74LS165_H

#define  _MAX_   8

typedef union
{
    uchar All;
    struct
    {
        uchar _Bit_0:1;
        uchar _Bit_1:1;
        uchar _Bit_2:1;
        uchar _Bit_3:1;
        uchar _Bit_4:1;
        uchar _Bit_5:1;
        uchar _Bit_6:1;
        uchar _Bit_7:1;
    } Bits;
}Bit_165_def;




extern Bit_165_def BIT1;
extern uchar Read_165Data(void);



void Scan_165_Deal(uchar keyaddr);



#endif

