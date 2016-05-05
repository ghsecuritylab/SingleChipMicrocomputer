

#ifndef PID_v1_h
#define PID_v1_h

#include "includes.h"

#define LIBRARY_VERSION	1.0.0
#define AUTOMATIC	1
#define MANUAL	0
#define DIRECT  0
#define REVERSE  1

typedef struct
{
//  int Input;
//  int Output;
//  int Setpoint;
   int Kp;
   int Ki;
   int Kd;
   int SampleTime;
   int DeadBand;
}uPidParaSet;


typedef struct
{
   uchar inAuto:1;
   uchar controllerDirection:1;
   uchar Write:1;
   uchar Read:1;
}PID_FLAG;

typedef struct
{
//  int dispKp;				// * we'll hold on to the tuning parameters in user-entered
//  int dispKi;				//   format for display purposes
//  int dispKd;				//
   int kp;                  // * (P)roportional Tuning Parameter
   int ki;                  // * (I)ntegral Tuning Parameter
   int kd;                  // * (D)erivative Tuning Parameter
   int SampleTime;
   int myInput;              // * Pointers to the Input, Output, and Setpoint variables
   int myOutput;             //   This creates a hard link between the variables and the
   int mySetpoint;           //   PID, freeing the user from having to constantly tell us
                             //   what these values are.  with pointers we'll just know.
   long ITerm;
   int	lastInput;
   int lastTime;
   int outMin;
   int outMax;
   PID_FLAG Flags;
   uchar DeadBand;
}uPID;





//commonly used functions **************************************************************************
//  PID(double*, double*, double*,        // * constructor.  links the PID to the Input, Output, and
//      double, double, double, int);     //   Setpoint.  Initial tuning parameters are also set here
extern void PID(uPID *CtrlPid, uPidParaSet *PIDStatus);

//  void SetMode(int Mode);               // * sets PID to either Manual (0) or Auto (non-0)
extern void SetMode(uPID *CtrlPid, bool Mode);

//  bool Compute();                       // * performs the PID calculation.  it should be
//                                        //   called every time loop() cycles. ON/OFF and
//                                        //   calculation frequency can be set using SetMode
//                                        //   SetSampleTime respectively
extern unsigned char PIDCompute(uPID *CtrlPid);

//  void SetOutputLimits(double, double); //clamps the output to a specific range. 0-255 by default, but
//  									  //it's likely the user will want to change this depending on
//  									  //the application

extern void SetOutputLimits(uPID *CtrlPid, int Min, int Max);

//available but not commonly used functions ********************************************************
//  void SetTunings(double, double,       // * While most users will set the tunings once in the
//                  double);         	  //   constructor, this function gives the user the option
//                                        //   of changing tunings during runtime for Adaptive control
//  void SetControllerDirection(int);	  // * Sets the Direction, or "Action" of the controller. DIRECT
//  									  //   means the output will increase when error is positive. REVERSE
//  									  //   means the opposite.  it's very unlikely that this will be needed
//  									  //   once it is set in the constructor.
//  void SetSampleTime(int);              // * sets the frequency, in Milliseconds, with which
//                                        //   the PID calculation is performed.  default is 100

extern void SetTunings(uPID *CtrlPid, int kp, int ki, int kd);
extern void SetControllerDirection(uPID *CtrlPid, int direction);
extern void SetSampleTime(uPID *CtrlPid, int NewSampleTime);




//Display functions ****************************************************************
//  double GetKp();						  // These functions query the pid for interal values.
//  double GetKi();						  //  they were created mainly for the pid front-end,
//  double GetKd();						  // where it's important to know what is actually
//  int GetMode();						  //  inside the PID.
//  int GetDirection();					  //
//  void Initialize();

extern int GetKp(uPID *CtrlPid);
extern int GetKi(uPID *CtrlPid);
extern int GetKd(uPID *CtrlPid);
extern int GetMode(uPID *CtrlPid);
extern int GetDirection(uPID *CtrlPid);
extern void Initialize(uPID *CtrlPid);
extern unsigned long millis();
#endif




