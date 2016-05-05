

#ifndef RELAY_H
#define RELAY_H


typedef union
{
    uint08 uint08All[8];
    uint16 uint16All[4];
    struct  
    {
/*00*/   uint16 FAN_FC_START:1;//送风机变频
/*01*/   uint16 FAN_FF_START:1;//送风机定频
/*02*/   uint16 FAN_TRIANGLE_START:1;//送风机三角形
/*03*/   uint16 FAN_STAR_START:1;//送风机星形
/*04*/   uint16 FAN_COOLER:1;//送风机散热风扇
/*05*/   uint16 EHEAT_LV01:1;//一级再热
/*06*/   uint16 EHEAT_LV02:1;//二级再热
/*07*/   uint16 EHEAT_LV03:1;//三级再热
/*08*/   uint16 REHEAT_LV01:1;//一级预热
/*09*/   uint16 REHEAT_LV02:1;//二级预热
/*10*/   uint16 REHEAT_LV03:1;//三级预热
/*11*/   uint16 BOX_COOLER:1;//电柜自用散热风扇
/*12*/   uint16 STOP_WARMING:1;//停机保温
/*13*/   uint16 NGT_PRESS:1;//负压排风
/*14*/   uint16 SHA_JUN_DENG:1;//杀菌灯
         uint16 UNUSED02:1;//未使用                                                                                                                                            
/*15*/   uint16 AUTO_GATES_01:1;//排风机自动门1
/*16*/   uint16 AUTO_GATES_02:1;//排风机自动门2
/*17*/   uint16 AUTO_GATES_03:1;//排风机自动门3
/*18*/   uint16 AUTO_GATES_04:1;//排风机自动门4
/*19*/   uint16 AUTO_GATES_05:1;//排风机自动门5
/*20*/   uint16 AUTO_GATES_06:1;//排风机自动门6
         uint16 AUTO_GATES_UNUSED01:1;//未使用
         uint16 AUTO_GATES_UNUSED02:1;//未使用
         uint16 AUTO_GATES_UNUSED03:1;//未使用
         uint16 AUTO_GATES_UNUSED04:1;//未使用
         uint16 AUTO_GATES_UNUSED05:1;//未使用
         uint16 AUTO_GATES_UNUSED06:1;//未使用
         uint16 AUTO_GATES_UNUSED07:1;//未使用
         uint16 AUTO_GATES_UNUSED08:1;//未使用
         uint16 AUTO_GATES_UNUSED09:1;//未使用
         uint16 AUTO_GATES_UNUSED10:1;//未使用
/*21*/   uint16 FC_CTRL_SPARE:1;//(变频器控制)备用
/*22*/   uint16 FRESH_AIR_GATE_FIX:1;//新风机定量风阀
/*23*/   uint16 FRESH_AIR_GATE_TIGHT:1;//新风机密闭阀
/*24*/   uint16 FC_CTRL_START:1;//(变频器控制)开启
/*25*/   uint16 FC_CTRL_STANDBY:1;//(变频器控制)值机:1  全速:0
/*26*/   uint16 HIGH_TEMP_CHAIN:1;//高温连锁
/*27*/   uint16 NO_WIND_CHAIN:1;//缺风连锁 
/*28*/   uint16 HUMIDIFIER_GATE:1;//加湿器电磁阀
/*29*/   uint16 HUMIDIFIER_START:1;//加湿器开关
/*30*/   uint16 HUMIDIFIER_CHAIN:1;//加湿器互锁
/*31*/   uint16 PANEL_RUN:1;//(扩展板)运行
/*32*/   uint16 PANEL_STANDBY:1;//(扩展板)值机
/*33*/   uint16 PANEL_FILTER:1;//(扩展板)滤网
/*34*/   uint16 PANEL_ERR:1;//(扩展板)故障
    }Solo;
}YYJ_DOR_DEF;


typedef union  //AHU状态与故障指示
{
    uint08 uint08All[2];
    uint16 uint16All[1];
    struct  
    {
/*00*/ uint16 LAMP_AHU_RUNNING:1;//机组运行灯 
/*01*/ uint16 LAMP_AHU_STANDBY:1;//机组值机灯
/*02*/ uint16 LAMP_EX01:1;//备用1
/*03*/ uint16 LAMP_AHU_ERROR:1;//机组故障灯
/*04*/ uint16 LAMP_AHU_NOWIND:1;//缺风报警灯
/*05*/ uint16 LAMP_AHU_CHU_XIAO:1;//初效报警灯
/*06*/ uint16 LAMP_AHU_ZHONG_XIAO:1;//中效报警灯
/*07*/ uint16 LAMP_AHU_YA_GAO_XIAO:1;//亚高效报警灯
/*08*/ uint16 LAMP_AHU_GAO_XIAO:1;//高效报警灯
/*09*/ uint16 LAMP_AHU_EHEAT_HIGH:1;//电热高温报警灯
/*10*/ uint16 LAMP_AHU_PREHEAT_HIGH:1;//预热高温报警灯
/*11*/ uint16 LAMP_AHU_COLD_ERR:1;//防冻报警灯
/*12*/ uint16 LAMP_AHU_COLD_STOP_ERR:1;//防冻停机报警灯
/*13*/ uint16 LAMP_AHU_EXTERN_EMC_ERR:1;//外接急停报警灯
/*14*/ uint16 LAMP_AHU_FIRE_ERR:1;//消防报警灯
    }Solo;
}YYJ_DOL_DEF;

typedef struct 
{
   YYJ_DOR_DEF Relay;
   YYJ_DOL_DEF Light;
}YYJ_DO_DEF;





//extern uint08 ReadBits(uint08 *p2data, uint08 index);
//extern void WriteBits(uint08 *p2data, uint08 index, uint08 bits);
extern void OutPutPoll();
extern void Run_uchar(void (*ptask)(uchar),uchar state); 
extern void Run_void(void (*ptask)()); 
extern void RelayAll(uchar RelayNum, uchar state);
extern YYJ_DOR_DEF Relays;
extern YYJ_DOL_DEF Lamps;
#endif












