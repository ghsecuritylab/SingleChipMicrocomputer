
#include "includes.h"


typedef union
{
   uchar uint08All[8];
   uint16 uint16All[4];
   struct 
   {
      /*00*/     uint08  BOX_PANEL_KEY_RUN:1;                 //本地运行  (门板)
      /*01*/     uint08  BOX_PANEL_KEY_STANDBY:1;             //本地值机  (门板)
      /*02*/     uint08  BOX_PANEL_KEY_REMOTE_RUN:1;          //远起使能  (门板)
      /*03*/     uint08  BOX_PANEL_KEY_REMOTE_STANDBY:1;      //远值使能  (门板)
      /*04*/     uint08  BOX_PANEL_KEY_EMC_STOP:1;            //门板急停按键
      /*05*/     uint08  FC_FEEDBACK_RUN:1;                   //(反馈)变频运行
      /*06*/     uint08  FC_FEEDBACK_ERROR:1;                 //(反馈)变频故障
      /*07*/     uint08  FF_FEEDBACK_RUN:1;                   //(反馈)定频运行
      /*08*/     uint08  FF_FEEDBACK_ERR:1;                   //(反馈)定频故障
      /*09*/     uint08  PANEL_KEY_RUN:1;                     //远启动(扩展板)
      /*10*/     uint08  PANEL_KEY_STANDBY:1;                 //远值机(扩展板)
      /*11*/     uint08  PANEL_KEY_NGT:1;                     //远负压(扩展板)
      /*12*/     uint08  INPUT_EMC:1;                         //急停按钮
      /*13*/     uint08  INPUT_FIRE_EMC:1;                    //消防(火)
      /*14*/     uint08  INPUT_NO_WIND:1;                     //缺风
      /*15*/     uint08  INPUT_CHU_XIAO:1;                    //初效
      /*16*/     uint08  INPUT_WIND_GATE_01:1;                //排风机1
      /*17*/     uint08  INPUT_WIND_GATE_02:1;                //排风机2
      /*18*/     uint08  INPUT_WIND_GATE_03:1;                //排风机3
      /*19*/     uint08  INPUT_WIND_GATE_04:1;                //排风机4
      /*20*/     uint08  INPUT_WIND_GATE_05:1;                //排风机5
      /*21*/     uint08  INPUT_WIND_GATE_06:1;                //排风机6
      /*22*/     uint08  SEL_SEASON_WINTER:1;                 //手动夏天
      /*23*/     uint08  SEL_SEASON_SUMMER:1;                 //手动冬天
      /*28*/     uint08  TRIANGLE_STAR_TIMESET:5;             //时间设定5个拨码开关
      /*31*/     uint08  TRIANGLE_STAR_NOUSED:3;              //不使用3bit
      /*32*/     uint08  INPUT_ZHONG_XIAO:1;                  //中效
      /*33*/     uint08  INPUT_YA_GAO_XIAO:1;                 //亚高效
      /*34*/     uint08  INPUT_GAO_XIAO:1;                    //高效
      /*35*/     uint08  INPUT_HEAT_HIGH_TEMP:1;              //电高温(热高温)*
      /*36*/     uint08  INPUT_PRE_HEAT_HIGH_TEMP:1;          //预热高温
      /*37*/     uint08  INPUT_WATER_SENSOR:1;                //管温(水,传感器)*
      /*38*/     uint08  INPUT_COLD_PROTECT:1;                //防冻
      /*39*/     uint08  SEL_STAR_START:1;                    //星形
      /*40*/     uint08  SEL_TRIANGLE_START:1;                //三角形
      /*41*/     uint08  SEL_MODE_FIX_FRQ:1;                  //定频
      /*42*/     uint08  SEL_MODE_FRQ_CVT:1;                  //变频
      /*43*/     uint08  SEL_MODE_MANUAL_FRQ:1;               //变频控制电压选择
      /*44*/     uint08  SEL_MODE_SPARE_01:1;                 //备用1
      /*45*/     uint08  SEL_MODE_SPARE_02:1;                 //备用2
		 uint08  SysWorking:1;                        //系统工作状态
   }Solo;
}StatusDef;




extern StatusDef Status;
















