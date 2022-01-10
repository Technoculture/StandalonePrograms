#include <Arduino.h>
#include <Servo.h>
#include <mcp_can.h>
#include <SPI.h>
#define EXT_INT 8
const int SPI_CS_PIN = 7;
volatile uint8_t statemachine = IDLE;
volatile bool pushbISRflag = 0;
MCP_CAN CAN(SPI_CS_PIN);
void FUNCTION();

enum state
 {
  IDLE = 0,
  START,
  RUNNING,
  STOP
 };


void setup()
{
  pinMode(EXT_INT, INPUT);
  Serial.begin(115200);
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
      unsigned char len = 0;
      unsigned char buf[1];
      if (CAN_MSGAVAIL == CAN.checkReceive())
       {
        CAN.readMsgBuf(&len, buf);
        unsigned long canId = CAN.getCanId();
         if (buf[0] == 0)
         {
          Serial.println("idle mila");
         }
       }
       break;
       
   case START:
    if(pushbISRflag)
      {
      CAN.sendMsgBuf(0xAA, 0, 1, &start);
      Serial.println("start bit bheja");
      pushbISRflag = 0;
      }
      break;

   case RUNNING:
      unsigned char len = 0;
      unsigned char buf[1];
      if (CAN_MSGAVAIL == CAN.checkReceive())
       {
        CAN.readMsgBuf(&len, buf);
        unsigned long canId = CAN.getCanId();
         if (buf[0] == 2)
         {
          Serial.println("Running mila");
         }
       }
       break;
       
   case STOP:
    if(pushbISRflag)
      {
      CAN.sendMsgBuf(0xAA, 0, 1, &halt);
      Serial.println("stop bit bheja");
      statemachine = IDLE;
      pushbISRflag = 0;
      }
     break;     
  }
}

void FUNCTION()
{
  statemachine++;
  pushbISRflag = 1;
}