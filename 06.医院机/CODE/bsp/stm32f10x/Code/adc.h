#ifndef __ADC_H
#define __ADC_H	

#include "stm32f10x.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

void ADC_Configuration(void); 

#pragma pack (2) /*ָ����2�ֽڶ���*/ 
typedef struct
{
    uint16 DMA_ADC_PeripheralBaseAddr[24][7];
}Adc_fun_Struct_date;
#pragma pack() /*ȡ��ָ�����룬�ָ�ȱʡ����*/






void PrintVolt();
void ADC_Configuration(void);
extern uchar DebugOut;
extern Adc_fun_Struct_date Adc_fun_date;//ADC��������



#endif 















