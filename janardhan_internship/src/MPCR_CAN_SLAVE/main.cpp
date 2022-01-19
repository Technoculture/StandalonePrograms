#include"REQLIBS.h"

Servo myservo[2];
const int thermocouple = A2;                            // Analog pin of Arduino Due
unsigned long FutureTime  = 0;
unsigned long CurrentTime = 0;
const int SPI_CS_PIN = SPIPIN;
MCP_CAN CAN(SPI_CS_PIN);
int CYCLE = 0;
bool flag = 0;
int adc_val = 0;
float temp = 0;
int temperature = 0;
uint8_t estate = IDLE;

void setup()
{
  pinMode(SERVOPIN1, OUTPUT);
  pinMode(SERVOPIN2, OUTPUT);
  myservo[0].attach(SERVOPIN1);
  myservo[1].attach(SERVOPIN2);
  myservo[0].write(HOME);
  myservo[1].write(HOME);
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
  switch (estate)
  {
    case IDLE:
      {
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
        //    unsigned long canId = CAN.getCanId();
        if (buf[0] == 1)
        {
          Serial.println("----------Start is received------------");
          digitalWrite(LED_BUILTIN, HIGH);
          estate = RUNNING;
        }
        else
        {
          Serial.println("----------ERROR COMMAND------------");
          estate = IDLE;
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
          if (CYCLE <= NUMBER_OF_CYCLES)                              // count CYCLES
          {
            myservo[0].write(CHAMBER1POS);         //enter in chamber 1
            myservo[1].write(CHAMBER1POS);         //enter in chamber 1

            adc_val = analogRead(thermocouple);
            temp = map(adc_val, 0, 1023 , 0 , 100 );
            //  y = ( ((adc_val * 4.88) - 0.0027 ) / 10.0 );
            temperature = (temp);
            // temperature = round(y);
            if (temperature <= CHAMBER1_TEMP)        //compare chamber temp to reference
            {
              myservo[0].write(CHAMBER1POS);          // if true stay in chamber 1
              myservo[1].write(CHAMBER1POS);
              Serial.println("waiting in chamber 1");
              Serial.print("Chamber 1 temp:");      //else print
              Serial.println(temperature);
              
            }
            else
            {
              myservo[0].write(CHAMBER2POS);             //move to chamber two
              myservo[1].write(CHAMBER2POS);
              Serial.println("In chamber 2");       
              goto in;
in:
              if (temperature > 53)                    //wait until temperature is less than 55
              {
                Serial.println("Waiting in ch2");        
                myservo[0].write(CHAMBER2POS);           // if true stay in chamber 2
                myservo[1].write(CHAMBER2POS);
                adc_val = analogRead(thermocouple);
                temp = map(adc_val, 0, 1023 , 0 , 100 );
                //  y = ( ((adc_val * 4.88) - 0.0027 ) / 10.0 );
                temperature = (temp);
                Serial.print("ch2 temp");                
                Serial.println(temperature);    
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
                if (temperature <= CHAMBER2_TEMP)
                {
                  Serial.println(temperature);        
                  goto out;
                }
                else
                {
                  goto in;
                }
              }
out:                                           
              if (CYCLE == NUMBER_OF_CYCLES)
              {
                estate = COMPLETE;
                break;
              }
             CYCLE++;                          // increment the cycle
            }
                                           
          }
          estate = RUNNING;
        }
      }
      break;

    case STOP:
      {
        CYCLE = 0;
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("PCR INTERRUPTED");             // print status
        myservo[0].write(HOME);
        myservo[1].write(HOME);
        estate = IDLE;
      }
      break;

    case COMPLETE:
      {
        CAN.sendMsgBuf(0xAA, 0, 1, &done);
        Serial.println("PROCESS COMPLETE");
        CYCLE = 0;
        estate = IDLE;
      }
      break;

  }

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
