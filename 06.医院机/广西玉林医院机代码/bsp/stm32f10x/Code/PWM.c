
#include "includes.h"



//const uint16 CCR1_Val = 200-1;
//const uint16 CCR2_Val = 300-1;
//const uint16 CCR3_Val = 400-1;
//const uint16 CCR4_Val = 500-1;

void  T1PWMInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    //调用重映射函数：
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);//开启TIM1 全部重映射

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13|GPIO_Pin_14;  //   T1OC1 T1OC2 T1OC3 T1OC4 引脚输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       
    GPIO_Init(GPIOE, &GPIO_InitStructure);    

    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = PWM_MAX -1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    /* Channel 1, 2,3 and 4 Configuration in PWM mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse = 200;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 300;
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 400;
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 500;
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);

    /* TIM1 counter enable */
    TIM_Cmd(TIM1, ENABLE);

    /* TIM1 Main Output Enable */
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

}


void  T8PWMInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;      //   T8OC1 T8OC2 T8OC3 T8OC4 引脚输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       
    GPIO_Init(GPIOC, &GPIO_InitStructure);  

    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = PWM_MAX -1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

    /* Channel 1, 2,3 and 4 Configuration in PWM mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse = 600;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

    TIM_OC1Init(TIM8, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 700;
    TIM_OC2Init(TIM8, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 800;
    TIM_OC3Init(TIM8, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 900;
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);

    /* TIM1 counter enable */
    TIM_Cmd(TIM8, ENABLE);

    /* TIM1 Main Output Enable */
    TIM_CtrlPWMOutputs(TIM8, ENABLE);

}



void  TIM3CntInit(void)
{

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_Prescaler = 100;
    TIM_TimeBaseStructure.TIM_Period = 720;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* TIM Interrupts enable */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    /* TIM1 counter enable */
    TIM_Cmd(TIM3, ENABLE);
}



