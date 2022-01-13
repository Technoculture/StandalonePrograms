#include "REQLIBS.h"

const int SPI_CS_PIN = SPIPIN;
MCP_CAN CAN(SPI_CS_PIN);
Servo myservo[2];
unsigned long FutureTime = 0;
unsigned long CurrentTime = 0;
uint8_t estate = IDLE;                           // set initial state to idle
int CYCLE = 1;
bool flag = 0;
volatile int pos = 0;

void setup()
{
  pinMode(ENCA, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(PWMPIN, OUTPUT);
  pinMode(MOTORPIN1, OUTPUT);
  pinMode(MOTORPIN2, OUTPUT);
  pinMode(SERVOPIN1, OUTPUT);
  pinMode(SERVOPIN2, OUTPUT);
  myservo[0].attach(SERVOPIN1);
  myservo[1].attach(SERVOPIN2);
  digitalWrite(MOTORPIN1, LOW);                                          // initially stop
  digitalWrite(MOTORPIN2, LOW);     
  analogWrite(PWMPIN, 0);                                          // disable motor initially
  Serial.begin(BAUDRATE);                                               // set baudrate
  attachInterrupt(digitalPinToInterrupt(ENCA), ENCODER, RISING);

  while (!Serial)
    ;
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
  switch (estate)
  {
  case IDLE:
  {
    // unsigned char len = 0;
    // unsigned char buf[1];
    if (CAN_MSGAVAIL == CAN.checkReceive())                             // check if can msg is available
    {
      estate = START;                                                  // if yes move to START state
    }
    else
    {
      CAN.sendMsgBuf(0xAA, 0, 1, &idle);                             // else simply send idle status to master
      Serial.println("Idle Sent");
      estate = IDLE;                                                     // stay in IDLE
    }
  }
  break;

  case START:
  {
    CAN.readMsgBuf(&len, buf);                                          // read the available mesaage
    // unsigned long canId = CAN.getCanId();
    if (buf[0] == 1)                                                        // if can msg is 1
    {
      Serial.println("----------Start is received------------");
      digitalWrite(LED_BUILTIN, HIGH);                                    // start system by moving
      estate = RUNNING;                                                        // to RUNNING state
    }
    else
    {
      Serial.println("----------ERROR COMMAND------------");                    // if other message
      estate = IDLE;                                                            // move to IDLE state
    }
  }
  break;

  case RUNNING:
  {
    unsigned char len = 0;
    unsigned char buf[1];
    if (CAN_MSGAVAIL == CAN.checkReceive())                               // continuously check for CAN msg
    {
      CAN.readMsgBuf(&len, buf);                                              //  if available read it
      // unsigned long canId = CAN.getCanId();
      if (buf[0] == 2)                                                          // cheeck if msg is 2
      {
        Serial.println("----------Stop is received------------");
        estate = STOP;                                                          // move to STOP state
      }
    }
    else
    {
      CAN.sendMsgBuf(0xAA, 0, 1, &ongoing);                                 // if no CAN msf simply send
      Serial.println("running status sent");                              // system running status to master
      if (CYCLE <= 6)                                                                // count CYCLES
      {
        DOWN();                                                           // execute move DOWN function
        if (flag)                                                                // if flag is set
        {
          estate = STOP;                                                // transit to STOP and break
          break;
        }
        DRIVER();                                                 // set servos to angle according to data
        Serial.print("SERVO SET TO:");                                  // serial print status of cycle
        Serial.println(CYCLE);
        UP();                                                             // execute move UP function
        if (flag)                                                             // if flag is set
        {
          estate = STOP;                                                 // transit to STOP and break
          break;
        }
        Serial.println("EXTRACTING DNA");                                      // Print Status
        CurrentTime = millis();                                                 //   delay
        FutureTime = CurrentTime + DELAY;
        while (millis() <= FutureTime)                                      // while condioton is true
        {
          if (CAN_MSGAVAIL == CAN.checkReceive())
          {
            CAN.readMsgBuf(&len, buf);                                     // check for CAN msg available
            // unsigned long canId = CAN.getCanId();
            if (buf[0] == 2)                                                        // if msg = 2
            {
              Serial.println("System INTERRUPTED while EXTRACTION");
              estate = STOP;                                                // transit to STOP and break
              break;
            }
          }
        }
        if (CYCLE == 6)                                                             // if last cycle
        {
          DOWN();                                                                   // then go DOWN
          myservo[0].write(HOME);                                                 //set servos to home
          myservo[1].write(HOME);
          Serial.println("DNA EXTRACTION COMPLETE");                           // print completion msg
          estate = COMPLETE;                                                 // transit to COMPLETE state
        }
        CYCLE++;                                                                   // increment the cycle
      }
    }
  }
  break;

  case STOP:
  {
    flag = 0;
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("RESETTING");                                                  // print status
    if (digitalRead(SWITCH1) == HIGH)                                    // if motor is somewhere in mid move DOW
    {
      Serial.println("MOVING DOWN");                                         // print status of moving DOWN
      digitalWrite(MOTORPIN1, LOW);                                                  //
      digitalWrite(MOTORPIN2, HIGH);                                        // set motors to move down
      digitalWrite(PWMPIN, HIGH);                                                     //
      estate = STOP;                                                      // transit to STOP state
    }
    else                                                                      // if motor reaches DOWN
    {
      digitalWrite(PWMPIN, LOW);                                                  // then stop
      myservo[0].write(HOME);                                                // set servos at home pos
      myservo[1].write(HOME);
      Serial.println("IDLE STATE");
      estate = IDLE;                                                          // transit to IDLE state
    }
  }
  break;

  case COMPLETE:                                                      // if Process terminates by itself
  {
    CAN.sendMsgBuf(0xAA, 0, 1, &done);                                  // send completion msg to master
    Serial.println("PROCESS COMPLETE");
    CYCLE = 0;                                                            // reset cycle for next iteration
    estate = IDLE;                                                             // transit to IDLE state
  }
  }
}

void DRIVER()                                                 // set servos to diff positions based on cycles
{

  switch (CYCLE)
  {
  case 1:                                                               // first cycle servo positions
    myservo[0].write(30);
    myservo[1].write(30);
    break;

  case 2:                                                               // second cycle servo positions
    myservo[0].write(60);
    myservo[1].write(60);
    break;

  case 3:                                                                 // third cycle servo positions
    myservo[0].write(90);
    myservo[1].write(90);
    break;

  case 4:                                                                 // fourth cycle servo positions
    myservo[0].write(120);
    myservo[1].write(120);
    break;

  case 5:                                                                 // fifth cycle servo positions
    myservo[0].write(150);
    myservo[1].write(150);
    break;

  case 6:                                                                  // last cycle servo positions
    myservo[0].write(180);
    myservo[1].write(180);
    break;

  default:                                                                    // default set to home
    myservo[0].write(HOME);
    myservo[1].write(HOME);
  }
}

void DOWN()                                                                       // DOWN logic
{
  Serial.println("MOVING DOWN");
  while (digitalRead(SWITCH1) == HIGH)                        // while lower limit switch is low do the following
  {
    digitalWrite(MOTORPIN1, LOW);                                                        //
    digitalWrite(MOTORPIN2, HIGH);                                      // command for moving motor down
    digitalWrite(PWMPIN, HIGH);                                                             //
    if (CAN_MSGAVAIL == CAN.checkReceive())                                      // check for CAN msg
    {
      CAN.readMsgBuf(&len, buf);
      // unsigned long canId = CAN.getCanId();
      if (buf[0] == 2)                                                          // if msg is equal to 2
      {
        Serial.println("System INTERRUPTED while going DOWN");             // print the status of interrupt
        flag = 1;                                                                // set flag and break
        break;
      }
    }
  }
  digitalWrite(PWMPIN, LOW);                                                       // stop the motor
}

void UP()
{
  pos = 0;                                                                    // reset pos variable to zero
  Serial.println("MOVING UP");
  while (pos <= TURNS)                                          // while pos is less than Turns do the following
  {
    digitalWrite(MOTORPIN1, HIGH);                                                   //
    digitalWrite(MOTORPIN2, LOW);                                              //  command for moving up
    digitalWrite(PWMPIN, HIGH);                                                       //

    if (CAN_MSGAVAIL == CAN.checkReceive())                               // while running check for can msg
    {
      CAN.readMsgBuf(&len, buf);
      // unsigned long canId = CAN.getCanId();
      if (buf[0] == 2)                                                               // if msg is equal to 2
      {
        Serial.println("System INTERRUPTED while going UP");                      // Print interrupt status
        flag = 1;                                                                 // set flag as 1 and break
        break;
      }
    }
  }
  digitalWrite(PWMPIN, LOW);                                            // if while condition is false stop the motor
}

void ENCODER()                                                                  // when interrupt occurs
{
  pos++;                                                                        // simply increment pos value
}
