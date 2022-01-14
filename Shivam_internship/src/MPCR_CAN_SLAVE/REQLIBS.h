#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include<Servo.h>

#define SPIPIN 8
#define SERVOPIN1 9
#define SERVOPIN2 10
#define BAUDRATE 115200
#define HOME 90
#define CHAMBER1POS  0
#define CHAMBER2POS 180
#define NUMBER_OF_CYCLES 4
#define CHAMBER1_TEMP 95
#define CHAMBER2_TEMP 55

enum process
{
  IDLE = 0,
  START,
  RUNNING,
  STOP,
  COMPLETE
};