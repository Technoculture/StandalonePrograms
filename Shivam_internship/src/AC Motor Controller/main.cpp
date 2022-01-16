#include<Arduino.h>
#define TRIGGERPIN 7

long RUN_DELAY  = 3600000;
long STOP_DELAY = 900000;
unsigned long RUNNING_FUTURE_TIME = 0;
unsigned long RUNNING_CURRRENT_TIME = 0;
unsigned long HALT_FUTURE_TIME = 0;
unsigned long HALT_CURRRENT_TIME = 0;

void setup() 
{
 pinMode(LED_BUILTIN, OUTPUT);
 pinMode(TRIGGERPIN, OUTPUT);
 digitalWrite(TRIGGERPIN, LOW);
}

void loop() 
{
 RUNNING_CURRRENT_TIME = millis();
 RUNNING_FUTURE_TIME = RUNNING_CURRRENT_TIME + RUN_DELAY;
 while( millis() <= RUNNING_FUTURE_TIME )
 {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(TRIGGERPIN, HIGH);
 }

 HALT_CURRRENT_TIME = millis();
 HALT_FUTURE_TIME = RUNNING_FUTURE_TIME + STOP_DELAY;
 while( millis() <= HALT_FUTURE_TIME )
 {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(TRIGGERPIN, LOW);
 } 
}
