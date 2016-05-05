

#ifndef _PWM_H_
#define _PWM_H_

#define PWM_TIM   TIM8
#define PWM_TIM_1 TIM1
#define PWM_TIM_8 TIM8
#define PWM_MAX   1024
void T1PWMInit();
void T8PWMInit();
void TIM3CntInit(void);

#endif
