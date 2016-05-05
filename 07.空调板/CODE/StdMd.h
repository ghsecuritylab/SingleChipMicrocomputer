

#ifndef _STD_MD_H_
#define _STD_MD_H_


uint08 ReadBits(uint08 *p2data, uint08 index);
void WriteBits(uint08 *p2data, uint08 index, uint08 bits);
MdErrEnum LengthCheck(uint16 trgaddr, uint16 length);

uint16 PDR1(uint16 index);
void PDW1(uint16 index, uint16 Data);

uint16 PDR2(uint16 index);
void PDW2(uint16 index, uint16 Data);

void StdMdTcpInit1(Md_Tcp_Dep *Tcp);
void StdMdTcpInit2(Md_Tcp_Dep *Tcp);

void MdTcbInit1();
void MdTcbInit2();

void MdPoll01(void);
MdErrEnum MdPoll2(void);
void MdMasterPoll();
void MdPoll02(void);



extern Md_Tcp_Dep MdTcp1;
extern Md_Tcp_Dep MdTcp2;





#endif













