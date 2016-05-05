
#include "includes.h"


Adc_fun_Struct_date Adc_fun_date;//ADC保存数据

void ADC_Configuration(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
    /* Enable peripheral clocks ------------------------------------------------*/
    /* Enable DMA1 clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /*------------------使能时钟---------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB |
                           RCC_APB2Periph_AFIO | RCC_APB2Periph_ADC1,ENABLE);        
    /*----------端口配置 模拟输入模式---------*/            
//  已经设置好
//  GPIO_InitTypeDef GPIO_InitStructure;
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
    /*----------端口DMA1_Channel1---------*/  

    /* DMA1 channel1 configuration ----------------------------------------------*/
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&Adc_fun_date.DMA_ADC_PeripheralBaseAddr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 24*7;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    /* Enable DMA1 channel1 */
    DMA_Cmd(DMA1_Channel1, ENABLE);

    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 7;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC1 regular channel14 configuration */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 2, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 4, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 5, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 6, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 7, ADC_SampleTime_239Cycles5);

    /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);

    /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

    /* Enable ADC1 reset calibration register */   
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while ( ADC_GetResetCalibrationStatus(ADC1) );

    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while ( ADC_GetCalibrationStatus(ADC1) );

    /* Start ADC1 Software Conversion */ 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

} 


void PrintVolt()
{
    uint08 tmp;
    uint32 SumValue;
    uint32 AD_value;
    /* Printf message with AD value to serial port */
    //#1 算出平均值电压
    for ( tmp = 0,SumValue = 0;tmp < 16;tmp++ )
    {
        SumValue += Adc_fun_date.DMA_ADC_PeripheralBaseAddr[tmp][0];
    }
    AD_value = SumValue/16;
    if ( DebugOut==2 )
    {
        AD_value = (AD_value*3300/4096);
        //PRINTF((0,"The current AD value1 = %05dV \r\n",AD_value));
    }
    //#2 算出平均值电压
    for ( tmp = 0,SumValue = 0;tmp < 16;tmp++ )
    {
        SumValue += Adc_fun_date.DMA_ADC_PeripheralBaseAddr[tmp][1];
    }
    AD_value = SumValue/16;
    if ( DebugOut==2 )
    {
        AD_value = (AD_value*3300/4096);
        //PRINTF((0,"The current AD value2 = %05dV \r\n",AD_value));
    }
    //#3 算出平均值电压
    for ( tmp = 0,SumValue = 0;tmp < 16;tmp++ )
    {
        SumValue += Adc_fun_date.DMA_ADC_PeripheralBaseAddr[tmp][2];
    }
    AD_value = SumValue/16;
    if ( DebugOut==2 )
    {
        AD_value = (AD_value*3300/4096);
        //PRINTF((0,"The current AD value3 = %05dV \r\n",AD_value));
    }
    //#4 算出平均值电压
    for ( tmp = 0,SumValue = 0;tmp < 16;tmp++ )
    {
        SumValue += Adc_fun_date.DMA_ADC_PeripheralBaseAddr[tmp][3];
    }
    AD_value = SumValue/16;
    if ( DebugOut==2 )
    {
        AD_value = (AD_value*3300/4096);
        //PRINTF((0,"The current AD value4 = %05dV \r\n",AD_value));
    }
    //#5 算出平均值电压
    for ( tmp = 0,SumValue = 0;tmp < 16;tmp++ )
    {
        SumValue += Adc_fun_date.DMA_ADC_PeripheralBaseAddr[tmp][4];
    }
    AD_value = SumValue/16;
    if ( DebugOut==2 )
    {
        AD_value = (AD_value*3300/4096);
        //PRINTF((0,"The current AD value5 = %05dV \r\n",AD_value));
    }
    //#6 算出平均值电压
    for ( tmp = 0,SumValue = 0;tmp < 16;tmp++ )
    {
        SumValue += Adc_fun_date.DMA_ADC_PeripheralBaseAddr[tmp][5];
    }
    AD_value = SumValue/16;
    if ( DebugOut==2 )
    {
        AD_value = (AD_value*3300/4096);
        //PRINTF((0,"The current AD value6 = %05dV \r\n",AD_value));
    }
    //#7 算出平均值电压
    for ( tmp = 0,SumValue = 0;tmp < 16;tmp++ )
    {
        SumValue += Adc_fun_date.DMA_ADC_PeripheralBaseAddr[tmp][6];
    }
    AD_value = SumValue/16;
    if ( DebugOut==2 )
    {
        AD_value = (AD_value*3300/4096);
        //PRINTF((0,"The current AD value7 = %05dV \r\n",AD_value));
    }
    if ( DebugOut == 2 )
    {
        //PRINTF((0,"\r\n\r\n"));
       
    }
}


















