
#ifndef _DEFINES_H
#define _DEFINES_H


#define BIT(x)           ( 1 << x )
#define SetBit(x,y)   ( x |= BIT(y)  ) 
#define ClrBit(x,y)   ( x &= ~BIT(y) ) 
#define GetBit(x,y)   ( x & BIT(y)   ) 

#define MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#define MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )


#endif