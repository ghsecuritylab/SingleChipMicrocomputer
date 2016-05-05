
#ifndef CL_MODBUS_H
#define CL_MODBUS_H

//typedef enum
//{
//     MD_ERR_OK = 0x00,
//     MD_DEV_ADDR_ERR ,
//     MD_CMD_ERR ,
//     MD_CRC_ERR ,
//     MD_LEN_ERR ,
//     MD_TRG_ADDR_ERR ,
//     MD_TRG_LEN_ERR ,
//     MD_TRG_LEN_LMT_ERR ,
//     MD_READ_TOTAL_LEN_ERR ,
//     MD_WRITE_TOTAL_LEN_ERR ,
//     MD_NULL_ERROR = 0xEE10,
//}MdErrEnum;
//
//typedef enum
//{
//    MD_CMD_RD = 0x03,
//    MD_CMD_WR = 0x06,
//    MD_CMD_WRP = 0x10,
//    MD_SHORT_CMD_LEN = 0x08,
//    MD_DEV_ADDR_LEN = 0x08,
//
//    MD_0X10_EXTRA_BYTE = 0x09,
//    MD_0X03_EXTRA_BYTE = 0x05,
//    MD_UART_MAX_LEN = 0xFF,//must keep <= UartData Buff length
//    MD_RSP_DATA_INDEX = 0x03,//Slave 0x03 data start
//    MD_DEV_ADDR_INDEX = 0x00,
//    MD_DEV_CMD_INDEX = 0x01,
//
//    MD_0X10_TRG_ADDR_INDEX = 0x02,
//    MD_0X10_TRG_LEN_INDEX = 0x04,
//    MD_0X10_TRG_NUM_INDEX = 0x06,
//
//    MD_0X03_TRG_ADDR_INDEX = 0x02,
//    MD_0X03_RSP_NUM_INDEX = 0x02,
//    MD_0X03_TRG_LEN_INDEX = 0x04,
//    MD_0X03_TRG_NUM_INDEX = 0x06,
//    MD_MST_DATA_INDEX = 0x07,//Master 0x10 data start
//
//}MdCmdEnum;

typedef enum
{
   MD_ERR_OK = 0x00,
   SYS_MEM_REQ_ERR,
   SYS_MEM_POLL_NUM_ERR,
   SYS_SPE_POLL_IN_DEAL,
   SYS_CMD_TYPE_ERR,
   SYS_CMD_ADDR_ERR,
   SYS_CMD_LEN_ERR,
   SYS_CMD_RESPONSE_FLAG_ERR,
   SYS_NOTHING_ENABLE_ERR,
   SYS_ERR,
   SYS_FIND_NEXT,
   SYS_FIND_OK,
   SYS_BUS_DEV_FIND_OK,
   SYS_POLL_OK,
   SYS_NULL_POINTER_ERR,
   SYS_NULL_POINTER_BINDDEV,
   SYS_NULL_POINTER_BINDPCB,
   MD_DEV_ADDR_ERR,
   MD_CMD_ERR,
   MD_CRC_ERR,
   MD_LEN_ERR,
   MD_TRG_ADDR_ERR,
   MD_TRG_LEN_ERR,
   MD_TRG_LEN_LMT_ERR,
   MD_READ_TOTAL_LEN_ERR,
   MD_WRITE_TOTAL_LEN_ERR,
   MD_ERR,
   MD_READING_MAX_LEN_EXCEED,
   MD_ERR_RSP_ID_ERR,
   MD_NULL,
   MD_ERR_RSP_DATALEN_ERR,
   MD_NULL_ERROR = 250,
}MdErrEnum;

typedef enum
{
   MD_CMD_RD = 0x03,
   MD_CMD_WR = 0x06,
   MD_CMD_WRP = 0x10,

   TCP_APP_DATA_LEN_INDEX = 4,
   TCP_SERIAL_INDEX = 0,
   TCP_HEADER_LEN = 6,
   TCP_DEV_ADDR_INDEX = 6,
   TCP_DEV_CMD_INDEX = 7,
   TCP_SHORT_CMD_LEN = 12,
   TCP_0X10_EXTRA_BYTE = 13,
   TCP_0X03_EXTRA_BYTE = 9,
   TCP_0X10_TRG_NUM_INDEX = 12,
   TCP_0X10_TRG_ADDR_INDEX = 0x08,
   TCP_0X03_RSP_NUM_INDEX = 8,
   TCP_0X03_TRG_LEN_INDEX = 10,
   TCP_0X03_TRG_ADDR_INDEX = 0x08,
   TCP_MST_DATA_INDEX = 13,
   TCP_MST_RSP_DATA_INDEX = 9,



   MD_SHORT_CMD_LEN = 0x08,
   MD_DEV_ADDR_LEN = 0x08,

   MD_0X10_EXTRA_BYTE = 0x09,
   MD_0X03_EXTRA_BYTE = 0x05,
   MD_UART_MAX_LEN = 0xFF,
   MD_RSP_DATA_INDEX = 0x03,          //Slave 0x03 data start
   MD_DEV_ADDR_INDEX = 0x00,
   MD_DEV_CMD_INDEX = 0x01,

   MD_0X10_TRG_ADDR_INDEX = 0x02,
   MD_0X10_TRG_LEN_INDEX = 0x04,
   MD_0X10_TRG_NUM_INDEX = 0x06,

   MD_0X03_TRG_ADDR_INDEX = 0x02,
   MD_0X03_RSP_NUM_INDEX = 0x02,
   MD_0X03_TRG_LEN_INDEX = 0x04,
   MD_0X03_TRG_NUM_INDEX = 0x06,
   MD_DEV_RSP_DATA_LEN_INDEX = 0x02,
   MD_MST_RSP_DATA_INDEX = 0x03,
   MD_MST_DATA_INDEX = 0x07, //Master 0x10 data start
   SYS_READING_MAX_LEN = 127, //Master 0x10 data start

}MdCmdEnum;


#define MD_POLL_RD 0x01
#define MD_POLL_WR 0x02

typedef struct
{
   uint08 Addr;
   uint08 Flags;
   uint08 DataToRead; //in word
   uint16 StartAddr;
}Poll_Def;


typedef struct Md_Tcp_Dep *Md_Tcp_SameDep;


typedef struct
{
   MdErrEnum (*AddrCheck)(Md_Tcp_SameDep *Tcp);
   MdErrEnum (*LenChkCheck)(uint16 trgaddr, uint16 length, uint08 Station);
   uint16 (*RdData)(uint16 trgaddr, uint08 Station);
   void     (*WrData)(uint16 trgaddr, uint16 data, uint08 Station);
   Poll_Def  NowPoll;
   uint08 *RawData;           //收到的纯字节数据
   uint08 *p2trg;                //回复包的保存地址
   uint16  RawDataLen;     //收到的纯字节数据的长度
   uint16  rePkglen;          //回复包的长度
}Md_Tcp_Dep;





uint16  Slave_ModbusDataSetup(Md_Tcp_Dep *Tcp);
uint16  Master_ModbusDataSetup(Md_Tcp_Dep *Tcp);
extern MdErrEnum MdDataDeal(Md_Tcp_Dep *Tcp);



#endif

















