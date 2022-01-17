#include<Arduino.h>
#define ENCA 2
#define EXT_INT 3
#define MOTPIN1 6
#define MOTPIN2 7
#define PULSES 3000
#define BAUDRATE 115200
volatile bool flag = 0;
volatile int pos = 0;
void FUNCTION();
void ENCODER();