#include"REQLIBS.h"

const int SPI_CS_PIN = SPI_PIN;
MCP_CAN CAN(SPI_CS_PIN);
volatile bool ISR_Flag = 0;
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

unsigned char initialize = 1;
unsigned char terminate = 2;

void loop()
{
  switch (statemachine)
  {
    case IDLE:
      {
        unsigned char len = 0;
        unsigned char buf[1];
        if (CAN_MSGAVAIL == CAN.checkReceive())                 // check if can msg available
        {
          CAN.readMsgBuf(&len, buf);                            // read CAN msg
          unsigned long canId = CAN.getCanId();
          if (buf[0] == 0)                                      // if can data = 0
          {
            Serial.println("Idle Received");
          }
        }
        if (ISR_Flag)                                           // if ISR_Flag = 1
        {
          statemachine = START;                             // transit to START state
        }
        else
        {
          statemachine = IDLE;                             // transit to IDLE state
        }
      }
      break;

    case START:
      {
        if (ISR_Flag)                                         // if ISR_Flag  = 1
        {
          CAN.sendMsgBuf(0xAA, 0, 1, &initialize);           // send START bit
          Serial.println("Start bit sent");
          ISR_Flag = 0;                                      // Clear ISR_Flag
          statemachine = RUNNING;
        }
      }
      break;

    case RUNNING:
      {
        unsigned char len = 0;
        unsigned char buf[1];
        if (ISR_Flag)                                      // if ISR_Flag  = 1
        {
          statemachine = STOP;                             // transit to STOP state
        }
        else
        {
          statemachine = RUNNING;                       // else transit to RUNNING state
        }

        if (CAN_MSGAVAIL == CAN.checkReceive())            // check if can msg available
        {
          CAN.readMsgBuf(&len, buf);
          if (buf[0] == 2)                                 // if CAN data = 2
          {
            Serial.println("PCR RUNNING");
          }
          else if (buf[0] == 3)                            // or else can data = 3
          {
            Serial.println("PCR COMPLETE");
            statemachine = IDLE;                          // transit to IDLE state
          }
        }
      }
      break;

    case STOP:
      {
        if (ISR_Flag)                                      // if ISR_Flag = 1
        {
          CAN.sendMsgBuf(0xAA, 0, 1, &terminate);         
          Serial.println("STOP BIT SENT");             
          statemachine = IDLE;                          // tranist to IDLE state
          ISR_Flag = 0;
        }
      }
      break;
  }
}

void FUNCTION()                              // executes this function when external interrupt occurs
{
  ISR_Flag = 1;                                 // set ISR_Flag
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
