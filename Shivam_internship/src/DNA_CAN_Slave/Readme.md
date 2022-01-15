## DNA EXTRACTOR WITH CAN BUS (SLAVE)

#### OBJECTIVE

* To control the System Remotely via command given by Master

* To receive START /STOP Command from master in Real-time

* To execute and send the current status of Process to master via CAN Communication

* To design a finite state machine with different transition states.

* To Run the system for Six iterations by setting Servos to different angular positions

* To control the Z axis motor using two Limit Switches

  ​

### Bill of Materials

| Sr No |         Part Name          |                Mfg Number                | Quantity |
| :---: | :------------------------: | :--------------------------------------: | :------: |
|   1   |        Arduino Due         | [A000062](https://www.digikey.in/en/products/detail/arduino/A000062/3712582) |    1     |
|   2   | MCP2515 Transceiver Module | [Module](https://robu.in/product/mcp2515-can-module-tja1050-receiver-spi-51-single-chip-program-routine-arduino/) |    1     |
|   3   |   N20 Motor with Encoder   | [ 470827](https://robu.in/product/n20-6v-30rpm-micro-metal-gear-motor-with-encoder/) |    1     |
|   4   |   TB6112fng Motor driver   | [43846](https://robu.in/product/motor-driver-tb6612fng-module-performance-ultra-small-volume-3-pi-matching-performance-ultra-l298n/) |    1     |
|   5   |      SG90 Servo Motor      | [Tower Pro](https://robu.in/product/towerpro-sg90-9g-mini-servo-9-gram/) |    2     |
|   6   |    Optical Limit Switch    | [12078](https://robu.in/product/optical-endstop-light-control-limit-optical-switch/) |    2     |



#### Pin Configuration for Arduino DUE

| (Arduino due) Pin Number |    Components attached     |
| :----------------------: | :------------------------: |
|            2             |    Encoder Pin of Motor    |
|            3             |  PWMA Pin of Motor Driver  |
|            4             |     Lower Limit Switch     |
|            5             |     Upper Limit Switch     |
|            6             |  AIN1 Pin of Motor Driver  |
|            7             |  AIN2 Pin of Motor Driver  |
|            9             | Signal Pin of Servo Motor1 |
|            10            | Signal Pin of Servo Motor2 |
|            13            |        LED_BUILTIN         |

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
![dna slave](https://user-images.githubusercontent.com/95620523/149617048-62d72399-6395-453b-8897-989682543b9f.jpeg)



##### <u>Note:</u> 
*Short the 120 ohm Termination resistor on MCP2515*

*On Pin 4 Optical Limit Switch is connected*

*CAN_H of master conected to CAN_H of slave*

*CAN_L of master conected to CAN_L of slave*


#### STATE DIAGRAM
![slave](https://user-images.githubusercontent.com/95620523/149617053-f95b3988-c41a-49a7-b675-df2603ced7e9.jpg)




#### OUTPUT

![dna ckt](https://user-images.githubusercontent.com/95620523/149617058-f25d35bc-2dea-411b-86e9-3304555bb4db.jpeg)



#### Serial Monitor Output

<u>IDLE MODE</u>: In this state Slave sends Idle status to Master and Master receives that Can msg
![DNA IDle](https://user-images.githubusercontent.com/95620523/149617086-b3876921-fcc1-445c-be07-666994dce450.png)



<u> RUNNING MODE</u>: In this State an interrupt connected to master is being trigerred externally in response to which Master sends "Start" command to Slave.
Accordingly Slave Moves to Running State and Starts the Process and keeps Sending Status to master.
![dna Run](https://user-images.githubusercontent.com/95620523/149617083-2ea7101c-4b09-46e3-98c6-1bcd4ba208bb.png)



<u>COMPLETE MODE:</u> In this state the process terminates naturally and slave then sends Complete command to master and both transit in Idle state
![dna complete](https://user-images.githubusercontent.com/95620523/149617077-33322a12-bbd0-4da0-8a97-1165322403c1.png)



<u>STOP MODE</u>: In this state the process is externally interrupted, and the masters sends Stop Command to Slave.
In response to that slave interrupts the process and sets all parameters to initial and then transits to Idle mode
![dna stop](https://user-images.githubusercontent.com/95620523/149617065-835ebb6d-6a00-4df7-98a4-268d608bd9bf.png)

