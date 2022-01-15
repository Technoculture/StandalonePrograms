## DNA EXTRACTOR WITH CAN BUS (MASTER)

#### OBJECTIVE

* To control the System Remotely via command given by Master

* To Send START /STOP Command to slave in Real-time

* To get the current status of Process connected to slave via CAN Communication

* To design a finite state machine with different transition states.


### Bill of Materials

| Sr No |  Part Name  |                Mfg Number                | Quantity |
| :---: | :---------: | :--------------------------------------: | :------: |
|   1   | Arduino Due | [A000062](https://www.digikey.in/en/products/detail/arduino/A000062/3712582) |    1     |
|   2   |   MCP2515   |                                          |    1     |



#### Pin Configuration for Arduino DUE

| (Arduino due) Pin Number | Components attached |
| :----------------------: | :-----------------: |
|            7             |     Push Button     |
|            8             |  CS pin of MCP2515  |
|            13            |     LED_BUILTIN     |

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



#### STATE DIAGRAM
               ┌──────────────┐
               │              │
       ┌───────►     IDLE     ├──────────┐
       │       │              │          │
       │       └──────────────┘          │
       │                                 │
       │                                 │
       │                         ┌───────▼──────┐
┌──────┴───────┐                 │              │
│              │                 │     START    │
│    STOP      │                 │              │
│              │                 └───────┬──────┘
└───────▲──────┘                         │
        │                                │
        │                                │
        │       ┌──────────────┐         │
        │       │              │         │
        └───────┤    RUNNING   ◄─────────┘
                │              │
                └──────────────┘

#### OUTPUT



