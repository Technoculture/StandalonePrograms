#include"REQLIBS.h"

void setup()
{
 pinMode(ENCA, INPUT); 
 pinMode(EXT_INT, INPUT);
 pinMode(MOTPIN1, OUTPUT); 
 pinMode(MOTPIN2, OUTPUT); 
 attachInterrupt(digitalPinToInterrupt(ENCA), ENCODER, RISING);              // interrupt for motor encoder
 attachInterrupt(digitalPinToInterrupt(EXT_INT), FUNCTION, RISING);          //interrupt for push button
 Serial.begin(BAUDRATE);
}

void loop() 
{
  if(flag)                                               // if flag = 1
  {
    if(pos<PULSES)                                         // if pos is less than pulses
    {
      Serial.println(pos);
      digitalWrite(MOTPIN1, HIGH);                          // trigger the motor
      digitalWrite(MOTPIN2, LOW);
    }
    else
    {
      digitalWrite(MOTPIN1, LOW);                         // else stop the motor
      digitalWrite(MOTPIN2, LOW);
    }
  }
  else
  {
    digitalWrite(MOTPIN1, LOW);                     // if no interrupt stop the motor
    digitalWrite(MOTPIN2, LOW);
  }
}

void FUNCTION()                               // executes when external push button interrupt occurs
{ 
  flag = !flag;                               // invert flag
  pos = 0;                                    // clear pos
}

void ENCODER()                               // executes when ENCA interrupt occurs
{
  pos++;                                     // increment pos
}
