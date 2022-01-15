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

| (Arduino due) Pin Number |    Components attached     |
| :----------------------: | :------------------------: |
|            A2            |       Potentiometer        |
|            8             |     CS pin of MCP2515      |
|            13            |        LED_BUILTIN         |
|            9             | Signal Pin of Servo Motor1 |
|            10            | Signal Pin of Servo Motor2 |

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
*Short the 120 ohm Termination resistor on MCP2515*
*CAN_H of master conected to CAN_H of slave*
*CAN_L of master conected to CAN_L of slave*



#### STATE DIAGRAM
![slave](https://user-images.githubusercontent.com/95620523/149616919-61ade2c2-f88d-4519-8e25-f917c7bc0e81.jpg)



#### OUTPUT

![CKT](https://user-images.githubusercontent.com/95620523/149564391-758f4083-f900-4975-bd86-2d6bbe480985.jpeg)



### Serial Monitor Output

<u>IDLE MODE</u>: In this state Slave sends Idle status to Master and Master receives that Can msg
![mpcr can](https://user-images.githubusercontent.com/95620523/149616936-2eac445f-d779-4464-9d8f-2f8ea974eee9.PNG)



<u> RUNNING MODE</u>: In this State an interrupt connected to master is being trigerred externally in response to which Master sends "Start" command to Slave.
Accordingly Slave Moves to Running State and Starts the Process and keeps Sending Status to master.
![can2](https://user-images.githubusercontent.com/95620523/149616942-986067dd-6118-41ad-95bf-5143b8f613f0.png)



<u>COMPLETE MODE:</u> In this state the process terminates naturally and slave then sends Complete command to master and both transit in Idle state
![can complete](https://user-images.githubusercontent.com/95620523/149616945-bbe03923-65fb-431c-836c-12559c306044.png)



<u>STOP MODE</u>: In this state the process is externally interrupted, and the masters sends Stop Command to Slave.
In response to that slave interrupts the process and sets all parameters to initial and then transits to Idle mode
![can stop](https://user-images.githubusercontent.com/95620523/149616949-58352387-8f86-4ae8-8a65-08f2a9506b52.png)

