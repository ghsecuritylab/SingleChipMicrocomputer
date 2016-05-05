
#ifndef CAPP_H
#define CAPP_H

typedef struct  {
    uint08 tel_addr:7;             //Bit0—Bit6如果是远程设备此地址为 0x5A 
    uint08 scr_addr_en:1;       //Bit7=1,表示11字节后跟随4字节的请求源设备地址
    uint08 pkg_len:8;             //本次命令数据包的长度，此长度包括两字节的 CRC校验码
    uint08 cmd_type:3;           //Bit0—Bit2为读写模式，其值为0x03为读，其值为 0x06为写 
    uint08 dev_type:5;            //本次命令的设备类型码及读写模式，Bit3—Bit7 为设备类型，这里手术室情	情报面板为0x02
    uint08 trg_len:8;               //写入从设备的数据长度 MAX = 256-13 = 243 Bytes big endian
    uint16 trg_addr:16;          //读取从设备内部的开始地址，高 8 位，即Bit8—Bit15 big endian
    uint16 serial:15;               //当前命令的序列号  big endian
    uint16 MSbit:1;                //MSbit=0 请求包 MSbit=1 回复包
    uint32 scr_addr:32;          //当前命令的序列号
    uint32 dev_id:24;             //读取设备的从地址高 8 位，此地址为能迪公司命名的唯一设备识别地址 big endian
    uint32 dp:8;                    //数据开始位 datapointer
    uint16 crc:16;                 //CRC16值
}Cp_Rev_Solo_Def;

typedef union
{
    uint08 All[sizeof(Cp_Rev_Solo_Def)];
    Cp_Rev_Solo_Def Solo;
}Cp_Rev_Def;

typedef struct  {
     uint08 *RawData;           //收到的纯字节数据
     uint08 RawDataLen;       //收到的纯字节数据的长度
     Cp_Rev_Def  *cphead;           //接收数据解析的包头  结构体
     uint08 *p2trg;               //回复包的保存地址
     uint08  rePkglen;          //回复包的长度
}Cp_Tcp_Dep;



typedef enum 
{
    CP_ERR_OK = 0x00,
    CP_TRG_ADDR_ERR = 0x01,
    CP_TRG_LENGH_ERR = 0x02,
    CP_CRC_ERR = 0x03,
    CP_TEL_ADDR_ERR = 0x04,
    CP_DEV_TYPE_ERR = 0x05,
    CP_DEV_ID_ERR = 0x06,
    CP_BAD_REV = 0x07,
    CP_UNCOMPLETED_DATA = 0x08,
    CP_TOTAL_LENGH_ERR = 0x09,
}CpErrEnum;

typedef enum 
{
    CP_READING = 0x03,
    CP_WRITING = 0x06,
    CP_RAW_DATA_ADDR_WITH_ID = 15,
    CP_RAW_DATA_ADDR_WITHOUT_ID = 11,
    CP_EXLENGTH_WITH_ID = 17,
    CP_EXLENGTH_WITHOUT_ID = 13,
}CpCmdEnum;


enum CpLocEnum 
{
    deviceAddressLoc = 0x00,
    packageLenLoc = 0x01,
    cmd_DevType_Loc = 0x02,
    dev_id_Loc_H = 0x03,
    dev_id_Loc_M = 0x04,
    dev_id_Loc_L = 0x05,
    trg_addr_loc_H = 0x06,
    trg_addr_loc_L = 0x07,
    trg_len_loc = 0x08,
    trg_len_serial_H = 0x09,
    trg_len_serial_L = 0x0A,
    scr_addr_H1 = 0x0B,
    scr_addr_H2 = 0x0C,
    scr_addr_H3 = 0x0D,
    scr_addr_H4 = 0x0E,
} ;

extern const char *CP_ERR_ECHO[11];
void Cp_ReadPkg(Cp_Rev_Def *cp, const uchar *p2data);
CpErrEnum CpDevDeal(Cp_Tcp_Dep *CpTcp);


#endif 

















