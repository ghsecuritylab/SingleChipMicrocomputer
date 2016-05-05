
#ifndef  _MODBUS_H
#define  _MODBUS_H


typedef enum
{
   NONE_ERR,
   ID_ERR,
   CMD_ERR,
   LENGTH_WRITE_ERR,
   LENGTH_READ_ERR,
   REG_ADDR_BEYOND_ERR,
   REG_LEN_BEYOND_ERR,
   REG_ADDR_ERR,
   CRC_ERR,
   WRITE_ERR,
   READ_ERR,
}ModbusErrorEnum;


typedef enum
{   
   CMD_0x00,
   CMD_0x01,
   CMD_0x02,
   CMD_0x03,
   CMD_0x04,
   CMD_0x05,
   CMD_0x06,
   CMD_0x07,
   CMD_0x08,
   CMD_0x09,
   CMD_0x0A,
   CMD_0x0B,
   CMD_0x0C,
   CMD_0x0D,
   CMD_0x0E,
   CMD_0x0F,
   CMD_0x10,
   CMD_0x11,
   CMD_0x12,
   CMD_0x13,
   CMD_0x14,
   CMD_0x15,
   CMD_0x16,
   CMD_0x17,
}ModbusCommandEnum;


typedef struct
{
    uint08 IDAddress;
    uint08 Command;
    uint08 DataLength;
    uint16 RegStartAddr;
    uint16 RegNumber;
    uint08 All;
    union
    {
       uint08 Read0Write1:1;
       uint08 nouse:1;
       uint08 nouse1:1;
       uint08 nouse2:1;
    }Flags;
}MasterModbus;

typedef struct  
{
     uint08 ReadDataLen;
     uint08 SendDataLen;
     uint08 *ReadData;           
     uint08 *SendData;  
     uint08 ErrorRepot; 
     MasterModbus Poll;
     uint08 All;
     union
     {
	uint08 Read0_Write1:1;
	uint08 none1:1;
	uint08 none2:1;
	uint08 none3:1;
	uint08 none4:1;
     }Flags;	            
}ModbusTcp;

extern ModbusTcp MdTcp1;


void SlaveModbus(ModbusTcp *Tcp);


#endif
