#include <Arduino.h>
#define SWITCH1 4
#define ENCA 2 
#define ENCB 3 
#define ENABLE 5
#define MOTORPIN2 6
#define MOTORPIN1 7
volatile int pos = 0;
void readEncoder();

void setup() 
{
  Serial.begin(9600);
  pinMode(SWITCH1, INPUT);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(ENABLE,OUTPUT);
  pinMode(MOTORPIN1,OUTPUT);
  pinMode(MOTORPIN2,OUTPUT); 
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
}

void loop() 
{
 while(pos <= 3000)
 {
   Serial.println("MOVING UP");
   digitalWrite(MOTORPIN1, HIGH);
   digitalWrite(MOTORPIN2, LOW);
   digitalWrite(ENABLE, HIGH);
 } 

 while(pos >= 3000)
 {
   Serial.println("MOVING DOWN");
   digitalWrite(MOTORPIN1, LOW);
   digitalWrite(MOTORPIN2, HIGH);
   digitalWrite(ENABLE, HIGH);
 }

}

void readEncoder()
{
  int b = digitalRead(ENCB);
  if(b > 0)
  {
    pos++;
  }
  else
  {
    pos--;
  }
}