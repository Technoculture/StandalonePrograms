#include<Arduino.h>

#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);


void setup() {
  SPI.begin(10);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA");
}

void loop() {
 if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
 if(canMsg.can_id== 0x036){
    int x=canMsg.data[0];
    Serial.print(" Pot Value ");
    Serial.println(x);
    Serial.println(); 
    delay(200);     
  }
 }
 Serial.println("No MSG");
}
