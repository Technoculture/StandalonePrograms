#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
const int SPI_CS_PIN = 7;             
MCP_CAN CAN(SPI_CS_PIN);                                   
int flag = 0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    while(!Serial);
    while (CAN_OK != CAN.begin(CAN_500KBPS))   
    {
        Serial.println("CAN BUS FAIL!");
        delay(100);
    }
    Serial.println("CAN BUS OK!");
}

unsigned char idle = 0;


void loop()
{       
    unsigned char len = 0;
    unsigned char buf[1];
    if(CAN_MSGAVAIL == CAN.checkReceive())            
    {
        flag = 1;
        CAN.readMsgBuf(&len, buf);    
        unsigned long canId = CAN.getCanId();
        if(buf[0] == 1)
        {
        Serial.println("Start is received"); 
        digitalWrite(LED_BUILTIN, HIGH);
        }
        else if(buf[0] == 2)
        {
         Serial.println("Stop is received"); 
         digitalWrite(LED_BUILTIN, LOW); 
        }
        else
        {
         Serial.println("LOLs");  
        }
    } 
    else
    {
      if(flag == 0);
      {
       CAN.sendMsgBuf(0xAA, 0, 1, idle);
       Serial.println("Idle bheja"); 
       delay(1000);
      else
      }  
    }
}