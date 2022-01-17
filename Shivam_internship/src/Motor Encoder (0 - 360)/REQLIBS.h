#include<Arduino.h>
#define ENCA 2                       // encoder pin of N20 Motor on due pin 2
#define MOTPIN1 6                    
#define MOTPIN2 7              
#define BAUDRATE 115200
#define DELAY 100                   // delay response of serial read

void ENCODER();                           // function Declaration
int degreeToPulse();                      // function Declaration