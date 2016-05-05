
//下以操作前提是port可写入
#define RevBit(port, bitn)           (port ^=  (1<<(bitn)))                            
#define SetBit(port, bitn)           (port |=  (1<<(bitn)))                                
#define ClrBit(port, bitn)           (port &= ~(1<<(bitn)))                               
#define GetBit(port, bitn)           (port &   (1<<(bitn)))                              
#define OutBit(port, bitn, value)    ((value) ? (SetBit(port, bitn)) : (ClrBit(port, bitn)))
#define BIT(bitn) (1<<bitn)