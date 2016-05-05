

#include   "includes.h"

#define _PLUS_NUM 100



unsigned long millis()
{
   return 10000;
}
/*Constructor (...)*********************************************************
*    The parameters specified here are those for for which we can't set up
*    reliable defaults, so we need to have the user set them.
 ***************************************************************************/
void PID(uPID *CtrlPid, uPidParaSet *PIDStatus)
{
   SetOutputLimits(CtrlPid, 0, 1000);  //default output limit corresponds to //the arduino pwm limits
   CtrlPid->SampleTime = PIDStatus->SampleTime;      //default Controller Sample Time is 1 seconds
   CtrlPid->DeadBand = PIDStatus->DeadBand;

   SetTunings(CtrlPid, PIDStatus->Kp, PIDStatus->Ki, PIDStatus->Kd);
// SetSampleTime(CtrlPid, PIDStatus->SampleTime);
   CtrlPid->lastTime = CtrlPid->SampleTime / 10;
}
/* Compute() **********************************************************************
 *     This, as they say, is where the magic happens.  this function should be called
 *   every time "void loop()" executes.  the function will decide for itself whether a new
 *   pid Output needs to be computed.  returns true when the output is computed,
 *   false when nothing has been done.
 **********************************************************************************/


unsigned char PIDCompute(uPID *CtrlPid)
{
   if (CtrlPid->lastTime != 0)
   {
      return 0;
   }

///PID(&FC1.FCpid, &FC1.Run.FCpidPar);
   double SampleTimeInSec = ((double)CtrlPid->SampleTime) / 1000;
   CtrlPid->kp = FC1.Run.FCpidPar.Kp;
   CtrlPid->ki =  (int)(FC1.Run.FCpidPar.Ki * SampleTimeInSec);
   CtrlPid->kd = (int)(FC1.Run.FCpidPar.Kd / SampleTimeInSec);
   CtrlPid->DeadBand = FC1.Run.FCpidPar.DeadBand;
   CtrlPid->lastTime = CtrlPid->SampleTime / 10;

   CtrlPid->myInput = FC1.Buff.RoomTemp;


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
         if (tmp <= CtrlPid->DeadBand)
         {
            /*Remember some variables for next time*/
            CtrlPid->lastInput = CtrlPid->myInput;
            return 2;
         }
      }
      else
      {
         if (tmp <= CtrlPid->DeadBand - 1)
         {
            /*Remember some variables for next time*/
            CtrlPid->lastInput = CtrlPid->myInput;
            return 2;
         }
      }

      CtrlPid->ITerm += (CtrlPid->ki * error);
      if ((CtrlPid->ITerm / _PLUS_NUM) > CtrlPid->outMax)
      {
         CtrlPid->ITerm = (long)((long)CtrlPid->outMax * (long)_PLUS_NUM);
      }
      else if ((CtrlPid->ITerm / _PLUS_NUM) < CtrlPid->outMin)
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
         if(output>=0)
         {
          CtrlPid->myOutput = output;
    ///      CtrlPid->myOutput = currentSpeedsET;
         }
         else
         {
          CtrlPid->myOutput = 0;
         }

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
void SetTunings(uPID *CtrlPid, int Kp, int Ki, int Kd)
{
   if (Kp < 0 || Ki < 0 || Kd < 0) return;

   CtrlPid->kp = Kp; CtrlPid->ki = Ki; CtrlPid->kd = Kd;

   if (1)
   {
      double SampleTimeInSec = ((double)CtrlPid->SampleTime) / 1000;
      CtrlPid->kp = Kp;
      CtrlPid->ki =  (int)(Ki * SampleTimeInSec);
      CtrlPid->kd = (int)(Kd / SampleTimeInSec);
   }
}

/* SetSampleTime(...) *********************************************************
 * sets the period, in Milliseconds, at which the calculation is performed	
 ******************************************************************************/
void SetSampleTime(uPID *CtrlPid, int NewSampleTime)
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
void SetOutputLimits(uPID *CtrlPid, int Min, int Max)
{
   if (Min >= Max) return;
   CtrlPid->outMin = Min;
   CtrlPid->outMax = Max;

///if (CtrlPid->Flags.inAuto)
///{
   if (CtrlPid->myOutput > CtrlPid->outMax)
   {
      CtrlPid->myOutput = CtrlPid->outMax;
   }
   else if (CtrlPid->myOutput < CtrlPid->outMin)
   {
      CtrlPid->myOutput = CtrlPid->outMin;
   }

   if ((CtrlPid->ITerm / _PLUS_NUM) > CtrlPid->outMax)
   {
      CtrlPid->ITerm = CtrlPid->outMax * _PLUS_NUM;
   }
   else if ((CtrlPid->ITerm / _PLUS_NUM) < CtrlPid->outMin)
   {
      CtrlPid->ITerm = CtrlPid->outMin * _PLUS_NUM;
   }
///}
}


/* Initialize()****************************************************************
 *	does all the things that need to happen to ensure a bumpless transfer
 *  from manual to automatic mode.
 ******************************************************************************/
void Initialize(uPID *CtrlPid)
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

void SetDeadBand(uPID *CtrlPid, uchar DeadBand)
{
   CtrlPid->DeadBand = DeadBand;
}
/* SetMode(...)****************************************************************
 * Allows the controller Mode to be set to manual (0) or Automatic (non-zero)
 * when the transition from manual to auto occurs, the controller is
 * automatically initialized
 ******************************************************************************/
void SetMode(uPID *CtrlPid, bool Mode)
{
   bool newAuto = (Mode == AUTOMATIC);
   if (newAuto == !CtrlPid->Flags.inAuto)
   {  /*we just went from manual to auto*/
      Initialize(CtrlPid);
   }
   CtrlPid->Flags.inAuto = newAuto;
}

/* SetControllerDirection(...)*************************************************
 * The PID will either be connected to a DIRECT acting process (+Output leads 
 * to +Input) or a REVERSE acting process(+Output leads to -Input.)  we need to
 * know which one, because otherwise we may increase the output when we should
 * be decreasing.  This is called from the constructor.
 ******************************************************************************/
void SetControllerDirection(uPID *CtrlPid, int Direction)
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



