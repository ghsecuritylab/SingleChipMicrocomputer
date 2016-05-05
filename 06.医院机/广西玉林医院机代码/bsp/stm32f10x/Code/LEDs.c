
#include "includes.h"


uint08 DisBuff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint08 TopLEDBuff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint08 BlinkTimer;
uint08 BlinkFlag;
uint08 FastBlinkTimer;
uint08 FastBlinkFlag;

#define COM1_ON() {GPIO_ResetBits(GPIOB,GPIO_Pin_9);}
#define COM2_ON() {GPIO_ResetBits(GPIOB,GPIO_Pin_8);}
#define COM3_ON() {GPIO_ResetBits(GPIOB,GPIO_Pin_7);}
#define COM4_ON() {GPIO_ResetBits(GPIOB,GPIO_Pin_6);}
#define COMS_OFF() {GPIO_SetBits(GPIOB,GPIO_Pin_9);\
                                   GPIO_SetBits(GPIOB,GPIO_Pin_8);\
                                   GPIO_SetBits(GPIOB,GPIO_Pin_7);\
                                   GPIO_SetBits(GPIOB,GPIO_Pin_6);}


void SetDispCode(uint16 dispData)
{
    if ( testbit(dispData,15)!=0x00 )
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_4);
    }
    else
    {
        GPIO_SetBits(GPIOD,GPIO_Pin_4);
    }
    if ( testbit(dispData,14)!=0x00 )
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_5);
    }
    else
    {
        GPIO_SetBits(GPIOD,GPIO_Pin_5);
    }
    if ( testbit(dispData,13)!=0x00 )
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_6);
    }
    else
    {
        GPIO_SetBits(GPIOD,GPIO_Pin_6);
    }
    if ( testbit(dispData,12)!=0x00 )
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_7);
    }
    else
    {
        GPIO_SetBits(GPIOD,GPIO_Pin_7);
    }
    if ( testbit(dispData,11)!=0x00 )
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_9);
    }
    else
    {
        GPIO_SetBits(GPIOG,GPIO_Pin_9);
    }
    if ( testbit(dispData,10)!=0x00 )
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_10);
    }
    else
    {
        GPIO_SetBits(GPIOG,GPIO_Pin_10);
    }
    if ( testbit(dispData,9)!=0x00 )
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_11);
    }
    else
    {
        GPIO_SetBits(GPIOG,GPIO_Pin_11);
    }
    if ( testbit(dispData,8)!=0x00 )
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_12);
    }
    else
    {
        GPIO_SetBits(GPIOG,GPIO_Pin_12);
    }
    if ( testbit(dispData,7)!=0x00 )
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_13);
    }
    else
    {
        GPIO_SetBits(GPIOG,GPIO_Pin_13);
    }
    if ( testbit(dispData,6)!=0x00 )
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_14);
    }
    else
    {
        GPIO_SetBits(GPIOG,GPIO_Pin_14);
    }
    if ( testbit(dispData,5)!=0x00 )
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_15);
    }
    else
    {
        GPIO_SetBits(GPIOG,GPIO_Pin_15);
    }
    if ( testbit(dispData,4)!=0x00 )
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_3);
    }
    else
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_3);
    }
    if ( testbit(dispData,3)!=0x00 )
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_4);
    }
    else
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_4);
    }
    if ( testbit(dispData,2)!=0x00 )
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_5);
    }
    else
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_5);
    }
    if ( testbit(dispData,1)!=0x00 )
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_0);
    }
    else
    {
        GPIO_SetBits(GPIOE,GPIO_Pin_0);
    }
    if ( testbit(dispData,0)!=0x00 )
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_1);
    }
    else
    {
        GPIO_SetBits(GPIOE,GPIO_Pin_1);
    }
}

void ScanLed()
{
    static uint08 DisOrder =0;
    COMS_OFF();
    if ( DisOrder ==0 )
    {
        SetDispCode(DisBuff[3]*256+DisBuff[2]);
//  	SetDispCode(0xAA55);
        COM2_ON();
        DisOrder++;
    }
    else if ( DisOrder ==1 )
    {
        SetDispCode(DisBuff[1]*256+DisBuff[0]);
//  	SetDispCode(0xAAFF);
        COM1_ON(); //����
        DisOrder++;
    }
    else if ( DisOrder ==2 )
    {
        SetDispCode(DisBuff[5]*256+DisBuff[4]);
        COM3_ON();
        DisOrder++;
    }
    else
    {
        SetDispCode(DisBuff[7]*256+DisBuff[6]);
        COM4_ON();
        DisOrder=0;
    }
}

void TurnLed(uint08 num)
{
    uint08 LedNum = (num&0x7F)-1;
    if ( num ==0xFF )
    {
        TopLEDBuff[0] = 0x00;
        TopLEDBuff[1] = 0x00;
        TopLEDBuff[2] = 0x00;
        TopLEDBuff[3] = 0x00;
        TopLEDBuff[4] = 0x00;
        TopLEDBuff[5] = 0x00;
        TopLEDBuff[6] = 0x00;
        TopLEDBuff[7] = 0x00;
        return;
    }

    if ( LedNum>63 )
    {
        return;
    }
    WriteBits(TopLEDBuff,LedNum,1);
}

uint08 LEDZero()
{
    return 0;
}
uint08 lled01()//��ͣ
{
    return !POL_DI_Block.Solo.INPUT_EMC;
}
uint08 lled02()//����
{
    return !POL_DI_Block.Solo.INPUT_FIRE_EMC;
}
uint08 lled03()//ȱ��
{
    return !POL_DI_Block.Solo.INPUT_NO_WIND;
}

uint08 lled04()//��Ч
{
    return POL_DI_Block.Solo.INPUT_CHU_XIAO;
}
uint08 lled05()//��Ч
{
    return POL_DI_Block.Solo.INPUT_ZHONG_XIAO;
}
uint08 lled06()//�Ǹ�Ч
{
    return POL_DI_Block.Solo.INPUT_YA_GAO_XIAO;
}
uint08 lled07()//��Ч
{
    return POL_DI_Block.Solo.INPUT_GAO_XIAO;
}
uint08 lled08()//�����
{
    return POL_DI_Block.Solo.INPUT_HEAT_HIGH_TEMP;
}

uint08 lled09()//Ԥ�ȸ��� 
{
    return POL_DI_Block.Solo.INPUT_PRE_HEAT_HIGH_TEMP;
}
uint08 lled10()//����
{
    return POL_DI_Block.Solo.INPUT_WATER_SENSOR;
}
uint08 lled11()//���� 
{
    return POL_DI_Block.Solo.INPUT_COLD_PROTECT;
}
uint08 lled12()//��ͣ (�Ű�)
{
    return POL_DI_Block.Solo.BOX_PANEL_KEY_RUN;
}
uint08 lled13()//ֵ�� (�Ű�)
{
    return POL_DI_Block.Solo.BOX_PANEL_KEY_STANDBY;
}

uint08 lled14()//Զ�� (�Ű�)
{
    return POL_DI_Block.Solo.BOX_PANEL_KEY_REMOTE_RUN;
}

uint08 lled15()//Զֵ (�Ű�)
{
    return POL_DI_Block.Solo.BOX_PANEL_KEY_REMOTE_STANDBY;
}

uint08 lled16()//��ͣ  (�Ű�)
{
    return !POL_DI_Block.Solo.BOX_PANEL_KEY_EMC_STOP;
}

uint08 lled17()//����
{
    return FastBlinkFlag;
}
uint08 lled18()//ͨѶ1
{
    if(UartAppData2.MasterTimeout>0)
    {
        return FastBlinkFlag;
    }
    return 0;
}
uint08 lled19()//ͨѶ2
{
    if (YYJ1.OP.SysPar.SaveBit.Solo.MCU1_PLC0)
    {
        return 1;
    }
    else
    {
        if (UartAppData3.MasterTimeout > 0)
        {
            return FastBlinkFlag;
        }
        return 0;
    }
}
uint08 lled20()//��Ƶ
{
    return POL_DI_Block.Solo.SEL_MODE_FRQ_CVT;
}
uint08 lled21()//��Ƶ
{
    return POL_DI_Block.Solo.SEL_MODE_FIX_FRQ;
}
uint08 lled22()//����
{
    return POL_DI_Block.Solo.SEL_STAR_START;
}

uint08 lled23()//������
{
    return POL_DI_Block.Solo.SEL_TRIANGLE_START;
}

uint08 lled24()//�ļ�
{
   if (POL_DI_Block.Solo.SEL_SEASON_SUMMER)
   {
      return 1;
   }
   else if (!POL_DI_Block.Solo.SEL_SEASON_WINTER)
   {
      if (!POL_DI_Block.Solo.INPUT_WATER_SENSOR)
      {
         return 1;
      }
   }
   return 0;
}
uint08 lled25()//����
{
   if (POL_DI_Block.Solo.SEL_SEASON_WINTER)
   {
      return 1;
   }
   else if (!POL_DI_Block.Solo.SEL_SEASON_SUMMER)
   {
      if (POL_DI_Block.Solo.INPUT_WATER_SENSOR)
      {
         return 1;
      }
   }
   return 0;
}
uint08 lled26()//�Զ�
{
   if (!POL_DI_Block.Solo.SEL_SEASON_SUMMER && !POL_DI_Block.Solo.SEL_SEASON_WINTER )
   {
      return 1;
   }
   return 0;
}

uint08 lled27()//�ֶ�
{
   if (!POL_DI_Block.Solo.SEL_SEASON_SUMMER && !POL_DI_Block.Solo.SEL_SEASON_WINTER )
   {
      return 0;
   }
      return 1;
}

uint08 lled28()//����(��Ƶ����)
{
    return POL_DI_Block.Solo.FF_FEEDBACK_RUN;
}

uint08 lled29()//����(��Ƶ����)
{
    return POL_DI_Block.Solo.FF_FEEDBACK_ERR;
}

uint08 lled30()//����(��Ƶ����)
{
    return POL_DI_Block.Solo.FC_FEEDBACK_RUN;
}
uint08 lled31()//����(��Ƶ����)
{
    return POL_DI_Block.Solo.FC_FEEDBACK_ERROR;
}

uint08 lled32()//���Ƴ�ʱ
{
    //if(PolMdTimeOutTimer==0)
    //{
    //    return FastBlinkFlag;
   // }
    return 0;
}

/***************AHU״̬�����ָʾ********************/
uint08 lled33()//����
{
    return Lamps.Solo.LAMP_AHU_RUNNING;
}

uint08 lled34()//ֵ��
{
    return Lamps.Solo.LAMP_AHU_STANDBY;
}
uint08 lled35()//����
{
    return Lamps.Solo.LAMP_AHU_ERROR;
}

uint08 lled36()//ȱ��
{
    return Lamps.Solo.LAMP_AHU_NOWIND;
}
uint08 lled37()//��Ч
{
    return Lamps.Solo.LAMP_AHU_CHU_XIAO;
}
uint08 lled38()//��Ч
{
    return Lamps.Solo.LAMP_AHU_ZHONG_XIAO;
}
uint08 lled39()//�Ǹ�Ч
{
    return Lamps.Solo.LAMP_AHU_YA_GAO_XIAO;
}
uint08 lled40()//��Ч
{
    return Lamps.Solo.LAMP_AHU_GAO_XIAO;
}
uint08 lled41()//���ȱ���
{
    return !Lamps.Solo.LAMP_AHU_EHEAT_HIGH;
}
uint08 lled42()//Ԥ�ȱ���
{
    return !Lamps.Solo.LAMP_AHU_PREHEAT_HIGH;
}

uint08 lled43()//��������
{
    return Lamps.Solo.LAMP_AHU_COLD_ERR;
}
uint08 lled44()//����ͣ����
{
    return Lamps.Solo.LAMP_AHU_COLD_STOP_ERR;
}
uint08 lled45()//��ͣ����
{
    return Lamps.Solo.LAMP_AHU_EXTERN_EMC_ERR;
}

uint08 lled46()//��������
{
    return Lamps.Solo.LAMP_AHU_FIRE_ERR;
}
uint08 lled47()//(�ֶ�)��Ƶ��AO
{
    return POL_DI_Block.Solo.SEL_MODE_MANUAL_FRQ;
}
uint08 lled48()//(�Զ�)��Ƶ��AO
{
    return (!POL_DI_Block.Solo.SEL_MODE_MANUAL_FRQ);
}
/****************��ʪ��״̬*****************/
uint08 lled49()//����
{
    return Relays.Solo.HUMIDIFIER_CHAIN;
}
uint08 lled50()//����
{
    return Relays.Solo.HUMIDIFIER_START;
}
uint08 lled51()//��ŷ�
{
    return Relays.Solo.HUMIDIFIER_GATE;
}
/*************�ŷ���Զ���״̬*********************/
uint08 lled52()//#1
{
    if(Relays.Solo.AUTO_GATES_01)
    {
        return 1;
    }
    else if(POL_DI_Block.Solo.INPUT_WIND_GATE_01)
    {
        return BlinkFlag;
    }
    return 0;
}

uint08 lled53()//#2
{
    if(Relays.Solo.AUTO_GATES_02)
    {
        return 1;
    }
    else if(POL_DI_Block.Solo.INPUT_WIND_GATE_02)
    {
        return BlinkFlag;
    }
    return 0;
}
uint08 lled54()//#3
{
    if(Relays.Solo.AUTO_GATES_03)
    {
        return 1;
    }
    else if(POL_DI_Block.Solo.INPUT_WIND_GATE_03)
    {
        return BlinkFlag;
    }
    return 0;
}
uint08 lled55()//#4
{
    if(Relays.Solo.AUTO_GATES_04)
    {
        return 1;
    }
    else if(POL_DI_Block.Solo.INPUT_WIND_GATE_04)
    {
        return BlinkFlag;
    }
    return 0;
}

uint08 lled56()//#5
{
    if(Relays.Solo.AUTO_GATES_05)
    {
        return 1;
    }
    else if(POL_DI_Block.Solo.INPUT_WIND_GATE_05)
    {
        return BlinkFlag;
    }
    return 0;
}
uint08 lled57()//#6
{
    if(Relays.Solo.AUTO_GATES_06)
    {
        return 1;
    }
    else if(POL_DI_Block.Solo.INPUT_WIND_GATE_06)
    {
        return BlinkFlag;
    }
    return 0;
}
/*******����ģʽ*********/
uint08 lled58()//PLC
{
    return !YYJ1.OP.SysPar.SaveBit.Solo.MCU1_PLC0;
}
uint08 lled59()//MCU1
{
    return YYJ1.OP.SysPar.SaveBit.Solo.MCU1_PLC0;
}
uint08 lled60()//MCU2
{
    return 0;
}
/************��Ƶ������******************/
uint08 lled61()//����
{
    return Relays.Solo.FC_CTRL_START;
}
uint08 lled62()//ֵ��
{
    return Relays.Solo.FC_CTRL_STANDBY;
}
uint08 lled63()//ȫ��
{
    if(Relays.Solo.FC_CTRL_START)
    {
        return (!Relays.Solo.FC_CTRL_STANDBY);
    }
    else
    {
        return 0;
    }
}
uint08 lled64()//����
{
    return Relays.Solo.FC_CTRL_SPARE;
}




//void (* const RelayTasks[48])(uchar state)
uint08 (* const LedOnOffs[64])() =
{
    lled01,     //00
    lled02,     //01
    lled03,     //02
    lled04,     //03
    lled05,     //04
    lled06,     //05
    lled07,     //06
    lled08,     //07
    lled09,     //08
    lled10,     //09
    lled11,     //10
    lled12,     //11
    lled13,     //12
    lled14,     //13
    lled15,     //14
    lled16,     //15


    lled17,     //16
    lled18,     //17
    lled19,     //18
    lled20,     //19
    lled21,     //20
    lled22,     //21
    lled23,     //22
    lled24,     //23
    lled25,     //24
    lled26,     //25
    lled27,     //26
    lled28,     //27
    lled29,     //28
    lled30,     //29
    lled31,     //30
    lled32,     //31

    lled33,     //32
    lled34,     //33
    lled35,     //34
    lled36,     //35
    lled37,     //36
    lled38,     //37
    lled39,     //38
    lled40,     //39
    lled41,     //40
    lled42,     //41
    lled43,     //42
    lled44,     //43
    lled45,     //44
    lled46,     //45
    lled47,     //46
    lled48,     //47

    lled49,     //48
    lled50,     //49
    lled51,     //50
    lled52,     //51
    lled53,     //52
    lled54,     //53
    lled55,     //54
    lled56,     //55
    lled57,     //56
    lled58,     //57
    lled59,     //58
    lled60,     //59
    lled61,     //60
    lled62,     //61
    lled63,     //62
    lled64,     //63
};


void LedDisp()
{
    uint08 tmp;
    uint08 (*pFun)(void);


    if (BlinkTimer++ <120)
    {
        BlinkFlag = 1;
    }
    else
    {   
        BlinkFlag = 0;
        if(BlinkTimer>200)
        {
            BlinkTimer=0;
        }
    }

    if (FastBlinkTimer++ <25)
    {
        FastBlinkFlag = 1;
    }
    else
    {   
        FastBlinkFlag = 0;
        if(FastBlinkTimer>40)
        {
            FastBlinkTimer=0;
        }
    }

    //SetAllOff
    TurnLed(0XFF);
    for ( tmp =0;tmp<64;tmp++ )
    {
        pFun = LedOnOffs[tmp];//64��LED����
        if (  pFun() )
        {
            TurnLed(tmp+1);
        }
    }
    DisBuff[0x00]=TopLEDBuff[0];
    DisBuff[0x01]=TopLEDBuff[1];
    DisBuff[0x02]=TopLEDBuff[2];
    DisBuff[0x03]=TopLEDBuff[3];
    DisBuff[0x04]=TopLEDBuff[4];
    DisBuff[0x05]=TopLEDBuff[5];
    DisBuff[0x06]=TopLEDBuff[6];
    DisBuff[0x07]=TopLEDBuff[7];
}


