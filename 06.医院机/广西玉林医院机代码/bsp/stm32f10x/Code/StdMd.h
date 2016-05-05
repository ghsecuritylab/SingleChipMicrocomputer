

#ifndef _STD_MD_H_
#define _STD_MD_H_

typedef enum 
{
  BITTYPE = 0X55,
  BYTETYPE = 0XAA,
  WORDTYPE = 0X5A,
  DEF_INDEX = 0XFF,
  BIT_LEN_MAX = 48,
  BYTE_LEN_MAX = 10,
  WORD_LEN_MAX = 8,
}DATA_TYPE_Enum;


typedef union
{
   uint08 All[6];
   struct
   {
/*000*/   uint08 AHURunning:1;
/*001*/   uint08 AHUStandBy:1;
/*002*/   uint08 HEPAError:1;
/*003*/   uint08 Nagative:1;
/*004*/   uint08 AHUError:1;
/*005*/   uint08 MoistRunning:1;
/*006*/   uint08 WinterSummer:1;//1=冬天; 0 = 夏天
/*007*/   uint08 EHeating01:1;
/*008*/   uint08 EHeating02:1;
/*009*/   uint08 EHeating03:1;
/*010*/   uint08 AHU01RunKey:1;
/*011*/   uint08 AHU01StbKey:1;
/*012*/   uint08 AHU01NgtKey:1;
/*013*/   uint08 AHU01NonKey:1;
/*014*/   uint08 AHU02RunKey:1;
/*015*/   uint08 AHU02StbKey:1;
/*016*/   uint08 AHU02NgtKey:1;
/*017*/   uint08 AHU02NonKey:1;
/*018*/   uint08 AHU03RunKey:1;
/*019*/   uint08 AHU03StbKey:1;
/*020*/   uint08 AHU03NgtKey:1;
/*021*/   uint08 AHU03NonKey:1;
/*022*/   uint08 AHULogRunKey:1;
/*023*/   uint08 AHULogStbKey:1;
/*024*/   uint08 AHULogNgtKey:1;
/*025*/   uint08 AHULogNonKey:1;
/*026*/   uint08 unused001:1;
/*027*/   uint08 unused002:1;
/*028*/   uint08 unused003:1;
/*029*/   uint08 unused004:1;
/*030*/   uint08 unused005:1;
/*031*/   uint08 unused006:1;
/*032*/   uint08 unused007:1;
/*033*/   uint08 unused008:1;
/*034*/   uint08 unused009:1;
/*035*/   uint08 unused010:1;
/*036*/   uint08 unused011:1;
/*037*/   uint08 unused012:1;
/*038*/   uint08 unused013:1;
/*039*/   uint08 unused014:1;
/*040*/   uint08 unused015:1;
/*041*/   uint08 unused016:1;
/*042*/   uint08 unused017:1;
/*043*/   uint08 unused018:1;
/*044*/   uint08 unused019:1;
/*045*/   uint08 unused020:1;
/*046*/   uint08 unused021:1;
/*047*/   uint08 unused022:1;
   }List;
}StdAirBitBase;

typedef union
{
   uint08 All[10];
   struct
   {
/*000*/        uint08 HeatGate;//热水阀
/*001*/        uint08 ColdGate;//冷水阀
/*002*/        uint08 AHU01TempSet;
/*003*/        uint08 AHU01RhSet;
/*004*/        uint08 AHU02TempSet;
/*005*/        uint08 AHU02RhSet;
/*006*/        uint08 AHU03TempSet;
/*007*/        uint08 AHU03RhSet;
/*008*/        uint08 AHULogTempSet;
/*009*/        uint08 AHULogRhSet;
/*XXX*/        uint08 AHULogTempSetRec;
/*XXX*/        uint08 AHULogRhSetRec;
   }List;
}StdAirByteBase;

typedef union
{
   uint16 All[8];
   struct
   {
/*000*/        uint16 SupplyPressDisp;
/*001*/        uint16 RoomPressDisp;
/*002*/        uint16 Room01TempDisp;    
/*003*/        uint16 Room01RhDisp;    
/*004*/        uint16 Room02TempDisp;            
/*005*/        uint16 Room02RhDisp;                
/*006*/        uint16 Room03TempDisp;                
/*007*/        uint16 Room03RhDisp;                  
   }List;
}StdAirWordBase;

typedef struct
{
   uint08 All[40];
   struct
   {
      StdAirBitBase Bits;   //6
      StdAirByteBase Bytes; //10
      StdAirWordBase Words; //16
   }Solo;
}StdAirDataBase;

extern StdAirDataBase *StdAirBlock1;
extern Md_Tcp_Dep MdTcp1;
extern Md_Tcp_Dep MdTcp4;
extern uint08 ReadBits(uint08 *p2data, uint08 index);
extern void WriteBits(uint08 *p2data, uint08 index, uint08 bits);

void COM4MdTcpRsp(Md_Tcp_Dep *Tcp, UartType *UartDataBlock);
void StdMdTcpInit(Md_Tcp_Dep *Tcp);
void StdMdTcpGetReady(Md_Tcp_Dep *Tcp,UartType *UartDataBlock);
void StdMdTcpRsp(Md_Tcp_Dep *Tcp,UartType *UartDataBlock);
void MdTcbInit();
void PanelDataWrite(StdAirDataBase *DataBase,uint16 index ,uint16 Data);
uint16 PanelDataRead(StdAirDataBase *DataBase,uint16 index);

void MdMasterPoll2();



#endif
