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

void setup()
{
 pinMode(ENCA, INPUT); 
 pinMode(EXT_INT, INPUT);
 pinMode(MOTPIN1, OUTPUT); 
 pinMode(MOTPIN2, OUTPUT); 
 attachInterrupt(digitalPinToInterrupt(ENCA), ENCODER, RISING);
 attachInterrupt(digitalPinToInterrupt(EXT_INT), FUNCTION, RISING);
 Serial.begin(BAUDRATE);
}

void loop() 
{
  if(flag)
  {
    if(pos<PULSES)
    {
      Serial.println(pos);
      digitalWrite(MOTPIN1, HIGH);
      digitalWrite(MOTPIN2, LOW);
    }
    else
    {
      digitalWrite(MOTPIN1, LOW);
      digitalWrite(MOTPIN2, LOW);
    }
  }
  else
  {
    digitalWrite(MOTPIN1, LOW);
    digitalWrite(MOTPIN2, LOW);
  }
}

void FUNCTION()
{
  flag = !flag;
  pos = 0;
}

void ENCODER()
{
  pos++;
}
