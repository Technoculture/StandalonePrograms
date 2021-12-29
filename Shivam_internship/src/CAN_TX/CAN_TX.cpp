

#include<Arduino.h>
#include <SPI.h>
#include <mcp2515.h>

#define potPin A2
int potValue=0;
struct can_frame canMsg;

MCP2515 mcp2515(10);


void setup() {
  
 // while (!Serial);
  Serial.begin(115200);
  Serial.println("Serial active");
    Serial.println("Spi active");
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS);
  mcp2515.setNormalMode();
  
  canMsg.can_id  = 0x036;
  canMsg.can_dlc = 1;
  
  Serial.println("Example: Write to CAN");
}

void loop() {

 potValue = map(analogRead(potPin),0,1023,0,255);

 canMsg.data[0]=potValue;
 Serial.println(potValue);
 mcp2515.sendMessage(&canMsg);
  delay(100);
} 
