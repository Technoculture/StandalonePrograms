## DNA EXTRACTOR WITH CAN BUS (SLAVE)

#### OBJECTIVE

* To control the System Remotely via command given by Master

* To receive START /STOP Command from master in Real-time

* To execute and send the current status of Process to master via CAN Communication

* To design a finite state machine with different transition states.

* To Run the system for Six iterations by setting Servos to different angular positions

  ​

### Bill of Materials

| Sr No |         Part Name          |                Mfg Number                | Quantity |
| :---: | :------------------------: | :--------------------------------------: | :------: |
|   1   |        Arduino Due         | [A000062](https://www.digikey.in/en/products/detail/arduino/A000062/3712582) |    1     |
|   2   | MCP2515 Transceiver Module | [Module](https://robu.in/product/mcp2515-can-module-tja1050-receiver-spi-51-single-chip-program-routine-arduino/) |    1     |
|   3   |   N20 Motor with Encoder   | [ 470827](https://robu.in/product/n20-6v-30rpm-micro-metal-gear-motor-with-encoder/) |    1     |
|   4   |   TB6112fng Motor driver   | [43846](https://robu.in/product/motor-driver-tb6612fng-module-performance-ultra-small-volume-3-pi-matching-performance-ultra-l298n/) |    1     |
|   5   |      SG90 Servo Motor      | [Tower Pro](https://robu.in/product/towerpro-sg90-9g-mini-servo-9-gram/) |    2     |
|   6   |    Optical Limit Switch    | [12078](https://robu.in/product/optical-endstop-light-control-limit-optical-switch/) |    1     |



#### Pin Configuration for Arduino DUE

| (Arduino due) Pin Number |    Components attached    |
| :----------------------: | :-----------------------: |
|            2             |   Encoder Pin of Motor    |
|            3             | PWMA Pin of Motor Driver  |
|            4             |       Limit Switch        |
|            6             | AIN1 Pin of Motor Driver  |
|            7             | AIN2 Pin of Motor Driver  |
|            9             | Signal Pin of Servo Motor |
|            10            | Signal Pin of Servo Motor |
|            13            |        LED_BUILTIN        |

| (Arduino due) SPI PIN | MCP2515 |
| :-------------------: | :-----: |
|          VCC          |   VCC   |
|          GND          |   GND   |
|           8           |   CS    |
|         MISO          |   SO    |
|         MOSI          |   SI    |
|          SCK          |   SCK   |
|         ----          |   INT   |

#### CIRCUIT DIAGRAM



##### Note: 
 Short the 120 ohm Termination resistor on MCP2515

On Pin 4 Optical Limit Switch is connected



#### STATE DIAGRAM




#### OUTPUT



#### Serial Monitor Output