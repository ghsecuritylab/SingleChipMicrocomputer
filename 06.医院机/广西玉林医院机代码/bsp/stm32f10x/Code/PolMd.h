

#ifndef _POL_MDB_H_
#define _POL_MDB_H_




extern uint16 PolMdTimeOutTimer;
extern Md_Tcp_Dep MdTcp2;
extern MdErrEnum MdRet;
//extern uint08 ReadBits(uint08 *p2data, uint08 index);
//extern void WriteBits(uint08 *p2data, uint08 index, uint08 bits);

void PolMdTcpInit(Md_Tcp_Dep *Tcp);
void PolMdTcpGetReady(Md_Tcp_Dep *Tcp,UartType *UartDataBlock);
void PolMdTcpRsp(Md_Tcp_Dep *Tcp,UartType *UartDataBlock);
void PolMdTcbInit();
void PolMdTimeOut();



void MdMasterPoll();
#endif
