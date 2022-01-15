## MPCR WITH CAN BUS (SLAVE)

#### OBJECTIVE

* To control the System Remotely via command given by Master

* To Receive START /STOP Command to slave in Real-time

* To execute and send status of process to master via CAN Communication

* To design a finite state machine with different transition states.

  ​

### Bill of Materials

| Sr No |        Part Name         |                Mfg Number                | Quantity |
| :---: | :----------------------: | :--------------------------------------: | :------: |
|   1   |       Arduino Due        | [A000062](https://www.digikey.in/en/products/detail/arduino/A000062/3712582) |    1     |
|   2   |         MCP2515          | [Module](https://robu.in/product/mcp2515-can-module-tja1050-receiver-spi-51-single-chip-program-routine-arduino/) |    1     |
|   3   |     SG90 Servo Motor     | [Tower Pro](https://robu.in/product/towerpro-sg90-9g-mini-servo-9-gram/) |    2     |
|   4   | AD595 Temperature Sensor | [AD595CQ](https://www.mouser.in/ProductDetail/Analog-Devices/AD595CQ?qs=NmRFExCfTkE1OIHqsmCkzA==&gclid=CjwKCAiA24SPBhB0EiwAjBgkht3R9hyDv5shnj4hVRNFAq1XslBKKGMqvHrZvV37td0DHUcNmQ7H2hoC7mgQAvD_BwE) |    1     |

##### <u>Other Components</u>

* 10K Potentiometer

#### Pin Configuration for Arduino DUE

| (Arduino due) Pin Number |  Components attached   |
| :----------------------: | :--------------------: |
|            A2            |     Potentiometer      |
|            8             |   CS pin of MCP2515    |
|            13            |      LED_BUILTIN       |
|            9             | Servo Motor Signal Pin |
|            10            | Servo Motor Signal Pin |

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

![mpcr slave](https://user-images.githubusercontent.com/95620523/149564383-c9ad05ac-30ad-4b43-978b-128c85e6290d.jpeg)

##### Note: 
 Short the 120 ohm Termination resistor on MCP2515



#### STATE DIAGRAM



#### OUTPUT

![CKT](https://user-images.githubusercontent.com/95620523/149564391-758f4083-f900-4975-bd86-2d6bbe480985.jpeg)



### Serial Monitor Output

