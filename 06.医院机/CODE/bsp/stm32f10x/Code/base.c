#include "Includes.h"

void                                                                                                                                                                                                                                                                                                                                                                                                                                                                          MasterFunctions(int argc,char*argv[])
{
    faUint16 i ;
    for (i = 0; i<argc; i++)
    {
        if ( 0 == strcmp(argv[i],"RTC") )
        {
            uint32 Volume = Asc2Int(argv[i+1]);
            break;
        }
        if ( 0 == strcmp(argv[i],"RTCSET") )
        {
            i++;
            uint16 syear = Asc2Int(argv[i++]);
            uint08 smon = Asc2Int(argv[i++]);
            uint08 sdate = Asc2Int(argv[i++]);
            uint08 shour = Asc2Int(argv[i++]);
            uint08 smin = Asc2Int(argv[i++]);
            uint08 ssec = Asc2Int(argv[i]);
            break;
        }
        if ( 0 == strcmp(argv[i],"DebugOut") )
        {
            DebugOut = Asc2Int(argv[i+1]);
            //PRINTF((0,"DebugOut Level is Set to Level:%02d\r\n",DebugOut));
            break;
        }
        if ( 0 == strcmp(argv[i],"Light") )
        {
            if(i<(argc-1))
            {
                  i++;  
                  Lamps.uint16All[0] = Asc2Int(argv[i]);
            }
            //PRINTF((0,"Light has been Reset!\r\n"));
            break;
        }
        if ( 0 == strcmp(argv[i],"AO") )
        {
            while(i<(argc-1))
            {
                  i++;  
                  POL_AO_Block.All[i-1] = Asc2Int(argv[i]);
            }
            //PRINTF((0,"AO has been Reset!\r\n"));
            break;
        }
        if ( 0 == strcmp(argv[i],"Relay") )
        {
            if(i<(argc-1))
            {
                  i++;  
                  Relays.uint16All[0] = Asc2Int(argv[i]);
            }
            if(i<(argc-1))
            {
                  i++;  
                  Relays.uint16All[1] = Asc2Int(argv[i]);
            }
            if(i<(argc-1))
            {
                  i++;  
                  Relays.uint16All[2] = Asc2Int(argv[i]);
            }
            if(i<(argc-1))
            {
                  Relays.uint16All[3] = Asc2Int(argv[i]);
            }
            //PRINTF((0,"Relay has been Reset!\r\n"));
            return;
        }
    }
      
}







