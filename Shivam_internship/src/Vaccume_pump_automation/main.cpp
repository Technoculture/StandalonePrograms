#include<Arduino.h>
#define TRIGGERPIN 8
//#define state_STOP 0
//#define state_RUN  1
unsigned long RUN_DURATION = 300000;
unsigned long STOP_DURATION = 60000;
bool motor_state = 0;
unsigned long PREVIOUS_TIME = 0;
unsigned long CURRRENT_TIME = 0;
unsigned long DURATION = RUN_DURATION;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TRIGGERPIN, OUTPUT);
  digitalWrite(TRIGGERPIN, motor_state);
  digitalWrite(LED_BUILTIN, !motor_state);
}

void loop()
{
  CURRRENT_TIME = millis();
  if ( CURRRENT_TIME - PREVIOUS_TIME >=  DURATION )
  {
    motor_state = !motor_state;
    
    digitalWrite(LED_BUILTIN, !motor_state);
    digitalWrite(TRIGGERPIN, motor_state);
    if(DURATION == RUN_DURATION) 
     { 
      DURATION = STOP_DURATION;
     }
    else
     {
      DURATION = RUN_DURATION;
     }
      
    PREVIOUS_TIME = CURRRENT_TIME;
  }
Serial.println(motor_state);
}