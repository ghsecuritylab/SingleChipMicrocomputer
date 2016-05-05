#ifndef __ADC_H
#define __ADC_H	

#include "stm32f10x.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

void ADC_Configuration(void); 

#pragma pack (2) /*指定按2字节对齐*/ 
typedef struct
{
    uint16 DMA_ADC_PeripheralBaseAddr[24][7];
}Adc_fun_Struct_date;
#pragma pack() /*取消指定对齐，恢复缺省对齐*/






void PrintVolt();
void ADC_Configuration(void);
extern uchar DebugOut;
extern Adc_fun_Struct_date Adc_fun_date;//ADC保存数据



#endif 















