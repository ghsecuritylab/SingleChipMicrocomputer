
#if!defined   __misc_me_H__
#define       __misc_me_H__

#ifndef uint8_t
typedef uint8_t BYTE ;
#endif
typedef uint16_t WORD ;
#ifndef DWORD
typedef uint32_t DWORD ;
#endif

typedef void VOID,*PVOID,*LPVOID;// VOID

typedef unsigned char  faUint8;
typedef signed   char  faInt8;
typedef unsigned short faUint16;
typedef signed   short faInt16;                
typedef unsigned int   faUint32;       
typedef signed   int   faInt32;   
typedef int faStatus;
typedef unsigned long int   faUint64;
typedef unsigned short* SWTLP16;
typedef unsigned char   faBoolean;

typedef unsigned char BOOL;

typedef unsigned char  uint8;
typedef unsigned char  uint08;
typedef unsigned char  UINT08;
typedef unsigned short uint16;
typedef unsigned int   uint32;

typedef signed   char  int8;
typedef signed   short int16;
typedef signed   int   int32;

typedef float           fp32;
typedef double          fp64;


typedef unsigned char  uchar,UCHAR,U8,UINT8,*puchar,*PUCHAR,*PU8,*pu8,*PUINT8,*puint8,*PBYTE,*LPBYTE;;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;

typedef signed   char  INT8;
typedef signed   short INT16;
typedef signed   int   INT32;


//related with C Compiler setting
typedef unsigned int      ULONG;
typedef signed   int      LONG;
typedef signed   long int int64;
typedef unsigned long int uint64;
typedef unsigned long int INT64U;
typedef signed   long int INT64;
typedef unsigned long int UINT64;

typedef int 	BITF;

/*! \brief Unsigned 16-bit value. */
typedef unsigned int       u_int;
/*! \brief Unsigned 32-bit value */
/*! \brief Unsigned 64-bit value */
typedef unsigned long int u_longlong;
/*! \brief Void pointer */
typedef void * HANDLE;

typedef unsigned int   uptr_t;
typedef const char      prog_char;

//-----------------------------------------------------------------------------
// Macro functions
//-----------------------------------------------------------------------------

#define s2ch(i) (*(uc*)(&(i)))
#define s2cl(i) *(((uc*)(&(i)))+1)
#define S2CH(i) (*(uc*)(&(i)))
#define S2CL(i) *(((uc*)(&(i)))+1)
#define testbit(var,bit) ((var)&(1<<(bit)))//位测试
#define notbit(var,bit)  ((var)^=(1<<(bit)))//位置1
#define setbit(var,bit)  ((var)|=(1<<(bit)))//位置1
#define Setbit(var,bit)  ((var)|=(1<<(bit)))//位置1
#define clrbit(var,bit)  ((var)&=~(1<<(bit)))//位清零
#define _nop_() __no_operation();
#define _di_()   __disable_interrupt();
#define _ei_()   __enable_interrupt();



#define MEMBER_OFFSET(TYPE,MEM) ((int)(char*)&(((TYPE*)0)->MEM))

//#define CopyMemory(pDest,pSrc,nLength)		memcpy(pDest,pSrc,nLength)
//#define FillMemory(pDest,nFill,nLength)		memset(pDest,nFill,nLength)
//#define ZeroMemory(pDest,nLength)		memset(pDest,0,nLength)
//#define MoveMemory(pDest,pSrc,nLength)		memcpy(pDest,pSrc,nLength)
//#define AllocMemory(nLength)			malloc(nLength)
//#define FreeMemory(pMem)		        free(pMem)
//#define HeapMemRequire(nLength)			malloc(nLength)
//#define HeapMemFree(pMem)			free(pMem)
//-----------------------------------------------------------------------------













#endif
