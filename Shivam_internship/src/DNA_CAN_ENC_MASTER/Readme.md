## DNA EXTRACTOR WITH CAN BUS (MASTER)

#### OBJECTIVE

* To control the System Remotely via command given by Master

* To Send START /STOP Command to slave in Real-time

* To get the current status of Process connected to slave via CAN Communication

* To design a finite state machine with different transition states.


### Bill of Materials

| Sr No |  Part Name   |                Mfg Number                | Quantity |
| :---: | :----------: | :--------------------------------------: | :------: |
|   1   | Arduino Due  | [A000062](https://www.digikey.in/en/products/detail/arduino/A000062/3712582) |    1     |
|   2   |   MCP2515    | [Module](https://robu.in/product/mcp2515-can-module-tja1050-receiver-spi-51-single-chip-program-routine-arduino/) |    1     |
|   3   | Push Button  | [Tactile Switch](https://robu.in/product/6x6x5-tactile-push-button-switch/) |    1     |
|   4   | 10K Resistor | [10k 0.25W](https://robu.in/product/10k-ohm-0-25w-metal-film-resistor-pack-of-100/) |    1     |

#### Pin Configuration for Arduino DUE

| (Arduino due) Pin Number | Components attached |
| :----------------------: | :-----------------: |
|            7             |     Push Button     |
|            8             |  CS pin of MCP2515  |

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
![master](https://user-images.githubusercontent.com/95620523/149609908-d8ea017d-9b13-4eb4-95a0-5bcd141ea7b1.jpeg)

##### Note: 
 *Short the 120 ohm Termination resistor on MCP2515*
 
 *10K Pull Down Resistor is Connected between Pin 7 and GND terminal of Due  Board*
 
 *CAN_H of master conected to CAN_H of slave*
 
 *CAN_L of master conected to CAN_L of slave*


#### STATE DIAGRAM

![state diagram](https://user-images.githubusercontent.com/95620523/149616972-23cfee4c-75dd-4760-8c42-d8ef76dd8642.jpg)


#### OUTPUT
![dna ckt](https://user-images.githubusercontent.com/95620523/149616997-8b518a8f-b183-4536-b54e-9d3a7fdddd5f.jpeg)



#### Serial Monitor Output

<u>IDLE MODE</u>: In this state Slave sends Idle status to Master and Master receives that Can msg
![DNA IDle](https://user-images.githubusercontent.com/95620523/149617008-cbdca264-6356-47c8-be30-022d41ea90ab.png)



<u>RUNNING MODE</u>: In this State an interrupt connected to master is being trigerred externally in response to which Master sends "Start" command to Slave.
Accordingly Slave Moves to Running State and Starts the Process and keeps Sending Status to master.
![dna Run](https://user-images.githubusercontent.com/95620523/149617015-a7a00f0a-b31e-4f94-822c-2e26d13bf827.png)



<u>COMPLETE MODE:</u> In this state the process terminates naturally and slave then sends Complete command to master and both transit in Idle state
![dna complete](https://user-images.githubusercontent.com/95620523/149617027-fa6e9d9b-d6a7-46c9-9ef8-c0c7cbce186d.png)



<u>STOP MODE</u>: In this state the process is externally interrupted, and the masters sends Stop Command to Slave.
In response to that slave interrupts the process and sets all parameters to initial and then transits to Idle mode
![dna stop](https://user-images.githubusercontent.com/95620523/149617019-324da160-28f5-4db3-b4e1-6a8d2cbb7889.png)

