
#ifndef CL_MODBUS_H
#define CL_MODBUS_H

typedef enum 
{
     MD_ERR_OK = 0x00,
     MD_DEV_ADDR_ERR ,
     MD_CMD_ERR ,
     MD_CRC_ERR ,
     MD_LEN_ERR ,
     MD_TRG_ADDR_ERR ,
     MD_TRG_LEN_ERR ,
     MD_TRG_LEN_LMT_ERR ,
     MD_READ_TOTAL_LEN_ERR ,
     MD_WRITE_TOTAL_LEN_ERR ,
     MD_NULL_ERROR = 0xEE10,
}MdErrEnum;

typedef enum 
{
    MD_CMD_RD = 0x03,
    MD_CMD_WR = 0x06,
    MD_CMD_WRP = 0x10,
    MD_SHORT_CMD_LEN = 0x08,
    MD_DEV_ADDR_LEN = 0x08,

    MD_0X10_EXTRA_BYTE = 0x09,
    MD_0X03_EXTRA_BYTE = 0x05,
    MD_UART_MAX_LEN = 0xFF,//must keep <= UartData Buff length
    MD_RSP_DATA_INDEX = 0x03,//Slave 0x03 data start
    MD_DEV_ADDR_INDEX = 0x00,
    MD_DEV_CMD_INDEX = 0x01,

    MD_0X10_TRG_ADDR_INDEX = 0x02,
    MD_0X10_TRG_LEN_INDEX = 0x04,
    MD_0X10_TRG_NUM_INDEX = 0x06,

    MD_0X03_TRG_ADDR_INDEX = 0x02,
    MD_0X03_RSP_NUM_INDEX = 0x02,
    MD_0X03_TRG_LEN_INDEX = 0x04,
    MD_0X03_TRG_NUM_INDEX = 0x06,
    MD_MST_DATA_INDEX = 0x07,//Master 0x10 data start

}MdCmdEnum;


//void (*ptask)(uchar)
typedef struct  {
     MdErrEnum (*LenChkCheck)(uint16 trgaddr,uint16 length);
     uint16 (*RdData)(uint16 trgaddr);
     void     (*WrData)(uint16 trgaddr,uint16 data);
     uint16  RawDataLen;       //收到的纯字节数据的长度
     uint16  rePkglen;          //回复包的长度
     uint08 *RawData;           //收到的纯字节数据
     uint08 *p2trg;               //回复包的保存地址
}Md_Tcp_Dep;

extern uint16  Slave_ModbusDataSetup(Md_Tcp_Dep *Tcp);

extern MdErrEnum MdDataDeal(Md_Tcp_Dep *Tcp);




#endif 

















