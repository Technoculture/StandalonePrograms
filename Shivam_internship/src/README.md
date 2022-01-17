## Reference

***mpcr*** 

This sub project file works around Mechanical PCR where in system consist of implementing PCR process on hardware.



***MPCR_CAN_MASTER***

In this sub project the above PCR process is being implemented using CAN BUS Communication with Main node as Master on which an External push Button is Connected to control the System.

***MPCR_CAN_SLAVE***

In this sub project the above PCR process is being implemented using CAN BUS Communication with other node as Slave on which whole PCR system is connected and controlled accordingly by master.

////////////////////////////////////////////////////////////////////////////

***dna_extractor***

In this sub project DNA EXTRACTOR process is being developed and implemented on hardware consisting of two Guard limit switch for controlling the Z-axis motor.



**dna_extractor_encoder**

In this sub project DNA EXTRACTOR process is being interfaced with an encoder motor  with one optical limit switch attached to the lower end of Z-axis motor.



***DNA_CAN_MASTER***

In this sub project DNA EXTRACTOR process is being developed and implemented on hardware consisting of two Guard limit switch for controlling the Z-axis motor. The system is then integrated with CANBUS Communication. The master controls the whole system remotely by sending Process commands.

***DNA_CAN_SLAVE***

In this sub project DNA EXTRACTOR process is being developed and implemented on hardware consisting of two Guard limit switch for controlling the Z-axis motor. The system is then integrated with CANBUS Communication. The whole system is attached to the slave which starts/stops the process and sends status of the process to master via CANBUS protocol.



***DNA_CAN_ENC_MASTER***

In this sub project DNA EXTRACTOR process is being interfaced with an encoder motor  with one optical limit switch attached to the lower end of Z-axis motor. The system is then integrated with CANBUS Communication. The master controls the whole system remotely by sending Process commands.

***DNA_CAN_ENC_SLAVE***

In this sub project DNA EXTRACTOR process is being interfaced with an encoder motor  with one optical limit switch attached to the lower end of Z-axis motor. The system is then integrated with CANBUS Communication. The whole system is attached to the slave which starts/stops the process and sends status of the process to master via CANBUS protocol.

//////////////////////////////////////////////////////////////////////////////

***Motor Encoder***

In this sub project an N20 motor is being controlled to take specific number of turns based on Encoder values.

***Motor Encoder(0 - 360)***

In this sub project an N20 motor is being controlled to move at specific angle. The desired angle is entered via serial monitor.