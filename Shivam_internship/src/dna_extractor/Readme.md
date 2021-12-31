## DNA EXTRACTOR TESTING V1.1

### OBJECTIVE

* To develop an algorithm based on the Process flow
* To design a External Interrupt Based Code which will Start and Stop the System
* To set Servo motors at different angles based on the chamber position
* To take Six readings by dipping the swab Sample into 6 chambers for 10 seconds

### Process Flow
![algo](https://user-images.githubusercontent.com/95620523/147822482-3bb8857a-dc14-493b-9ee1-0c39b5481450.jpg)


#### COMPONENTS

* N20 MOTOR (1)
* Optical Limit Switch (2)
* TB6112 Motor Driver (1)
* Push Buttion (1)
* SG 90 Servo Motors (2)

#### Pin Configuration

| (Arduino due) Pin Number | Components attached             |
| :----------------------: | ------------------------------- |
|            2             | External Interrupt              |
|            3             | PWMA Pin of TB6112 Motor driver |
|            4             | Lower Limit Switch              |
|            5             | Upper Limit Switch              |
|            6             | AIN1 of TB6112 Motor driver     |
|            7             | AIN2 of TB6112 Motor driver     |
|            9             | Servo Motor1 Signal Pin         |
|            10            | Servo Motor2 Signal Pin         |

### OUTPUT 
![Capture](https://user-images.githubusercontent.com/95620523/147822490-8325db6c-8536-4852-8a3b-80f9c380cd34.PNG)

