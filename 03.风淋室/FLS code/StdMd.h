

#ifndef _STD_MD_H_
#define _STD_MD_H_



typedef enum
{
   ERR_FALSE = 0x00,
   ERR_TRUE =  0x01,
   ERR_TBD = 0x10,
   ERR_OVER = 0x11,
   ERR_BELOW = 0x12,
   RUNTIME_EXPIRE = 0x13,
   RUNTIME_ALERT = 0x14,
   RUNTIME_OK = 0x15,
   DEFAULT_ERROR_TIME = 0x0A,
}FLS_Enum;













extern Md_Tcp_Dep MdTcp1;
extern uint08 ReadBits(uint08 *p2data, uint08 index);
extern void WriteBits(uint08 *p2data, uint08 index, uint08 bits);

void StdMdTcpInit(Md_Tcp_Dep *Tcp);
void StdMdTcpGetReady(Md_Tcp_Dep *Tcp,UartType *UartDataBlock);
void StdMdTcpRsp(Md_Tcp_Dep *Tcp,UartType *UartDataBlock);
void MdTcbInit();
void MdPoll(void);












#endif













