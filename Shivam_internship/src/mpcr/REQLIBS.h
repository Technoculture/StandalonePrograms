#include <Arduino.h>
#include <Servo.h>

#define SERVOPIN1 9
#define SERVOPIN2 10
#define HOME 90
#define CHAMBER1POS  0
#define CHAMBER2POS 180
#define BAUDRATE 9600
void InterruptFunc();
Servo myservo[2];