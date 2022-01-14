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
|   2   |         MCP2515          |                                          |    1     |
|   3   |     SG90 Servo Motor     |                                          |    2     |
|   4   | AD595 Temperature Sensor |                                          |    1     |

#### <u>Other Components</u>

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



#### STATE DIAGRAM

                  ┌─────────────┐
                  │             │
       ┌─────────►│    IDLE     ├──────────┐
       │          │             │          │
       │          └──────▲──────┘          │
       │                 │                 │
       │                 │                 ▼
┌──┴───┐          ┌───┴────┐  ┌───────┐
│                 │          │ COMPLETE  │  │    START     │
│    STOP   │          └───▲────┘  │                   │
└──────┘                      │               └────┬──┘
       ▲                 │               │
       │            ┌────┴──────┐        │
       │            │           │        │
       └────────────┤  RUNNING  │◄───────┘
                    │           │
                    └───────────┘
#### OUTPUT



