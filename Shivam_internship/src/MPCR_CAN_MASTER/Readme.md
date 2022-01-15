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
 Short the 120 ohm Termination resistor on MCP2515
 10K Pull Down Resistor is Connected between Pin 7 and GND terminal of Due Board



#### STATE DIAGRAM




#### OUTPUT
![CKT](https://user-images.githubusercontent.com/95620523/149563855-e3527e79-5cb4-4d55-afae-eec0265c35e7.jpeg)



### Serial Monitor Output

