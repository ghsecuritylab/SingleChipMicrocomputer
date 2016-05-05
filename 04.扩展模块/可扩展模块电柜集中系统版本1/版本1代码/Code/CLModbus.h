
#ifndef CLMODBUS_H
#define CLMODBUS_H

typedef enum
{
   MD_ERR_OK = 0x00,
   MD_DEV_ADDR_ERR,
   MD_CMD_ERR,
   MD_CRC_ERR,
   MD_LEN_ERR,
   MD_TRG_ADDR_ERR,
   MD_TRG_LEN_ERR,
   MD_TRG_LEN_LMT_ERR,
   MD_READ_TOTAL_LEN_ERR,
   MD_WRITE_TOTAL_LEN_ERR,
   MD_NULL_ERROR = 0xEE10,
}MdErrEnum;


//typedef struct
//{
//   uint08 AddrID;
//   uint16 AddrReg;
//   uint16 RegNum;
//   union
//   {
//      uint08 All;
//      struct
//      {
//         uint08 TimeOut:4;
//         uint08 Enable:1;
//         uint08 Byte0Word1:1;
//         uint08 WR1RD0:1;
//         uint08 Health:1;
//      }Solo;
//   }Flags;
//}Md_Poll_Def;

//typedef struct Md_Tcp_Dep *Md_Tcp_SameDep;//指向本身结构体的指针

typedef struct
{
//   MdErrEnum (*AddrCheck)(void *pData);
   MdErrEnum (*LenChkCheck)(uint16 trgaddr, uint16 length);
   uint16  (*RdData)(uint16 trgaddr);
   void    (*WrData)(uint16 trgaddr, uint16 data);
   uint08  RegArea;
   uint16  RawDataLen;       //收到的纯字节数据的长度
   uint16  rePkglen;         //回复包的长度
   uint08 *RawData;          //收到的纯字节数据
   uint08 *p2trg;            //回复包的保存地址
//   Md_Poll_Def Poll;
}Md_Tcp_Dep;



uint08 MdRegArea(Md_Tcp_Dep *Tcp);
//MdErrEnum MdAddrCheck(void *pData);
//MdErrEnum LengthCheck(uint16 trgaddr, uint16 length);
MdErrEnum MdDataDeal(Md_Tcp_Dep *Tcp);
uint16  Slave_ModbusDataSetup(Md_Tcp_Dep *Tcp);

extern Md_Tcp_Dep MdTcp1;


#endif

















