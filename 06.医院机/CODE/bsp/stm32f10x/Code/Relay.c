

#include "includes.h"


YYJ_DOR_DEF Relays;
YYJ_DOL_DEF Lamps;


void SET_FAN_FC_START(uchar state)//送风机变频 #1
{
//    static uint08 FcStep=0;
//    if(state==0)
//    {
//        GPIO_ResetBits(GPIOD,GPIO_Pin_10);
//        FcStep = 0;
//    }
//    else if(FcStep==0)
//    {
//        if(POL_DI_Block.Solo.SEL_MODE_FRQ_CVT)
//        {
//            FcStep = 1;
//        }
//        else
//        {
//            FcStep = 2;
//        }
//    }
//    else if(FcStep==1)
//    {
//        GPIO_SetBits(GPIOD,GPIO_Pin_10);
//    }
//    else if(FcStep==2)
//    {
//        GPIO_ResetBits(GPIOD,GPIO_Pin_10);
//    }
/***************************************/
   if (state==0)
   {
      GPIO_ResetBits(GPIOD,GPIO_Pin_10);
   }
   else
   {
      GPIO_SetBits(GPIOD,GPIO_Pin_10);
   }
/***************************************/
}


#define SET_STAR_OFF GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define SET_STAR_ON  GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define SET_FAN_FF_OFF GPIO_ResetBits(GPIOD,GPIO_Pin_11)
#define SET_FAN_FF_ON  GPIO_SetBits(GPIOD,GPIO_Pin_11)

void SET_FAN_FF_START(uchar state)//送风机定频 #2
{
//    static uint08 StarStep = 0;
//    static uint16 StarChangeTimer = 0;
//
//    if(state==0)
//    {
//        SET_STAR_OFF;
//        SET_FAN_FF_OFF;
//        StarStep = 0;
//    }
//    else if(StarStep==0)
//    {
//        if(POL_DI_Block.Solo.SEL_MODE_FIX_FRQ)
//        {
//            if(POL_DI_Block.Solo.SEL_STAR_START)
//            {
//                StarStep=1;
//                SET_STAR_ON;
//                StarChangeTimer = (POL_DI_Block.uint08All[3]&0x01F)*200;
//            }
//            else
//            {
//                StarStep=2;
//            }
//        }
//        else
//        {
//            StarStep = 3;
//        }
//    }
//    else if(StarStep==1)
//    {
//        SET_STAR_ON;
//        SET_FAN_FF_ON;
//        if(StarChangeTimer-- ==0)
//        {
//            StarStep = 2;
//        }
//    }
//    else if(StarStep==2)
//    {
//        SET_STAR_OFF;
//        SET_FAN_FF_ON;
//    }
//    else if(StarStep==3)
//    {
//        SET_STAR_OFF;
//        SET_FAN_FF_OFF;
//    }
/***************************************/
   if (state==0)
   {
      GPIO_ResetBits(GPIOD,GPIO_Pin_11);
   }
   else
   {
      GPIO_SetBits(GPIOD,GPIO_Pin_11);
   }
/***************************************/
}

void SET_FAN_TRIANGLE_START(uchar state)//送风机三角形 #3
{
    return;
}

void SET_FAN_STAR_START(uchar state)//送风机星形 #4
{
//    return;
/***************************************/
   if (state==0)
   {
      GPIO_ResetBits(GPIOD,GPIO_Pin_12);
   }
   else
   {
      GPIO_SetBits(GPIOD,GPIO_Pin_12);
   }
/***************************************/
}


void SET_FAN_COOLER(uchar state)//送风机散热风扇 #5
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_13);
    }
    else
    {   
        GPIO_SetBits(GPIOD,GPIO_Pin_13);
    }
}


void SET_EHEAT_LV01(uchar state)//一级再热 #6
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_14);
    }
    else
    {   
        GPIO_SetBits(GPIOB,GPIO_Pin_14);
    }
}

void SET_EHEAT_LV02(uchar state)//二级再热 #7
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_12);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_12);
    }
}

void SET_EHEAT_LV03(uchar state)//三级再热 #8
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_8);
    }
    else
    {   
        GPIO_SetBits(GPIOD,GPIO_Pin_8);
    }
}

void SET_PREHEAT_LV01(uchar state)//一级预热 #9
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_8);
    }
    else
    {   
        GPIO_SetBits(GPIOA,GPIO_Pin_8);
    }
}

void SET_PREHEAT_LV02(uchar state)//二级预热 #10
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    }
    else
    {   
        GPIO_SetBits(GPIOB,GPIO_Pin_12);
    }
}

void SET_PREHEAT_LV03(uchar state)//三级预热 #11
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_13);
    }
    else
    {   
        GPIO_SetBits(GPIOB,GPIO_Pin_13);
    }
}

void SET_BOX_COOLER(uchar state)//电柜自用散热风扇 #12
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_12);
    }
    else
    {   
        GPIO_SetBits(GPIOE,GPIO_Pin_12);
    }
}

void SET_STOP_WARMING(uchar state)//停机保温 #13
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_7);
    }
    else
    {   
        GPIO_SetBits(GPIOE,GPIO_Pin_7);
    }
}

void SET_NGT_PRESS(uchar state)//负压排风 #14
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_10);
    }
    else
    {   
        GPIO_SetBits(GPIOE,GPIO_Pin_10);
    }
}

void SET_SHA_JUN_DENG(uchar state)//杀菌灯 #15
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_8);
    }
    else
    {   
        GPIO_SetBits(GPIOE,GPIO_Pin_8);
    }
}

void SET_AUTO_GATES_01(uchar state)//排风机自动门1 #16
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_11);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_11);
    }
}

void SET_AUTO_GATES_02(uchar state)//排风机自动门2 #17
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_13);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_13);
    }
}

void SET_AUTO_GATES_03(uchar state)//排风机自动门3 #18
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_14);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_14);
    }
}

void SET_AUTO_GATES_04(uchar state)//排风机自动门4 #19
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_15);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_15);
    }
}

void SET_AUTO_GATES_05(uchar state)//排风机自动门5 #20
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_0);
    }
    else
    {   
        GPIO_SetBits(GPIOG,GPIO_Pin_0);
    }
}

void SET_AUTO_GATES_06(uchar state)//排风机自动门6 #21
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_1);
    }
    else
    {   
        GPIO_SetBits(GPIOG,GPIO_Pin_1);
    }
}

void SET_NOTHING(uchar state)
{
    return;
}

void SET_FC_CTRL_SPARE(uchar state)//(变频器控制)备用 #22
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_5);
    }
    else
    {   
        GPIO_SetBits(GPIOG,GPIO_Pin_5);
    }
}

void SET_FRESH_AIR_GATE_FIX(uchar state)//新风机定量风阀 #23
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_9);
    }
    else
    {   
        GPIO_SetBits(GPIOD,GPIO_Pin_9);
    }
}

void SET_FRESH_AIR_GATE_TIGHT(uchar state)//新风机密闭阀 #24
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_15);
    }
    else
    {   
        GPIO_SetBits(GPIOB,GPIO_Pin_15);
    }
}


void SET_FC_CTRL_START(uchar state)//(变频器控制)开启 #25
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_7);
    }
    else
    {   
        GPIO_SetBits(GPIOG,GPIO_Pin_7);
    }
}


void SET_FC_CTRL_STANDBY(uchar state)//(变频器控制)值机 #26
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_6);
    }
    else
    {   
        GPIO_SetBits(GPIOG,GPIO_Pin_6);
    }
}

void SET_HIGH_TEMP_CHAIN(uchar state)//高温连锁 #27
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_4);
    }
    else
    {   
        GPIO_SetBits(GPIOG,GPIO_Pin_4);
    }
}


void SET_NO_WIND_CHAIN(uchar state)//缺风连锁 #28
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_3);
    }
    else
    {   
        GPIO_SetBits(GPIOG,GPIO_Pin_3);
    }
}

void SET_HUMIDIFIER_GATE(uchar state)//加湿器电磁阀 #29
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_14);
    }
    else
    {   
        GPIO_SetBits(GPIOD,GPIO_Pin_14);
    }
}

void SET_HUMIDIFIER_START(uchar state)//加湿器开关 #30
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_15);
    }
    else
    {   
        GPIO_SetBits(GPIOD,GPIO_Pin_15);
    }
}

void SET_HUMIDIFIER_CHAIN(uchar state)//加湿器互锁 #31
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_2);
    }
    else
    {   
        GPIO_SetBits(GPIOG,GPIO_Pin_2);
    }
}
/****************扩展板************************/
void SET_PANEL_RUN(uchar state)//(扩展板)运行 #32
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_1);
    }
    else
    {   
        GPIO_SetBits(GPIOC,GPIO_Pin_1);
    }
}

void SET_PANEL_STANDBY(uchar state)//(扩展板)值机 #33
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_0);
    }
    else
    {   
        GPIO_SetBits(GPIOC,GPIO_Pin_0);
    }
}

void SET_PANEL_FILTER(uchar state)//(扩展板)滤网 #34
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_2);
    }
    else
    {   
        GPIO_SetBits(GPIOC,GPIO_Pin_2);
    }
}

void SET_PANEL_ERR(uchar state)//(扩展板)故障 #35
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_3);
    }
    else
    {   
        GPIO_SetBits(GPIOC,GPIO_Pin_3);
    }
}

/**********************门板硬接线************************/
void SET_LAMP_AHU_RUNNING(uchar state)// #1
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_1);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_1);
    }
}


void SET_LAMP_AHU_STANDBY(uchar state)// #2
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_2);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_2);
    }
}


void SET_LAMP_EX01(uchar state)// #3
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOD,GPIO_Pin_3);
    }
    else
    {   
        GPIO_SetBits(GPIOD,GPIO_Pin_3);
    }
}

void SET_LAMP_AHU_ERROR(uchar state)// #4
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_8);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_8);
    }
}

void SET_LAMP_AHU_NOWIND(uchar state)// #5
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_5);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_5);
    }
}

void SET_LAMP_AHU_CHU_XIAO(uchar state)// #6
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_7);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_7);
    }
}

void SET_LAMP_AHU_ZHONG_XIAO(uchar state)// #7
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_6);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_6);
    }
}

void SET_LAMP_AHU_YA_GAO_XIAO(uchar state)// #8
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_4);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_4);
    }
}


void SET_LAMP_AHU_GAO_XIAO(uchar state)// #9
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_3);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_3);
    }
}


void SET_LAMP_AHU_EHEAT_HIGH(uchar state)// #10
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_6);
    }
    else
    {   
        GPIO_SetBits(GPIOE,GPIO_Pin_6);
    }
}

void SET_LAMP_AHU_PREHEAT_HIGH(uchar state)// #11
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOF,GPIO_Pin_0);
    }
    else
    {   
        GPIO_SetBits(GPIOF,GPIO_Pin_0);
    }
}

void SET_LAMP_AHU_COLD_ERR(uchar state)// #12
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_5);
    }
    else
    {   
        GPIO_SetBits(GPIOE,GPIO_Pin_5);
    }
}

void SET_LAMP_AHU_COLD_STOP_ERR(uchar state)// #13
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_2);
    }
    else
    {   
        GPIO_SetBits(GPIOE,GPIO_Pin_2);
    }
}

void SET_LAMP_AHU_EXTERN_EMC_ERR(uchar state)// #14
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_3);
    }
    else
    {   
        GPIO_SetBits(GPIOE,GPIO_Pin_3);
    }
}

void SET_LAMP_AHU_FIRE_ERR(uchar state)// #15
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOE,GPIO_Pin_4);
    }
    else
    {   
        GPIO_SetBits(GPIOE,GPIO_Pin_4);
    }
}

void SET_LAMP_EX02(uchar state)// #16
{
    if(state==0)
    {
        GPIO_ResetBits(GPIOG,GPIO_Pin_8);
    }
    else
    {   
        GPIO_SetBits(GPIOG,GPIO_Pin_8);
    }
}

//指针数组指向带参数返回空类型函数
void (* const LampTasks[16])(uchar state) =
{
/*00*/  SET_LAMP_AHU_RUNNING,                         
/*01*/  SET_LAMP_AHU_STANDBY,                         
/*02*/  SET_LAMP_EX01,                                
/*03*/  SET_LAMP_AHU_ERROR,                           
/*04*/  SET_LAMP_AHU_NOWIND,                          
/*05*/  SET_LAMP_AHU_CHU_XIAO,                        
/*06*/  SET_LAMP_AHU_ZHONG_XIAO,                      
/*07*/  SET_LAMP_AHU_YA_GAO_XIAO,                     
/*08*/  SET_LAMP_AHU_GAO_XIAO,                        
/*09*/  SET_LAMP_AHU_EHEAT_HIGH,                      
/*10*/  SET_LAMP_AHU_PREHEAT_HIGH,                    
/*11*/  SET_LAMP_AHU_COLD_ERR,                        
/*12*/  SET_LAMP_AHU_COLD_STOP_ERR,                   
/*13*/  SET_LAMP_AHU_EXTERN_EMC_ERR,                  
/*14*/  SET_LAMP_AHU_FIRE_ERR,                        
/*15*/  SET_LAMP_EX02,   
};


void (* const RelayTasks[48])(uchar state) =
{
/*00*/   SET_FAN_FC_START,          
/*01*/   SET_FAN_FF_START,          
/*02*/   SET_FAN_TRIANGLE_START,    
/*03*/   SET_FAN_STAR_START,        
/*04*/   SET_FAN_COOLER,            
/*05*/   SET_EHEAT_LV01,            
/*06*/   SET_EHEAT_LV02,            
/*07*/   SET_EHEAT_LV03,            
/*08*/   SET_PREHEAT_LV01,           
/*09*/   SET_PREHEAT_LV02,           
/*10*/   SET_PREHEAT_LV03,           
/*11*/   SET_BOX_COOLER,            
/*12*/   SET_STOP_WARMING,          
/*13*/   SET_NGT_PRESS,             
/*14*/   SET_SHA_JUN_DENG,   
/*15*/   SET_NOTHING,       
/*16*/   SET_AUTO_GATES_01,         
/*17*/   SET_AUTO_GATES_02,         
/*18*/   SET_AUTO_GATES_03,         
/*19*/   SET_AUTO_GATES_04,         
/*20*/   SET_AUTO_GATES_05,         
/*21*/   SET_AUTO_GATES_06,   
         SET_NOTHING,
         SET_NOTHING,      
         SET_NOTHING,      
         SET_NOTHING,      
         SET_NOTHING,  
         SET_NOTHING,
         SET_NOTHING,      
         SET_NOTHING,      
         SET_NOTHING,      
         SET_NOTHING,              
/*22*/   SET_FC_CTRL_SPARE,         
/*23*/   SET_FRESH_AIR_GATE_FIX,    
/*28*/   SET_FRESH_AIR_GATE_TIGHT,  
/*31*/   SET_FC_CTRL_START,         
/*32*/   SET_FC_CTRL_STANDBY,       
/*33*/   SET_HIGH_TEMP_CHAIN,       
/*34*/   SET_NO_WIND_CHAIN,         
/*35*/   SET_HUMIDIFIER_GATE,       
/*36*/   SET_HUMIDIFIER_START,      
/*37*/   SET_HUMIDIFIER_CHAIN,      
/*38*/   SET_PANEL_RUN,             
/*39*/   SET_PANEL_STANDBY,         
/*40*/   SET_PANEL_FILTER,          
/*41*/   SET_PANEL_ERR,     
/*42*/   SET_NOTHING,
/*43*/   SET_NOTHING,   
};
   
//指向函数的指针函数 
void Run_void(void (*ptask)()) 
{  
   (*ptask)();  
} 
void Run_uchar(void (*ptask)(uchar),uchar state)
{  
   (*ptask)(state);  
} 

//OutPutPoll()
void RelayAll(uchar RelayNum, uchar state)//指向数组
{
    Run_uchar(RelayTasks[RelayNum],state);  // call target function
}

void LightAll(uchar RelayNum, uchar state)//指向数组
{
    Run_uchar(LampTasks[RelayNum],state);  // call target function
}

//ReadBits

void OutPutPoll()
{
    uint08 tmp;
    for(tmp=0;tmp<48;tmp++)//35个输出控制
    {
        RelayAll(tmp,ReadBits(Relays.uint08All,tmp));
    }
    for(tmp=0;tmp<16;tmp++)//门板16个LED显示控制
    {
        LightAll(tmp,ReadBits(Lamps.uint08All,tmp));
    }
}


















