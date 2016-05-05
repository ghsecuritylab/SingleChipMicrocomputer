

#if!defined(__MiscFuc_H__)
#define __MiscFuc_H__

//
//
//extern u8 RTC_Get_Week(u16 year,u8 month,u8 day) ;
//extern void ShellMemView() ;
//
//
//
//typedef struct 
//{
//	u8 hour;
//	u8 min;
//	u8 sec;                  
//	u16 w_year;
//	u8  w_month;
//	u8  w_date;
//	u8  week;    	   
//}tm,*p_tm ;
//
//typedef struct {
//
//	BYTE UartReceivedCnt ;
//	BYTE Uart1_Get_Data ;
//	tm timer;
//	u32 SystemBasicStatus ;
//	u32 SystemBasicStatus1 ;
//	u32 SystemBasicStatus2 ;
//	BYTE DownloadStatus ;
//	u16 RS232Counter ;
//	BYTE DownloadMode ;
//	u32 NandFlashSize ;
//	
//} SystemStatus,*P_SystemStatus;
//
//
//
//
//
//
//typedef enum {
//	DeletePlayingFile1 = 1<<0 ,
//       DeleteCurrentRecordFile1 = 1<<1,
//       NewRecordingCallMaster1 = 1<<2,
//       CallingMaster1 = 1<<3,
//       NowReceivedACallIDRec1 = 1<<4,
//       SartAMasterControl1 = 1<<5,
//	RemoteSendingNumber1 = 1<<6,
//	CopyRemoteRec1 = 1<<7 ,
//	VoicePlayNandAutoReply1 = 1<<8 ,
//	VoicePlayingNand1 = 1<<9,
//	VoicePlayingNandNext1 = 1<<10,
//	VoicePlayingNandPrev1 = 1<<11,	
//	StartAutoCallInReply1 = 1<<12,
//	AutoReplyingPlaying1 = 1<<13,
//	AutoReplyingRecording1 = 1<<14,
//	NowCopyingRemoteRec1 = 1<<15 ,
//	NowWait5SecondFinishedTelecontrol1 = 1<<16 ,
//	AutoReplyCallInSettingFlag1 = 1<<17 ,
//	NowPlayVoiceFiles1 = 1<<18,
//	NowSendDataToControl1 = 1<<19,	
//	NowUserGetOnEndPlay1 = 1<<20,	
//	FirstBiggerChargeInput1 = 1<<21 ,
//	FirstBiggerChargeWaitSeconds1 = 1<<22 ,	
//	FirstBiggerChargeInputEnter1= 1<<23 ,	
//	VoiceRecordingStarting1 = 1<<24,
//	WaitRemoterReturnDTMF1 = 1<<25,
//	ReceiveAOkTeleloginDatas1 = 1<<26,
//	NowLineAplifierPowerStatus1 = 1<<27,
//	LineTestMode1 = 1<<28,
//	SDTestStatus1 = 1<<29,
//	MaxStatusValue1 = 1<<30
//}SystemBasicStatusBits1 ;
//
//typedef enum {
//	NowChangeTheEepromStatus2 = 1<<0 ,
//	NowFilesCopyToFlash = 1<<1 ,
//	NowFilesCopyToFlashA = 1<<2 ,
//	NowResetWDG2 = 1<<3 ,
//	NowTestFileWrite2 = 1<<4 ,
//	SDCardInitialOk = 1<<5 ,
//	NowUsbOff = 1<<6 ,
//	NowUsbOn = 1<<7 ,
//	DeleteOneTask = 1<<8,
//	GetOneTaskInfomations = 1<<9,
//	NowFormatSD = 1<<10,
//	NowOpenAThread = 1<<11,
//	WaitARecordingStart2 = 1<<12,
//	WaitAPlayingStart2 = 1<<13,
//	WaitPlaySDCard2 = 1<<14,
//	NowProcessACommand2 = 1<<15,
//	UartReceivedEndCommandFlag2 = 1<<16,
//	UartReceivedDataFlag2 = 1<<17,
//	ADCandDMAOk2 = 1<<18,
//	ADCBufferADMA2 = 1<<19,
//	ADCandDMABufferAWaitProcess2 = 1<<20,
//	LED3Change2 = 1<<21,
//	AdcDisplay2 = 1<<22,
//	VoiceAdcOpenStatus2 = 1<<23,
//	MaxStatusValue2 = 1<<30
//}SystemBasicStatusBits2 ;

//extern u8 HeapMemFree(void * pt) ;
//extern void *HeapMemRequire(u32 nbyte) ;
//extern void HeapMemInit(void)  ;
//extern u32 HeapGetMemErr(void) ;
//extern u32 GetTotalRAMSpace(void) ;
//extern u32 GetRAMFreeSpace (void) ;
//extern int Asc2Int(const char*szAscNum) ;
//extern void printch(char ch) ;
//extern u16 GetRAMFreeBlock(void) ;
extern void MasterFunctions(int argc,char*argv[]) ;


#endif

