

#ifndef _STD_MD_H_
#define _STD_MD_H_


extern ulong maxSpeed;
extern ulong currentSpeedsET;
extern Md_Tcp_Dep MdTcp1;
extern uint08 ReadBits(uint08 *p2data, uint08 index);
extern void WriteBits(uint08 *p2data, uint08 index, uint08 bits);

void StdMdTcpInit(Md_Tcp_Dep *Tcp);
void StdMdTcpGetReady(Md_Tcp_Dep *Tcp,UartType *UartDataBlock);
void StdMdTcpRsp(Md_Tcp_Dep *Tcp,UartType *UartDataBlock);
void MdTcbInit();
void MdTcbInit2();
void MdPoll(void);
MdErrEnum MdPoll2(void);
void MdMasterPoll();












#endif













