#include"REQLIBS.h"

const int SPI_CS_PIN = SPI_PIN;
volatile bool ISR_Flag = 0;
MCP_CAN CAN(SPI_CS_PIN);

uint8_t statemachine = IDLE;

void setup()
{
  pinMode(EXT_INT, INPUT);
  Serial.begin(BAUDRATE);
  attachInterrupt(digitalPinToInterrupt(EXT_INT), FUNCTION, RISING);
  while (!Serial);
  while (CAN_OK != CAN.begin(CAN_500KBPS))
  {
    Serial.println("CAN BUS FAIL!");
    delay(100);
  }
  Serial.println("CAN BUS OK!");
}

unsigned char initialize = 1;                      // CAN data for sending Start 
unsigned char terminate = 2;                       // CAN data for sending Stop

void loop()
{
  switch (statemachine)
  {
    case IDLE:
      {
        unsigned char len = 0;
        unsigned char buf[1];
        if (CAN_MSGAVAIL == CAN.checkReceive())                  // check if can  msg available
        {
          CAN.readMsgBuf(&len, buf);                              // if yes read the msg
          unsigned long canId = CAN.getCanId();
          if (buf[0] == 0)                                       // if msg = 0
          {
            Serial.println("Idle Received");                     // Print Acknowledgement
          }
        }
        if (ISR_Flag)                                           // if ISR_Flag = 1
        {
          statemachine = START;                                  // transit to START state
        }
        else
        {
          statemachine = IDLE;                                  // else transit to IDLE state
        }
      }
      break;

    case START:
      {
        if (ISR_Flag)                                             // if ISR_Flag = 1
        {
          CAN.sendMsgBuf(0xAA, 0, 1, &initialize);              
          Serial.println("Start bit sent");                    // Print Sent Acknowledgment
          ISR_Flag = 0;
          statemachine = RUNNING;                             // transit to RUNNING state
        }
      }
      break;

    case RUNNING:
      {
        unsigned char len = 0;
        unsigned char buf[1];
        if (ISR_Flag)                                            // if ISR_Flag = 1
        {
          statemachine = STOP;                                  // transit to STOP state
        }
        else
        {
          statemachine = RUNNING;                               // transit to RUNNING state
        }

        if (CAN_MSGAVAIL == CAN.checkReceive())                 // check if can  msg available
        {
          CAN.readMsgBuf(&len, buf);
          
          unsigned long canId = CAN.getCanId();
          if (buf[0] == 2)                                        // if CAN data = 2
          {
            Serial.println("EXTRACTION IN PROCESS");
          } 
          else if (buf[0] == 3)                                  // or else if CAN data = 3
          {
            Serial.println("DNA EXTRACTION COMPLETE");
            statemachine = IDLE;
          }
        }
      }
      break;

    case STOP:
      {
        if (ISR_Flag)                                                 // if ISR_Flag = 1
        {
          CAN.sendMsgBuf(0xAA, 0, 1, &terminate);                   // send stop
          Serial.println("STOP BIT SENT");  
          statemachine = IDLE;                                      // transit to IDLE state
          ISR_Flag = 0;                                             // reset ISR_Flag
        }
      }
      break;
  }
}

void FUNCTION()                                          // Every time Interrupt Occurs
{
  ISR_Flag = 1;                                          // Set flag = 1
}


/*
               ┌──────────────┐
               │              │
       ┌───────►     IDLE     ├──────────┐
       │       │              │          │
       │       └──────────────┘          │
       │                                 │
       │                                 │
       │                         ┌───────▼──────┐
┌──────┴───────┐                 │              │
│              │                 │     START    │
│    STOP      │                 │              │
│              │                 └───────┬──────┘
└───────▲──────┘                         │
        │                                │
        │                                │
        │       ┌──────────────┐         │
        │       │              │         │
        └───────┤    RUNNING   ◄─────────┘
                │              │
                └──────────────┘

*/