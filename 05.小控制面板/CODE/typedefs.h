
#ifndef TYPEDEFS_H
#define TYPEDEFS_H


/*******************************************/ 
typedef  char  int8,INT8;
typedef  int   int16,INT16;
typedef  long  int32,INT32;
typedef unsigned char  uchar,uint08,UIN8;
typedef unsigned int   uint,uint16,UIN16;
typedef unsigned long  uint32,UIN32;


/*******************************************/ 
typedef union
{
   uint All;
   struct {
      uint  _1ms          :1;   //1����
      uint  _10ms         :1;   //10����
      uint  _100ms        :1;   //100����
      uint  _1000ms       :1;   //1000����
      uint  _10000ms      :1;   //5000����
      uint  Blink         :1;   //��˸
      uint  FastBlink     :1;   //����
      uint  Timer         :9;   //��ʱʱ��    
   } Solo;
}RUNFLAG_DEF;
/*******************************************/ 
typedef union
{
   uchar All;
   struct {
      uchar Key_RemotePower      :1;     //Զ�̿��ƿ�������
      uchar Key_RemoteStandby    :1;     //Զ�̿���ֵ������
      uchar Key_LocalPower       :1;     //���ؿ��ƿ������� 
      uchar Key_LocalStandby     :1;     //���ؿ���ֵ������
      uchar Key_None             :4;  
   }Solo;
}DI_KEY_DEF;
/*******************************************/ 
typedef union
{
   uint All[2];
   struct {
// /*1*/      uint  Run                         :1;  //���С�����
// /*2*/      uint  Standby                     :1;  //ֵ��������
// /*3*/      uint  Power                       :1;  //��Դ������
// /*4*/      uint  Faultr                      :1;  //���ϡ�����
// /*5*/      uint  Inefficient                 :1;  //��Ч������
// /*6*/      uint  InEeffect                   :1;  //��Ч������
// /*7*/      uint  Deigo                       :1;  //�Ǹߡ�����
// /*8*/      uint  Efficient                   :1;  //��Ч������
// /*9*/      uint  LackOfWind                  :1;  //ȱ�硪����
// /*10*/     uint  ElectricHeatingTemperature  :1;  //���ȸ��¡�����
// /*11*/     uint  PreheatingTemperature       :1;  //Ԥ�ȸ��¡�����
// /*12*/     uint  AntiFreezingAlarm           :1;  //��������������
// /*13*/     uint  FreezingStop                :1;  //����ͣ��������
// /*14*/     uint  EmergencyStop               :1;  //��ͣ������
// /*15*/     uint  FireControl                 :1;  //����������
// /*16*/     uint  Communication               :1;  //ͨѶ������

 /*1*/      uint  Power                       :1;  //��Դ������
 /*2*/      uint  Run                         :1;  //���С�����
 /*3*/      uint  Standby                     :1;  //ֵ��������
 /*4*/      uint  Communication               :1;  //ͨѶ������
 /*5*/      uint  Faultr                      :1;  //���ϡ�����
 /*6*/      uint  Inefficient                 :1;  //��Ч��������������
 /*7*/      uint  FanFaultr                   :1;  //������ϡ�����
 /*8*/      uint  InEeffect                   :1;  //��Ч��������������
 /*9*/      uint  LackOfWind                  :1;  //ȱ�籨��������
 /*10*/     uint  Deigo                       :1;  //�Ǹ�Ч��������������
 /*11*/     uint  ElectricHeatingTemperature  :1;  //���ȸ��¡�����
 /*12*/     uint  Efficient                   :1;  //��Ч��������������
 /*13*/     uint  PreheatingTemperature       :1;  //Ԥ�ȸ��¡�����
 /*14*/     uint  FreezingStop                :1;  //����ͣ��������
 /*15*/     uint  AntiFreezingAlarm           :1;  //����ͣ������������
 /*16*/     uint  FireControlEmc              :1;  //����/��ͣ����������
/****/      uint  Buzzer                      :1;  //������
/****/      uint  RemotePower                 :1;  //Զ�̿���_����������
/****/      uint  RemoteStandby               :1;  //Զ�̿���_ֵ��������
/****/      uint  LocalPower                  :1;  //���ؿ���_����������
/****/      uint  LocalStandby                :1;  //���ؿ���_ֵ��������
/****/      uint  NONE                        :11; //����
   }Solo;
}DO_LED_DEF;

/*******************************************/
typedef union
{
   uint All;
   struct
   {
      uint   RemotePower         :1 ;      //Զ�̿��� 1:���� 0:�ػ�  
      uint   RemoteStandby       :1 ;      //Զ�̿��� 1:ֵ�� 0:�ػ�  
      uint   LocalPower          :1 ;      //���ؿ��� 1:���� 0:�ػ�  
      uint   LocalStandby        :1 ;      //���ؿ��� 1:ֵ�� 0:�ػ�  
      uint   RemoteORLocal       :1 ;      //���ؿ��� 1:ֵ�� 0:�ػ� 
      uint   None                :11;      //����
   }Solo;             
}DO_LED_CTRL_DEF;
/*******************************************/
typedef struct
{
   DO_LED_CTRL_DEF Ctrl;
   uint   RS485addr;   //485��ַ
   uint   Crc;         //CRCУ�� 
   uint   LED_16bit;   //16λLED               
}STATUS_DEF;
/*******************************************/ 
typedef struct
{       	     
   RUNFLAG_DEF       Runflag;
   DI_KEY_DEF        Input;
   DI_KEY_DEF        KeyTreated;
   DO_LED_DEF        Output;
   STATUS_DEF        Status;
}CTRL_DEF;
/*******************************************/ 




extern CTRL_DEF  CTR1;




#endif




