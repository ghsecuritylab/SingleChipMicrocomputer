
#ifndef _PID_h
#define _PID_h


#define LIBRARY_VERSION	1.0.0
#define AUTOMATIC	1
#define MANUAL	0
#define DIRECT  0
#define REVERSE  1
//#define bool unsigned char
#define uchar unsigned char
#define ulong unsigned long
#define _PLUS_NUM 100



typedef signed short sint16;
typedef signed int sint32;
typedef signed long sint64;


typedef struct
{
    sint16 Kp;
    sint16 Ki;
    sint16 Kd;
    sint16 SampleTime;
    sint16 DeadBand;
   
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
   sint16 kp;                  // * (P)roportional Tuning Parameter
   sint16 ki;                  // * (I)ntegral Tuning Parameter
   sint16 kd;                  // * (D)erivative Tuning Parameter
   sint32 SampleTime;
   sint32 DeadBand;
   sint32 myInput;             // * Pointers to the Input, Output, and Setpoint variables  
   sint32 myOutput;            //   This creates a hard link between the variables and the
   sint32 mySetpoint;          //   PID, freeing the user from having to constantly tell us
                               //   what these values are.  with pointers we'll just know.
   sint64 ITerm;
   sint32 lastInput;
   sint32 lastTime;
   sint32 outMin,outMax;
   PID_FLAG Flags;
}uPID;





extern void PIDStructInit(uPID *CtrlPid, uPidParaSet *PIDStatus);
extern void SetMode(uPID *CtrlPid, bool Mode);
extern unsigned char Compute(uPID *CtrlPid);
extern void SetOutputLimits(uPID *CtrlPid, int Min, int Max);
extern void SetTunings(uPID *CtrlPid, int kp, int ki, int kd);
extern void SetControllerDirection(uPID *CtrlPid, int direction);
extern void SetSampleTime(uPID *CtrlPid, int NewSampleTime);

extern int GetKp(uPID *CtrlPid);
extern int GetKi(uPID *CtrlPid);
extern int GetKd(uPID *CtrlPid);
extern int GetMode(uPID *CtrlPid);
extern int GetDirection(uPID *CtrlPid);
extern void Initialize(uPID *CtrlPid);
extern unsigned long millis();




void PidPar_Init(uPID *pid,uPidParaSet *par,uint08 dir);
void PID_Init();




#endif




