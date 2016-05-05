

#ifndef AVR_AD_H
#define AVR_AD_H

#define FFU_CT_MAX 5913
#define FFU_CT_OFFSET 56 //静态时的AD值,采样电路决定
#define FFU_CT_ERROR 1200
#define FFU_CT_ERROR_MIN 200


typedef struct
{
   uint16 New:1;
   uint16 Dir:1;
   uint16 Cnt:7;
}BuffFliterFlag;

typedef struct
{
   BuffFliterFlag Flag;
   uint16 Buff[24];
   uint16 NowBuff;
   uint16 Average;
}BuffFliter;



extern BuffFliter FanCurFilter;

void AdcInit();
uint16 AvrGetAd(uint08 Chnr);


#endif









