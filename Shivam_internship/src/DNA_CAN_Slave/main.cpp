#include"REQLIBS.h"

unsigned long FutureTime  = 0;
unsigned long CurrentTime = 0;
int CYCLE = 1;
bool flag = 0;
uint8_t estate = IDLE;
const int SPI_CS_PIN = 8;
MCP_CAN CAN(SPI_CS_PIN);
Servo myservo[2];


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SWITCH2, INPUT_PULLUP);
  pinMode(MOTORPIN1, OUTPUT);
  pinMode(MOTORPIN2, OUTPUT);
  pinMode(PWMPIN, OUTPUT);
  pinMode(SERVOPIN1, OUTPUT);
  pinMode(SERVOPIN2, OUTPUT);
  myservo[0].attach(SERVOPIN1);
  myservo[1].attach(SERVOPIN2);
  digitalWrite(MOTORPIN1, LOW);               // initially stop
  digitalWrite(MOTORPIN2, LOW);
  Serial.begin(BAUDRATE);
  while (!Serial);
  while (CAN_OK != CAN.begin(CAN_500KBPS))
  {
    Serial.println("CAN BUS FAIL!");
    delay(100);
  }
  Serial.println("CAN BUS OK!");
}

unsigned char idle = 0;
unsigned char ongoing = 2;
unsigned char done = 3;
unsigned char len = 0;
unsigned char buf[1];

void loop()
{
 switch(estate)
 {
  case IDLE:
  {
    // unsigned char len = 0;
    // unsigned char buf[1];
    if (CAN_MSGAVAIL == CAN.checkReceive())
    {
      estate = START;
    } 
    else
    {
      CAN.sendMsgBuf(0xAA, 0, 1, &idle);
      Serial.println("Idle Sent");
      estate = IDLE;
    }
  }
  break;

  case START:
  {
    CAN.readMsgBuf(&len, buf);
    // unsigned long canId = CAN.getCanId();
    if (buf[0] == 1)
    {
      Serial.println("----------Start is received------------");
      digitalWrite(LED_BUILTIN, HIGH); 
      estate = RUNNING;
    }
    else
    {
      Serial.println("----------ERROR COMMAND------------");
    }
  }
  break;

  case RUNNING:
  {
    unsigned char len = 0;
    unsigned char buf[1];
    if (CAN_MSGAVAIL == CAN.checkReceive())
    {
      CAN.readMsgBuf(&len, buf);
      // unsigned long canId = CAN.getCanId();
      if (buf[0] == 2)
      {
       Serial.println("----------Stop is received------------");
       estate = STOP;
      }
    }
    else
    {
        CAN.sendMsgBuf(0xAA, 0, 1, &ongoing);
        Serial.println("running status sent");
        if (CYCLE <= 6)                              // count CYCLES
          {
           DOWN();                                  // move DOWN
           if(flag)
           {
            estate = STOP;
            break;
           }
           DRIVER();                                // set servos to angle according to data
           Serial.print("SERVO SET TO:");           // serial print status of cycle
           Serial.println(CYCLE);
           UP();                                    // move DOWN
           if(flag)
           {
            estate = STOP;
            break;
           }
           Serial.println("EXTRACTING DNA");
           CurrentTime = millis();                   //   delay
           FutureTime = CurrentTime + DELAY;
           while (millis() <= FutureTime)
            {
//           Serial.println("EXTRACTING DNA");
              if (CAN_MSGAVAIL == CAN.checkReceive())
               {
               CAN.readMsgBuf(&len, buf);
              //  unsigned long canId = CAN.getCanId();
                 if (buf[0] == 2)
                 {
                  Serial.println("System INTERRUPTED while EXTRACTION");
                  estate = STOP;
                  break;
                 }
               }
            }
           if (CYCLE == 6)                                   // if last cycle
           {
             DOWN();                                          // then go DOWN
             myservo[0].write(HOME);                          //set servos to home
             myservo[1].write(HOME);
             Serial.println("DNA EXTRACTION COMPLETE");       // print completion msg
             estate = COMPLETE;
           }
           CYCLE++;                                             // increment the cycle
         }
    }   
  }
  break;

  case STOP:
  {
    flag = 0;
    digitalWrite(LED_BUILTIN, LOW); 
    Serial.println("RESETTING");             // print status
    if (digitalRead(SWITCH1) == HIGH)                    // if motor is somewhere in mid move DOW
    {
      Serial.println("MOVING DOWN");                    // print status of moving DOWN
      digitalWrite(MOTORPIN1, LOW);
      digitalWrite(MOTORPIN2, HIGH);
      analogWrite(PWMPIN, SPEED);
      estate = STOP;
    }
    else                                            // if motor reaches DOWN
    {
      analogWrite(PWMPIN, 0);                           // then stop
      myservo[0].write(HOME);                           // set servos at home pos
      myservo[1].write(HOME);
      Serial.println("IDLE STATE"); 
      estate = IDLE;
    }
   
     
  }
  break;

  case COMPLETE:
  {
    CAN.sendMsgBuf(0xAA, 0, 1, &done);
    Serial.println("PROCESS COMPLETE");
    CYCLE = 0;
    estate = IDLE;
  }
 } 
}


void DRIVER()                                      // set servos to diff positions based on cycles
{

  switch (CYCLE)
  {
    case 1:
      myservo[0].write(30);
      myservo[1].write(30);
      break;

    case 2:
      myservo[0].write(60);
      myservo[1].write(60);
      break;

    case 3:
      myservo[0].write(90);
      myservo[1].write(90);
      break;

    case 4:
      myservo[0].write(120);
      myservo[1].write(120);
      break;

    case 5:
      myservo[0].write(150);
      myservo[1].write(150);
      break;

    case 6:
      myservo[0].write(180);
      myservo[1].write(180);
      break;

    default:
      myservo[0].write(HOME);
      myservo[1].write(HOME);
  }

}

void DOWN()                                             // DOWN logic
{
  Serial.println("MOVING DOWN");
  while (digitalRead(SWITCH1) == HIGH)              // while lower limit switch is low move DOWN

  {
//    Serial.println("MOVING DOWN");
    digitalWrite(MOTORPIN1, LOW);
    digitalWrite(MOTORPIN2, HIGH);
    analogWrite(PWMPIN, SPEED);
    if (CAN_MSGAVAIL == CAN.checkReceive())
    {
      CAN.readMsgBuf(&len, buf);
      // unsigned long canId = CAN.getCanId();
      if (buf[0] == 2)
      {
        Serial.println("System INTERRUPTED while going DOWN");
        flag = 1;
        break;
      }
    }
  }
  analogWrite(PWMPIN, 0);                         // stop the motor
}

void UP()
{
  Serial.println("MOVING UP");
  while (digitalRead(SWITCH2) == HIGH)
  {
//    Serial.println("MOVING UP");
    digitalWrite(MOTORPIN1, HIGH);
    digitalWrite(MOTORPIN2, LOW);
    analogWrite(PWMPIN, SPEED);

    if (CAN_MSGAVAIL == CAN.checkReceive())
    {
      CAN.readMsgBuf(&len, buf);
      // unsigned long canId = CAN.getCanId();
      if (buf[0] == 2)
      {
        Serial.println("System INTERRUPTED while going UP");
       flag = 1;
        break;
      }
    }
  }
  analogWrite(PWMPIN, 0);
}

/*

                   ┌──────────────┐
                   │              │
       ┌──────────►│     IDLE     ├───────────┐
       │           │              │           │
       │           └───────▲──────┘           │
       │                   │                  │
       │            ┌──────┴───────┐          ▼
┌──────┴───────┐    │              │   ┌──────────────┐
│              │    │   COMPLETE   │   │              │
│     STOP     │    │              │   │    START     │
│              │    └──────────────┘   │              │
└──────────────┘           ▲           └──────┬───────┘
       ▲                   │                  │
       │            ┌──────┴─────┐            │
       │            │            │            │
       └────────────┤   RUNNING  │◄───────────┘
                    │            │
                    └────────────┘

*/