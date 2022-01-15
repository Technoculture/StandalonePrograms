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
        if (CAN_MSGAVAIL == CAN.checkReceive())
        {
          CAN.readMsgBuf(&len, buf);
          unsigned long canId = CAN.getCanId();
          if (buf[0] == 0)
          {
            Serial.println("Idle Received");
          }
        }
        if (ISR_Flag)
        {
          statemachine = START;
        }
        else
        {
          statemachine = IDLE;
        }
      }
      break;

    case START:
      {
        if (ISR_Flag)
        {
          CAN.sendMsgBuf(0xAA, 0, 1, &initialize);
          Serial.println("Start bit sent");
          ISR_Flag = 0;
          statemachine = RUNNING;
        }
      }
      break;

    case RUNNING:
      {
        unsigned char len = 0;
        unsigned char buf[1];
        if (ISR_Flag)
        {
          statemachine = STOP;
        }
        else
        {
          statemachine = RUNNING;
        }

        if (CAN_MSGAVAIL == CAN.checkReceive())
        {
          CAN.readMsgBuf(&len, buf);


          
          unsigned long canId = CAN.getCanId();
          if (buf[0] == 2)
          {
            Serial.println("EXTRACTION IN PROCESS");
          }
          else if (buf[0] == 3)
          {
            Serial.println("DNA EXTRACTION COMPLETE");
            statemachine = IDLE;
          }
        }
      }
      break;

    case STOP:
      {
        if (ISR_Flag)
        {
          CAN.sendMsgBuf(0xAA, 0, 1, &terminate);
          Serial.println("STOP BIT SENT");
          statemachine = IDLE;
          ISR_Flag = 0;
        }
      }
      break;
  }
}

void FUNCTION()
{
  ISR_Flag = 1;
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