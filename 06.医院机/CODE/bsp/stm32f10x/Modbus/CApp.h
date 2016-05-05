
#ifndef CAPP_H
#define CAPP_H

typedef struct  {
    uint08 tel_addr:7;             //Bit0��Bit6�����Զ���豸�˵�ַΪ 0x5A 
    uint08 scr_addr_en:1;       //Bit7=1,��ʾ11�ֽں����4�ֽڵ�����Դ�豸��ַ
    uint08 pkg_len:8;             //�����������ݰ��ĳ��ȣ��˳��Ȱ������ֽڵ� CRCУ����
    uint08 cmd_type:3;           //Bit0��Bit2Ϊ��дģʽ����ֵΪ0x03Ϊ������ֵΪ 0x06Ϊд 
    uint08 dev_type:5;            //����������豸�����뼰��дģʽ��Bit3��Bit7 Ϊ�豸���ͣ�������������	�鱨���Ϊ0x02
    uint08 trg_len:8;               //д����豸�����ݳ��� MAX = 256-13 = 243 Bytes big endian
    uint16 trg_addr:16;          //��ȡ���豸�ڲ��Ŀ�ʼ��ַ���� 8 λ����Bit8��Bit15 big endian
    uint16 serial:15;               //��ǰ��������к�  big endian
    uint16 MSbit:1;                //MSbit=0 ����� MSbit=1 �ظ���
    uint32 scr_addr:32;          //��ǰ��������к�
    uint32 dev_id:24;             //��ȡ�豸�Ĵӵ�ַ�� 8 λ���˵�ַΪ�ܵϹ�˾������Ψһ�豸ʶ���ַ big endian
    uint32 dp:8;                    //���ݿ�ʼλ datapointer
    uint16 crc:16;                 //CRC16ֵ
}Cp_Rev_Solo_Def;

typedef union
{
    uint08 All[sizeof(Cp_Rev_Solo_Def)];
    Cp_Rev_Solo_Def Solo;
}Cp_Rev_Def;

typedef struct  {
     uint08 *RawData;           //�յ��Ĵ��ֽ�����
     uint08 RawDataLen;       //�յ��Ĵ��ֽ����ݵĳ���
     Cp_Rev_Def  *cphead;           //�������ݽ����İ�ͷ  �ṹ��
     uint08 *p2trg;               //�ظ����ı����ַ
     uint08  rePkglen;          //�ظ����ĳ���
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

















