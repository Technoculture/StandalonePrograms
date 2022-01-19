
#include <Arduino.h>
#include <Servo.h>
#include <mcp_can.h>
#include <SPI.h>
#define EXT_INT 8
void FUNCTION();

enum state
 {
  IDLE = 0,
  START,
  RUNNING,
  STOP
 };

