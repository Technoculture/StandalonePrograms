#include"REQLIBS.h"

volatile int pos = 0;              // position variable to count enoder pulses
int Pulses = 0;
int angle = 0;
void ENCODER();                           // function Declaration
int degreeToPulse();                      // function Declaration

void setup()
{
 pinMode(ENCA, INPUT); 
 pinMode(MOTPIN1, OUTPUT); 
 pinMode(MOTPIN2, OUTPUT); 
 attachInterrupt(digitalPinToInterrupt(ENCA), ENCODER, RISING);          // if rising pulse occurs at ENCA pin raise interrupt and call the ISR
 Serial.begin(BAUDRATE);
 Serial.setTimeout(DELAY);       // delay time to execute Serial.available data
}

void loop()
{  
  while(Serial.available() > 0)            // while serial data is present
 {
  angle = Serial.parseInt();               // convert string data to integer
  pos = 0;                                 // initilaize pos to 0
 }
 
 Pulses = degreeToPulse(angle);           // call angle to pulse conversion function
  while(pos <= Pulses)                     // rotate the motor while current pos is not equal to Pulses
  {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
  }
    digitalWrite(6, LOW);                  // stop the motor
    digitalWrite(7, LOW);
    
}

void ENCODER()                           // everytime interrupt occurs call and increment "pos"
{
  pos++;
}

int degreeToPulse(int value)                
{
  int y = map(value,0,360,0,1428);        // map value(angle) from 0-360 to 0-1428
  return y;                                // return processed value as pulses to main function
}
