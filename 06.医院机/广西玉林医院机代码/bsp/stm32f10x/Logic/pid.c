/**********************************************************************************************
 * Arduino PID Library - Version 1.0.1
 * by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#include "includes.h"


void PIDStructInit(uPID *CtrlPid, uPidParaSet *PIDStatus)
{
   SetOutputLimits(CtrlPid, 0, 1024);  //default output limit corresponds to //the arduino pwm limits 默认输出限制
   CtrlPid->SampleTime = PIDStatus->SampleTime;      //default Controller Sample Time is 1 seconds 采样时间1s
   CtrlPid->DeadBand = PIDStatus->DeadBand;  //死区

   SetTunings(CtrlPid, PIDStatus->Kp, PIDStatus->Ki, PIDStatus->Kd); //调节参数
// SetSampleTime(CtrlPid, PIDStatus->SampleTime);
   CtrlPid->lastTime = CtrlPid->SampleTime;
}


unsigned char Compute(uPID *CtrlPid)
{
   if (CtrlPid->Flags.inAuto == 0) return 0;

   if (CtrlPid->lastTime > 0)
   {
      CtrlPid->lastTime--;
   }

   if (CtrlPid->lastTime != 0)
   {
      return 0;
   }
   CtrlPid->lastTime = CtrlPid->SampleTime;


// if (timeChange >= CtrlPid->SampleTime)
   if (1)
   {
      /*Compute all the working error variables*/
      int input = CtrlPid->myInput;
      int error =  input - CtrlPid->mySetpoint;
      int tmp = error;
      if (CtrlPid->Flags.controllerDirection == 0)
      {
         error = 0 - error;
         tmp = error;
      }

      if (tmp < 0)
      {
         tmp = -tmp;
      }
      if (tmp <= CtrlPid->DeadBand)
      {
         /*Remember some variables for next time*/
         CtrlPid->lastInput = CtrlPid->myInput;
         return 1;
      }

      CtrlPid->ITerm += (CtrlPid->ki * error);
      if (CtrlPid->ITerm > (CtrlPid->outMax * _PLUS_NUM))
      {
         CtrlPid->ITerm = (CtrlPid->outMax * _PLUS_NUM);
      }
      else if (CtrlPid->ITerm < (CtrlPid->outMin * _PLUS_NUM))
      {
         CtrlPid->ITerm = (CtrlPid->outMin * _PLUS_NUM);
      }


      {
         /*Compute PID Output*/
         long dInput;
         long output;
         dInput =  (long)(CtrlPid->lastInput - CtrlPid->myInput);
         if (CtrlPid->Flags.controllerDirection == 0)
         {
            dInput = 0 - dInput;
         }
         output = (long)CtrlPid->kp * error  +  (long)CtrlPid->ITerm -  (long)CtrlPid->kd * dInput;
         output = output / 100;
         if (output > CtrlPid->outMax)
         {
            output = CtrlPid->outMax;
         }
         else if (output <  CtrlPid->outMin)
         {
            output = CtrlPid->outMin;
         }
         CtrlPid->myOutput = output;

         /*Remember some variables for next time*/
         CtrlPid->lastInput = CtrlPid->myInput;
         return 1;
      }
   }
   else
   {
      return 0;
   }
}


/* SetTunings(...)*************************************************************
 * This function allows the controller's dynamic performance to be adjusted. 
 * it's called automatically from the constructor, but tunings can also
 * be adjusted on the fly during normal operation
 ******************************************************************************/
void SetTunings(uPID *CtrlPid, int Kp, int Ki, int Kd) //设置调节参数
{
   if (Kp < 0 || Ki < 0 || Kd < 0) return;

   CtrlPid->kp = Kp; CtrlPid->ki = Ki; CtrlPid->kd = Kd;

   if (1)
   {
      double SampleTimeInSec = ((double)CtrlPid->SampleTime) / 1000;
      CtrlPid->kp = Kp;
      CtrlPid->ki = Ki * (int)SampleTimeInSec;
      CtrlPid->kd = Kd / (int)SampleTimeInSec;
   }
}

/* SetSampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed	
 ******************************************************************************/
void SetSampleTime(uPID *CtrlPid, int NewSampleTime) //设置采样时间
{
   if (NewSampleTime > 0)
   {
      double ratio  = (double)NewSampleTime
         / (double)CtrlPid->SampleTime;
      CtrlPid->ki *= ratio;
      CtrlPid->kd /= ratio;
      CtrlPid->SampleTime = (unsigned int)NewSampleTime;
   }
}

/* SetOutputLimits(...)****************************************************
 *     This function will be used far more often than SetInputLimits.  while
 *  the input to the controller will generally be in the 0-1023 range (which is
 *  the default already,)  the output will be a little different.  maybe they'll
 *  be doing a time window and will need 0-8000 or something.  or maybe they'll
 *  want to clamp it from 0-125.  who knows.  at any rate, that can all be done
 *  here.
 **************************************************************************/
void SetOutputLimits(uPID *CtrlPid, int Min, int Max) //设置输出限制
{
   if (Min >= Max) return;
   CtrlPid->outMin = Min;
   CtrlPid->outMax = Max;

   if (CtrlPid->Flags.inAuto)
   {
      if (CtrlPid->myOutput > CtrlPid->outMax)
      {
         CtrlPid->myOutput = CtrlPid->outMax;
      }
      else if (CtrlPid->myOutput < CtrlPid->outMin)
      {
         CtrlPid->myOutput = CtrlPid->outMin;
      }

      if (CtrlPid->ITerm > CtrlPid->outMax * _PLUS_NUM)
      {
         CtrlPid->ITerm = CtrlPid->outMax * _PLUS_NUM;
      }
      else if (CtrlPid->ITerm < CtrlPid->outMin * _PLUS_NUM)
      {
         CtrlPid->ITerm = CtrlPid->outMin * _PLUS_NUM;
      }
   }
}


/* Initialize()****************************************************************
 *	does all the things that need to happen to ensure a bumpless transfer 
 *  from manual to automatic mode.
 ******************************************************************************/
void Initialize(uPID *CtrlPid) //初始化
{
   CtrlPid->ITerm = CtrlPid->myOutput;
   CtrlPid->lastInput = CtrlPid->myInput;
   if (CtrlPid->ITerm > CtrlPid->outMax * _PLUS_NUM)
   {
      CtrlPid->ITerm = CtrlPid->outMax * _PLUS_NUM;
   }
   else if (CtrlPid->ITerm < CtrlPid->outMin * _PLUS_NUM)
   {
      CtrlPid->ITerm = CtrlPid->outMin * _PLUS_NUM;
   }
}

void SetDeadBand(uPID *CtrlPid, uchar DeadBand) //设置死区
{
   CtrlPid->DeadBand = DeadBand;
}
/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)   设置PID为自动或者手动模式。
 * when the transition from manual to auto occurs, the controller is 当从手动到自动的过渡时,控制器是自动初始化
 * automatically initialized
 ******************************************************************************/
void SetMode(uPID *CtrlPid, bool Mode) //设置模式
{
   BOOL newAuto = (Mode == AUTOMATIC);
   if (newAuto == !CtrlPid->Flags.inAuto)
   {  /*we just went from manual to auto*/
      Initialize(CtrlPid); //从手动到自动
   }
   CtrlPid->Flags.inAuto = newAuto;
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads 
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void SetControllerDirection(uPID *CtrlPid, int Direction) //设置控制方向
{
//    if (CtrlPid->Flags.inAuto && Direction != CtrlPid->Flags.controllerDirection)
////  if (Direction != CtrlPid->Flags.controllerDirection)
//   {
//      CtrlPid->kp = (0 - CtrlPid->kp);
//      CtrlPid->ki  = (0 - CtrlPid->ki);
//      CtrlPid->kd = (0 - CtrlPid->kd);
//   }
   CtrlPid->Flags.controllerDirection = Direction;
}

/* Status Funcions*************************************************************
 * Just because you set the Kp=-1 doesn't mean it actually happened.  these
 * functions query the internal state of the PID.  they're here for display 
 * purposes.  this are the functions the PID Front-end uses for example
 ******************************************************************************/
int GetKp(uPID *CtrlPid) { return  CtrlPid->kp; }
int GetKi(uPID *CtrlPid)  { return  CtrlPid->ki;}
int GetKd(uPID *CtrlPid) { return  CtrlPid->kd;}
int GetMode(uPID *CtrlPid) { return  CtrlPid->Flags.inAuto ? AUTOMATIC : MANUAL;}
int GetDirection(uPID *CtrlPid) { return CtrlPid->Flags.controllerDirection;}


////__no_init 是一个SEGMENT,是给LINKER用的,定义到不初始化的块中去



void PidPar_Init(uPID *pid, uPidParaSet *par, uint08 dir)
{
   par->Kp = 10;
   par->Ki = 10;
   par->Kd = 10;
   par->DeadBand = 10;
   par->SampleTime = 1000;
   PIDStructInit(pid, par);
   pid->Flags.controllerDirection = dir;
   Initialize(pid);
}


void PID_Init()
{
   PidPar_Init(&YYJ1.PID.RHpid, &YYJ1.OP.RHpid, DIRECT); // 0 正向 1 反向
   PidPar_Init(&YYJ1.PID.RHpidInv, &YYJ1.OP.RHpidInv, REVERSE);
   PidPar_Init(&YYJ1.PID.Hotpid, &YYJ1.OP.Hotpid, DIRECT);
   PidPar_Init(&YYJ1.PID.Coolpid, &YYJ1.OP.Coolpid, REVERSE);
   PidPar_Init(&YYJ1.PID.Freqpid, &YYJ1.OP.Freqpid, DIRECT);

   YYJ1.PID.RHpidInv.mySetpoint = 50 * 10;
   YYJ1.PID.RHpid.mySetpoint = 50 * 10;
   YYJ1.PID.Coolpid.mySetpoint = 25 * 10;
   YYJ1.PID.Hotpid.mySetpoint = 25 * 10;
   YYJ1.PID.Freqpid.mySetpoint = 30 * 10;
}


//void PIDSave()
//{
//   pid->Flags.inAuto = 1;
//   DoFlashSave(&ParSave);
////   PID(pid, par);
//}















