#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>
#include <Servo.h>

#define ENCA 2                     // encoder pin of N20 Motor
#define PWMPIN 3                   // PWMA of TB6112fmg motor driver
#define SWITCH1 4                  //lower limit switch
#define SPIPIN 8                   // Chip select pin of MCP2515
#define MOTORPIN1 6                // motor terminal 1
#define MOTORPIN2 7                // motor terminal 2
#define SERVOPIN1 9                // 1st servo signal pin on Due
#define SERVOPIN2 10               // 2nd servo signal pin on Due
#define BAUDRATE 115200            // Baudrate
#define DELAY 5000                 // Extraction time delay in milliseconds
#define HOME 0                     // Servo home position 0 degree
#define TURNS 3000                 // N20 base motor turn for 2 rounds

void DOWN();
void UP();
void DRIVER();
void ENCODER();

enum process
{
  IDLE = 0,
  START,
  RUNNING,
  STOP,
  COMPLETE
};