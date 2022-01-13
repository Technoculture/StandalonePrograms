#include<Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include<Servo.h>
#define PWMPIN    3
#define SWITCH1   4             //lower limit switch
#define SWITCH2   5             //upper limit switch 
#define MOTORPIN1 6
#define MOTORPIN2 7
#define SERVOPIN1 9
#define SERVOPIN2 10
#define BAUDRATE 115200
#define DELAY 5000
#define HOME 0
#define SPEED 200
void DOWN();
void UP();
void DRIVER();

enum process
{
  IDLE = 0,
  START,
  RUNNING,
  STOP,
  COMPLETE
};