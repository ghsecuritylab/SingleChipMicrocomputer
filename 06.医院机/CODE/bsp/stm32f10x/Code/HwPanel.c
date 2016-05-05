
#include "includes.h"


YYJ_AI_DEF POL_AI_Block;
YYJ_AO_DEF POL_AO_Block;

uint16 AOAI_AadjustDeal(uint16 input , uint16 k)
{
    uint32 tmp= input*k/10000;
    return tmp;
}


void DoAOPoll()//8·PWMģ�������
{
    TIM_SetCompare1(PWM_TIM_8, AOAI_AadjustDeal(POL_AO_Block.Solo.HW_AO_HOT_GATE, YYJ1.OP.Check.AOadjust.Solo.HW_AO_HOT_GATE));
    TIM_SetCompare2(PWM_TIM_8, AOAI_AadjustDeal(POL_AO_Block.Solo.HW_AO_COLD_GATE, YYJ1.OP.Check.AOadjust.Solo.HW_AO_COLD_GATE));
    TIM_SetCompare3(PWM_TIM_8, AOAI_AadjustDeal(POL_AO_Block.Solo.HW_AO_HUMIDIFIER_CTRL, YYJ1.OP.Check.AOadjust.Solo.HW_AO_HUMIDIFIER_CTRL));

    //�Զ����
    POL_AO_Block.Solo.HW_AO_MANUAL_FRQ_SET = (uint32)POL_AI_Block.Solo.HW_AI_MANUAL_FRQ_SET*1000/2048;//һ��
    if( POL_DI_Block.Solo.SEL_MODE_MANUAL_FRQ )
    {
        TIM_SetCompare4(PWM_TIM_8, AOAI_AadjustDeal(POL_AO_Block.Solo.HW_AO_MANUAL_FRQ_SET, YYJ1.OP.Check.AOadjust.Solo.HW_AO_MANUAL_FRQ_SET));
    }
    else
    {
        TIM_SetCompare4(PWM_TIM_8, AOAI_AadjustDeal(POL_AO_Block.Solo.HW_AO_FC_FRQ, YYJ1.OP.Check.AOadjust.Solo.HW_AO_FC_FRQ));
    }
    //
    TIM_SetCompare1(PWM_TIM_1, AOAI_AadjustDeal(POL_AO_Block.Solo.HW_AO_HWP_DISP_RH, YYJ1.OP.Check.AOadjust.Solo.HW_AO_HWP_DISP_RH));
    TIM_SetCompare2(PWM_TIM_1, AOAI_AadjustDeal(POL_AO_Block.Solo.HW_AO_HWP_DISP_TEMP, YYJ1.OP.Check.AOadjust.Solo.HW_AO_HWP_DISP_TEMP));
    TIM_SetCompare3(PWM_TIM_1, AOAI_AadjustDeal(POL_AO_Block.Solo.HW_AO_MANUAL_FRQ_SET, YYJ1.OP.Check.AOadjust.Solo.HW_AO_MANUAL_FRQ_SET));
    TIM_SetCompare4(PWM_TIM_1, AOAI_AadjustDeal(POL_AO_Block.Solo.HW_AO_COLDHOT_GATE, YYJ1.OP.Check.AOadjust.Solo.HW_AO_COLDHOT_GATE));
//  TIM_SetCompare4(PWM_TIM_2,POL_AO_Block.HW_AO_COLDHOT_GATE);
}


uint16 MaoPao(uint16 *p2buff)//ð�����򷨴�С��������
{
    uint08 tmp= 0;
    uint08 tmpx= 0;
    uint16 itmp= 0;
    uint32 SumValue = 0;
    for ( tmp=0;tmp<24-1;tmp++ )
    {
        for ( tmpx=0;tmpx<24-tmp-1;tmpx++ )
        {
            if ( p2buff[tmpx]<p2buff[tmpx+1] )
            {

                itmp=p2buff[tmpx];
                p2buff[tmpx]=p2buff[tmpx+1];
                p2buff[tmpx+1]=itmp;
            }
        }
    }
    for ( tmp=4;tmp<20;tmp++ )
    {
        SumValue +=p2buff[tmp];
    }
    return SumValue/16;
}

void DoAIFilter()//��·ADCģ��������
{
    uint08 tmp= 0;
    uint08 ChnrlCnt= 0;
    static uint16 *p2buff;

    p2buff = rt_malloc(256); //malloc(nLength)��̬�ڴ���亯��  
    //#���ƽ��ֵ��ѹ
    for(ChnrlCnt=0;ChnrlCnt<7;ChnrlCnt++)
    {
        //#1 ȡ������������
        for ( tmp = 0;tmp < 24;tmp++ )
        {
            p2buff[tmp] = Adc_fun_date.DMA_ADC_PeripheralBaseAddr[tmp][ChnrlCnt];
        }
        //#2 ����:ð�ݷ�
//        POL_AI_Block.All[ChnrlCnt]= MaoPao(p2buff);
        POL_AI_Block.All[ChnrlCnt] = AOAI_AadjustDeal(MaoPao(p2buff), YYJ1.OP.Check.AIadjust.All[ChnrlCnt]);

        if ( DebugOut==4 )
        {
            //PRINTF((0,"The %1d Chnrl Value AD = %05d \r\n",ChnrlCnt,POL_AI_Block.All[ChnrlCnt]));
            UINT32 tmpV = POL_AI_Block.All[ChnrlCnt]*3300*3/4096 ;
            //PRINTF((0,"The %1d Chnrl Value AD = %05d \r\n",ChnrlCnt,tmpV));

	    rt_kprintf("The %1d Chnrl Value AD = %05d \r\n", ChnrlCnt,tmpV);
        }

    }
    if ( DebugOut==4 )
    {
        //PRINTF((0,"\r\n\r\n"));
    }
     rt_free(p2buff);//free(pMem)�ͷ�malloc��������Ķ�̬�ڴ�
}





//DebugOut=4







