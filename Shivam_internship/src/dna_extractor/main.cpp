#include <Arduino.h>
#include <Servo.h>
#define EXT_INTERRUPT 12
#define LIM_SWITCH_PIN1 7
#define LIM_SWITCH_PIN2 8
#define MOTORPIN1 9
#define MOTORPIN2 10
#define SERVOPIN1 11
#define SERVOPIN2 12
#define HOME 0                       

Servo myservo[2];
volatile bool INT_FLAG = LOW;
void InterruptFunc();
int chamber = 10;

void setup() 
{
pinMode(EXT_INTERRUPT,    INPUT);          // external interrupt pin
pinMode(LIM_SWITCH_PIN1, INPUT);           // lower limit switch
pinMode(LIM_SWITCH_PIN2, INPUT);           // upper limit switch
pinMode(MOTORPIN1,      OUTPUT);
pinMode(MOTORPIN2,      OUTPUT); 
pinMode(SERVOPIN1,      OUTPUT);           // servo1
pinMode(SERVOPIN2,      OUTPUT);           // servo2
myservo[0].attach(SERVOPIN1); 
myservo[1].attach(SERVOPIN2);
myservo[0].write(HOME);                     // by default stay at home
myservo[1].write(HOME);                     // by default stay at home
digitalWrite(MOTORPIN1, LOW);               // initially stop
digitalWrite(MOTORPIN2, LOW);               // initially stop
attachInterrupt(digitalPinToInterrupt (EXT_INTERRUPT), InterruptFunc, FALLING);
}

void loop() 
{
  if(INT_FLAG == 1)                   // if interrupt occurs make flag 1 and start system
  {
    for(chamber = 10 ; chamber <= 60 ; chamber = chamber + 10)
    { 
      while(digitalRead(LIM_SWITCH_PIN1)!= LOW)
      {
       digitalWrite(MOTORPIN1, HIGH);       // move down            
       digitalWrite(MOTORPIN2, LOW);
      }
      myservo[0].write(chamber);            // set servo to chamber 1       
      myservo[1].write(chamber);
      while(digitalRead(LIM_SWITCH_PIN2)!= LOW)
      {
       digitalWrite(MOTORPIN1, LOW);       // move up            
       digitalWrite(MOTORPIN2, HIGH);                                                     
      }
      delay(10000);
    }
  }
  else                                         // if no interrupt   
  {                                           
   myservo[0].write(HOME);                    // move servo at home position
   myservo[1].write(HOME);                     
    if(digitalRead(LIM_SWITCH_PIN1) == HIGH)      // if limit switch is open 
    {
      digitalWrite(MOTORPIN1, HIGH);                // drive motor downwards
      digitalWrite(MOTORPIN2, LOW);
    }
    else                                           // if limit switch closed
    {
      digitalWrite(MOTORPIN1, LOW);               // stop the motor
      digitalWrite(MOTORPIN2, LOW);
    } 
  }
}

void InterruptFunc()
{
  INT_FLAG = !INT_FLAG;                        // toggle interrupt flag
}