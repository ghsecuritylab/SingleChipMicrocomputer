

#ifndef _74HC165_H_
#define _74HC165_H_
//_165CLK//时钟
//_165PLD //移位/置入控制  为低电平时 并行数据A-H被移入寄存器  为高时：并行置数被禁止
//_165SDO//数据输出

#define  _165PLDto0  GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define  _165PLDto1  GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define  _165CLKto0  GPIO_ResetBits(GPIOA,GPIO_Pin_12)
#define  _165CLKto1  GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define  _165SDOis1  (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)!=0x00)

//  tmp.Bits.Bit0 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10);//CALL
//  tmp.Bits.Bit1 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11);//SPK
//  tmp.Bits.Bit2 = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12);//FIRE
//  tmp.Bits.Bit3 = GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_3);//MP3_BUSY
//  tmp.Bits.Bit4 = GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7);//CPT_ON

#pragma pack (4) /*指定按4字节对齐*/
typedef union
{
   uchar uint08All[8];
   uint16 uint16All[4];
   struct {
      /*00*/     uint08  BOX_PANEL_KEY_RUN:1;                 //本地运行
      /*01*/     uint08  BOX_PANEL_KEY_STANDBY:1;             //本地值机
      /*02*/     uint08  BOX_PANEL_KEY_REMOTE_RUN:1;          //远起使能
      /*03*/     uint08  BOX_PANEL_KEY_REMOTE_STANDBY:1;      //远值使能
      /*04*/     uint08  BOX_PANEL_KEY_EMC_STOP:1;            //门板急停按键
      /*05*/     uint08  FC_FEEDBACK_RUN:1;                   //(反馈)变频运行
      /*06*/     uint08  FC_FEEDBACK_ERROR:1;                 //(反馈)变频故障
      /*07*/     uint08  FF_FEEDBACK_RUN:1;                   //(反馈)定频运行
      /*08*/     uint08  FF_FEEDBACK_ERR:1;                   //(反馈)定频故障  
      /*09*/     uint08  PANEL_KEY_RUN:1;                     //远启动(扩展板)
      /*10*/     uint08  PANEL_KEY_STANDBY:1;                 //远值机(扩展板)
      /*11*/     uint08  PANEL_KEY_NGT:1;                     //远负压(扩展板)
      /*12*/     uint08  INPUT_EMC:1;                         //外急停
      /*13*/     uint08  INPUT_FIRE_EMC:1;                    //消防
      /*14*/     uint08  INPUT_NO_WIND:1;                     //缺风
      /*15*/     uint08  INPUT_CHU_XIAO:1;                    //初效
      /*16*/     uint08  INPUT_WIND_GATE_01:1;                //排风机1
      /*17*/     uint08  INPUT_WIND_GATE_02:1;                //排风机2
      /*18*/     uint08  INPUT_WIND_GATE_03:1;                //排风机3
      /*19*/     uint08  INPUT_WIND_GATE_04:1;                //排风机4
      /*20*/     uint08  INPUT_WIND_GATE_05:1;                //排风机5
      /*21*/     uint08  INPUT_WIND_GATE_06:1;                //排风机6
      /*22*/     uint08  SEL_SEASON_WINTER:1;                 //手动冬天
      /*23*/     uint08  SEL_SEASON_SUMMER:1;                 //手动夏天
      /*28*/     uint08  TRIANGLE_STAR_TIMESET:5;             //时间设定5个拨码开关
      /*31*/     uint08  TRIANGLE_STAR_NOUSED:3;              //不使用3bit
      /*32*/     uint08  INPUT_ZHONG_XIAO:1;                  //中效
      /*33*/     uint08  INPUT_YA_GAO_XIAO:1;                 //亚高效
      /*34*/     uint08  INPUT_GAO_XIAO:1;                    //高效
      /*35*/     uint08  INPUT_HEAT_HIGH_TEMP:1;              //电热高温
      /*36*/     uint08  INPUT_PRE_HEAT_HIGH_TEMP:1;          //预热高温
      /*37*/     uint08  INPUT_WATER_SENSOR:1;                //管温
      /*38*/     uint08  INPUT_COLD_PROTECT:1;                //防冻
      /*39*/     uint08  SEL_STAR_START:1;                    //星形
      /*40*/     uint08  SEL_TRIANGLE_START:1;                //三角形
      /*41*/     uint08  SEL_MODE_FIX_FRQ:1;                  //定频
      /*42*/     uint08  SEL_MODE_FRQ_CVT:1;                  //变频
      /*43*/     uint08  SEL_MODE_MANUAL_FRQ:1;               //变频输出控制选择 1:手动 0:自动
      /*44*/     uint08  SEL_MODE_SPARE_01:1;                 //备用1
      /*45*/     uint08  SEL_MODE_SPARE_02:1;                 //备用2
   }Solo;
}YYJ_DI_DEF;
#pragma pack() /*取消指定对齐，恢复缺省对齐*/


extern YYJ_DI_DEF POL_DI_Block;
extern u8 InputState[6];
extern u8 InputStateRec[6];
extern u8 InputCnt[48];










void Input165();
void InputDeal();





#endif











