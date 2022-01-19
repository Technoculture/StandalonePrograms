#include <mcp_can.h>
#include <SPI.h>
#define EXT_INT 8
#define SPI_PIN 7
#define BAUDRATE 115200
void FUNCTION();

enum state
{
  IDLE = 0,
  START,
  RUNNING,
  STOP
};