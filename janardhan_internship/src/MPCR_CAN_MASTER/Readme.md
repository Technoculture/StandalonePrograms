## MPCR WITH CAN BUS (MASTER)

#### OBJECTIVE

* To control the System Remotely via command given by Master

* To Send START /STOP Command to slave in Real-time

* To get the current status of Process connected to slave via CAN Communication

* To design a finite state machine with different transition states.

  ​

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
![master](https://user-images.githubusercontent.com/95620523/149563530-83429fd2-04bc-4516-a78c-df131fe3d5eb.jpeg)

##### Note: 
  *Short the 120 ohm Termination resistor on MCP2515*
  
 *10K Pull Down Resistor is Connected between Pin 7 and GND terminal of Due  Board*
 
 *CAN_H of master conected to CAN_H of slave*
 
 *CAN_L of master conected to CAN_L of slave*



#### STATE DIAGRAM
![state diagram](https://user-images.githubusercontent.com/95620523/149616853-e632bb4b-cc76-41a2-8e84-e6084c8e4a03.jpg)




#### OUTPUT
![CKT](https://user-images.githubusercontent.com/95620523/149563855-e3527e79-5cb4-4d55-afae-eec0265c35e7.jpeg)



### Serial Monitor Output

<u>IDLE MODE</u>: In this state Slave sends Idle status to Master and Master receives that Can msg
![mpcr can](https://user-images.githubusercontent.com/95620523/149616880-2d70f512-ad49-4f78-975e-4f63607ad52d.PNG)



<u>RUNNING MODE</u>: In this State an interrupt connected to master is being trigerred externally in response to which Master sends "Start" command to Slave.
Accordingly Slave Moves to Running State and Starts the Process and keeps Sending Status to master.

![can2](https://user-images.githubusercontent.com/95620523/149616884-844125e8-ecc8-477a-8920-684ed4a3421d.png)



<u>COMPLETE MODE</u>: In this state the process terminates naturally and slave then sends Complete command to master and both transit in Idle state
![can complete](https://user-images.githubusercontent.com/95620523/149616892-239f5fa9-97da-4a52-a4da-3f1523a71a03.png)



<u>STOP MODE:</u> In this state the process is externally interrupted, and the masters sends Stop Command to Slave.
In response to that slave interrupts the process and sets all parameters to initial and then transits to Idle mode
![can stop](https://user-images.githubusercontent.com/95620523/149616895-db3a3f31-26f4-4576-87b6-5df38605c1c7.png)


