#ifndef __CPT_RUN_H
#define __CPT_RUN_H	



typedef union
{
    uint16 All;
    struct  
    {
        uint16 Cnt:12;             
        uint16 Step:1;         
        uint16 ThisState:1;     
    }Solo;
}CptCtrl_Def;

extern void CptRun();











#endif
