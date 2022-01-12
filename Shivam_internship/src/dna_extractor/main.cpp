#include<REQLIBS.h>
unsigned long FutureTime  = 0;
unsigned long CurrentTime = 0;
volatile bool flag = 0;
void FUNCTION();
void DOWN();
void UP();
void DRIVER();
int CYCLE = 1;
Servo myservo[2];

void setup() 
{
 pinMode(SWITCH1, INPUT);
 pinMode(SWITCH2, INPUT); 
 pinMode(INTERRUPT, INPUT);
 pinMode(MOTORPIN1, OUTPUT);
 pinMode(MOTORPIN2, OUTPUT); 
 pinMode(PWMPIN, OUTPUT);
 pinMode(SERVOPIN1, OUTPUT);
 pinMode(SERVOPIN2, OUTPUT); 
 myservo[0].attach(SERVOPIN1);       
 myservo[1].attach(SERVOPIN2);            
 digitalWrite(MOTORPIN1, LOW);               // initially stop
 digitalWrite(MOTORPIN2, LOW); 
 attachInterrupt(digitalPinToInterrupt (INTERRUPT), FUNCTION, RISING);
 Serial.begin(BAUDRATE);
}

void loop() 
{
 if(flag==1)                                // if interrupt occurs externally
  {
    if(CYCLE <=6)                                // count CYCLES
    {
       DOWN();                                  // move DOWN
      
       DRIVER();                                // set servos to angle according to data
       Serial.print("SERVO SET TO:");           // serial print status of cycle
       Serial.println(CYCLE);
       UP();                                    // move DOWN
      
       CurrentTime = millis();                   //   delay 
       FutureTime = CurrentTime + DELAY;         
       while(millis() <= FutureTime)
       {
         Serial.println("EXTRACTING DNA");
         if(flag!= 1)
        {
          Serial.println("INTERRUPT OCCURED");
          break;
        }
       } 
       if(CYCLE == 6)                                    // if last cycle
       {   
          DOWN();                                          // then go DOWN
        
          myservo[0].write(HOME);                          //set servos to home
          myservo[1].write(HOME);                          
          Serial.println("DNA EXTRACTION COMPLETE");       // print completion msg
       }
    CYCLE++;                                             // increment the cycle
    }   
  }
 else                                                   // if interrupt not occured
  {
     Serial.println("INTERRUPT NOT OCCURED");             // print status
     if(digitalRead(SWITCH1) == LOW)                     // if motor is somewhere in mid move DOWN
    
     {                                           
      Serial.println("MOVING DOWN");                    // print status of moving DOWN
    
      digitalWrite(MOTORPIN1, LOW);
      digitalWrite(MOTORPIN2, HIGH);
      digitalWrite(PWMPIN, HIGH); 
     }
     else                                              // if motor reaches DOWN
     
     {
      digitalWrite(PWMPIN,0);                            // then stop
      myservo[0].write(HOME);                           // set servos at home pos
      myservo[1].write(HOME);  
      Serial.println("IDLE STATE");                   // print status as idle
     }
  }
  
}

void FUNCTION()                                      // if interrupt occurs
{
  flag = !flag;                                     // toggle flag state
}

void DRIVER()                                      // set servos to diff positions based on cycles
{
  
  switch(CYCLE)
  {
    case 1:
    myservo[0].write(CYCLE);
    myservo[1].write(CYCLE);
    break;

    case 2:
    myservo[0].write(CYCLE);
    myservo[1].write(CYCLE);
    break;

    case 3:
    myservo[0].write(CYCLE);
    myservo[1].write(CYCLE);
    break;

    case 4:
    myservo[0].write(CYCLE);
    myservo[1].write(CYCLE);
    break;

    case 5:
    myservo[0].write(CYCLE);
    myservo[1].write(CYCLE);
    break;

    case 6:
    myservo[0].write(CYCLE);
    myservo[1].write(CYCLE);
    break;

    default:
    myservo[0].write(HOME);
    myservo[1].write(HOME);
  }
  
}

void DOWN()                                             // DOWN logic
{
      while(digitalRead(SWITCH1) == LOW)               // while lower limit switch is low move DOWN
    
      {
       Serial.println("MOVING DOWN");
       digitalWrite(MOTORPIN1, LOW);
       digitalWrite(MOTORPIN2, HIGH);
       digitalWrite(PWMPIN,HIGH); 
       if(flag!= 1)                                   // amid this, if interrupt occurs 
        {
        Serial.print("INTERRUPT OCCURED");             // then print and break 
        break; 
        }  
      }     
      digitalWrite(PWMPIN,0);                          // stop the motor
}

void UP()
{
    while(digitalRead(SWITCH2) == LOW)
      {
      Serial.println("MOVING UP");
      digitalWrite(MOTORPIN1, HIGH);
      digitalWrite(MOTORPIN2, LOW);
      digitalWrite(PWMPIN,HIGH);

       if(flag!= 1)
       {
        Serial.print("INTERRUPT OCCURED");
        break; 
       }  
      }
      digitalWrite(PWMPIN,0);
}
