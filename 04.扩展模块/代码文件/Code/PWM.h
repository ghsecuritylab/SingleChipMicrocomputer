


#ifndef PWM_H
#define PWM_H


void Timer0_Pwm_Init(void);
void Timer1_Pwm_Init(void);
void Timer2_Pwm_Init(void);

void SetPwm01(uint16 Voltage);
void SetPwm02(uint16 Voltage);
void SetPwm03(uint16 Voltage);
void SetPwm04(uint16 Voltage);

void Pwm_Init(void);
void PWMDeal(Module_All_Def *mode);

void AO_TIMER_PWM(uint16 Voltage, uint08 tmp);
void AO_1AND2AND4_PWM();
void AO3_PWM(uint16 Voltage);

#endif
