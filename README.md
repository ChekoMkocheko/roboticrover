# CS435: Embedded Systems Final Report -- Fall 2021 

## Robotic Rover With Object Avoidance 

#### By Assadou Nzigamasabo, Cheko Mkocheko


## Introduction

After nine weeks of learning embedded systems in class, we decided to spend the last four weeks of the semester developing a simple robotic rover that can be controlled by bluetooth or autonomnously by uploading commands to the divice via Bluetooth, and it can avoid objects on its way. The goal of the project is to design the rover as a tool that can be used by scientists to collect data or to observe phonomena in areas that are not human friendly. We draw our motivation from the Mars Persverance Rover which was launced last year (2020). We felt inspired by the fact that it is possible to put an autonomous vehicle on Mars and leave it to collect data in a way that a human would have done if Mars were accessible. In our project, we have managed to achieve a few functionalities of the Perseverance Rover such as remote control and limited autonomous control. Our desire is to add more data collection features over time. In implimenting this project, we found useful information from reading "Differential Drive Kinematics", "Esp32 Using HW Timers", "ArduinoBLE" , "Using DC Motors"  and YouTube tutorials. All links are found at the refence section. 


<p align="center">
  <b>Material</b>
</p>

The table below lists all the materials we used and how you can get them to get started: 

| Part description | Unit cost |	Quantity | Total |	Link to site |
| :-------------:   | :-----:  | :------:  | :---: |     ---------:|
| UltraSonic Distance Sensor | 	$3.95 |	1	 | $3.95 | 	https://www.adafruit.com/product/4007 |
| Wires	| $9.95	| 1	| $9.95	| https://www.adafruit.com/product/4482 |
| Rechargeable Battery |	$9.95	| 1	| $9.95 |	https://www.adafruit.com/product/258 |
| DC Motor Stepper + Featherwings | $19.50 | 1 | $19.50 |	https://www.adafruit.com/product/2927 |
| Min Robot Rover Chasis Kit |	$24.95	| 1 |	$24.95 |	https://www.adafruit.com/product/2939 |
| Full Size Bread Board | $5.95 |	1	| $5.95	| https://www.adafruit.com/product/239 |
| Battery Holder |	$2.95	| 1	| $2.95	| https://www.adafruit.com/product/830 |
| AA Batteries pack of 4 |	$2.95	| 1	| $2.95	| https://www.adafruit.com/product/3349 |
| Wheel for Micro Continuous Rotation FS90R Servo	| $2.50 |	2	| $5.00 |	https://www.adafruit.com/product/2744 |
| DC Motor in Micro Servo Body	| $3.50	| 2	| $7.00	| https://www.adafruit.com/product/2941 |
| Adafruit HUZZAH32 - ESP32 Feather | $19.95 | 1 |$19.95 |https://www.adafruit.com/product/3405 |
|  	|  	| **TOTAL** | **$112.10**	|  |


We chose to buy chasis kit with its associated tyres and DC motors to save ourselves time to build things from scratch and instead concentrate on writing software. Initally we wanted to use a different kind of motors that would have given us more control over rotating them but we would have had to spend more time trying to build a model car and put things together. As for the wheels, we wanted more compact wheels that would have a better grip on a variety of terrain but we were limited by the model. As for the Ultrasonic sensor, we chose it because it is easy to use and gave us the option of reading distance of an obstacle directly from it without any calculations. We were not able to use this mode due to poor instructions. We instead calculated the distance from the speed of sound and the duration that it takes the echo receiver to get the echo back. 
We used the rechargeable battery to provide 5V power to the Huzzah board, while the motors were powered by the AA batteries which provided 3.7V. 


<p align="center">
  <b>Arduino Libraries</b>
</p>
We found these libraries very useful in our development. They have good documentation that is easy to follow for a beginner. 

1. BLEDevice
2. BLEServer
3. BLEUtils
4. BLE2902
5. Wire
6. Adafruit_MotorShield V2
7. utility/Adafruit_MS_PWMServorDriver
8. Math

We learnt about the libraries by googling how Arduino supports each individual component we wanted to use. We started by looking at how Arduino supports bluetooth connections. We used Arduino examples under BLE to learn how it works. We then read more about the BLE libraries online before implimenting the connection in our project. For the motors, we directly searched the Arduino library until we found the Adafruit_MotorShield library which does not have very good examples and it has been discontinued. We googled further and found instructions on how to use [version 2](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-dc-motors) which is still supported. 
For the ultasonic sensor we wanted to use SoftwareSerial, the library that supports UART communication, but it does not support the Adafruit Esp32 Feather board. We could not use it. We used online tutorials to learn how to use the trig pin to send signals to the sensor and read back the duration it would take for the echo pin to recieve the reflected signal.

<p align="center">
  <b>Schedule</b>
</p>
We did not stick up to our initial schedule due to parts arriving late.

Original schedule:
* Week 1: Connect all parts and configure all pins
* Week 2: Impliment self driving and bluetooth modes with obstacle avoidance
* Week 3: Assemble all code and begin testing
* Week 4: Prepare for final Presentation and write up

Actual schedule:
* Week 1: Planning and ordering of parts 
* Week 2: Connecting all parts, configure pins and motor movements
* Week 3: Object detection and avoidance, and autonomous driving mode
* Week 4: Distance and speed calculations, turning at an angle and returning to original course
* Week 5: Website and final write up

<p align="center">
  <b>Methods</b>
</p>

Our project has 4 main components; they include driving the wheels using motors, sensing distance from obstacles by using the ultrasonic sensor, connecting bluetooth to receive commands via UART and autonomous driving which relies on bluetooth connection for commands. 
After getting the material from the vendor, we studied the schematic for evey component to figure out how to connect all the wires according. The Featherwings is soldered onto the Huzzah board, wires from the motors are connected to the pins on the featherbord which is also connected to a battery pack for power and the ultrasonic sensor is connected to the Huzzah board on tx and rx pins. 

![Circuit Diagram ](https://github.com/ChekoMkocheko/roboticrover/blob/main/wiring.png)

#### Driving Motors
We use the 4 DC motors in servo form factor to drive the rover and are controlled using the featherwing. The featherwing can accommodate 4 separate DC motors or 2 separate stepper motors. By using motorshield library, we control each individual motor's speed and direction in a few lines of code. We run each motor at a minimum of 20 rpm and a maximum of 120 rpm as per the manufacturer's specifications. 

#### Turning
To make a turn, we studied differential drive kinematics to move the wheels at different speeds to turn into the direction that want. To make a right turn, we move the wheels of the left side of the rover (outer wheels) at a speed that is 10 times faster than that of right side of the wheels (the inner wheels). To turn to the left side, we do the opposite.

#### Distance from an obstacle
We use the ultrasonic sensor to detect obstacles infront of the rover. The sensor sends 8 bursts of ultrasonic waves from the trigger and receives the echo through the receiver. We calculate the distance of the object from the rover by multiplying the duration it takes the receiver to recieve the first echo with the speed of sound in air divided by 2 to account for the round trip. In this project, we do not do the actual calculation of the distance, we instead calculate the duration it would take an object to be 25cm away from the rover and found it to be 1500 microseconds. We then use this time to detect if there are any objects at within range direnctly infront of the rover. We stop moving if we sense an object in the case of manual control. If in autonomous mode, we try to find the path using trial and error like a worm by turning 45 degrees first to the right, then  -90 if clear path not found, then 135 degrees , then -180 degrees until we find a path that has no obstacle, if we can't find a path we stop and send a distress signal using the red LED. 


#### Bluetooth
After writing the code for connecting the esp32 via bluetooth, we use the BlueFruitConnect app on our phone to connect to the esp32's bluetooth. The app has four directional arrows and 4 digits that can be used to send commands to the board via UART. We have encoded this commands to associate every command recieved with the desired connection. For instance, pressing the forward arrow is equivalent to sending !B517 to the esp via the UART terminal. This is interpreted as moving the the motors forward. Below is all the relevant actions on the app, their corresponding commands and how we interpret them
action              command         interpretation
Hold Up arrow       !B517           move forward
Press down arrow    !B617           move backward
Press left arrow    !B717           turn left
Press right arrow   !B817           turn right
Press 1             !B117           increase speed by 5 rpm
Press 2             !B217           decrease speed by 5 rpm
Press 3             !B317           switch to auto mode
Press 4             !B417           switch to manual mode



<p align="center">
  <b>Manual Mode</b>
  
The rover is always on manual mode by defualut. To use this mode, we first connect to the UART service using BlueFruitConnect app. We move in the direction of choice by pressing and holding the arrows. The rover stops upon releasing the arrows. Speed can be increased or reduced by pressing and holding or pressing and releasing buttons 1 and 2 respectively. When the rover is moving forward and senses an object within 25cm directly infront of it, it stops moving. It would resume movement if the oject is removed and the forward arrow is still held. 
  
</p>

<p align="center">
  <b>Autonomous Mode</b>
</p>

We switch to autonomous mode by pressing 3. We exit from autonomous mode by pressing 4. We can also change the speed of the rover by pressing 1 to increase speed or 2 to reduce speed. The default speed is 110 rpm. Upon pressing 3, we navigate to UART service in the app and send "sXXX" or "SXXX" where XXX is the distance to target in centimeters. At the moment we cannot send more than 3 digits of distance because the app does not allow us to send more than 4 bytes. For instance, to move 5cm we send "s005". The rover moves in straight line towards target distance and stops once it reaches the target. If there is an obstacle along the way, the rover would make a 45 degrees right turn and move 20cm then turn back to the original course towards the target, but it would approach the target from an angle. We use angle proprties of triangles to adjust the angle the rover needs to turn to remain on course after going around an obstacle, we use the cosine rule to find the new adjusted distance to target. If the rover does not find a path after turning 45 degrees we try to go 90 degrees left by 20cm and do the same adjustment as in the 45 degrees turn. If the left turn has no path we turn back right by 135 degrees, and if there is still an object we turn back left by 180 degrees. If we still can't find a path then the rover goes into distress mode by blinking the red LED. The triangle we describe above is formed by the destination, the point where the rover turns, and the point where the rover ends at after turning. 
Click the image below to watch the two demos below. 

[![Demo](https://github.com/ChekoMkocheko/roboticrover/blob/main/RoboticCarImage2.jpg)](https://www.youtube.com/watch?v=kqcvnlc73F0&ab_channel=FabianMkocheko)
[![Demo2](https://github.com/ChekoMkocheko/roboticrover/blob/main/RoboticCarImage2.jpg)](https://youtu.be/xCjoga6XJ-E)

<p align="center">
  <b>Challenges</b>
</p>

We had a difficult time understanding how to use UART mode to read the distance directly from the chip of the utlrasonic sensor. The ducomentation provided by the manufacturer did not provide clear instructions on how to "Serial UART" by connecting the jumper at the right place. After spending many unproductive hours, we decided to switch to "HC-SR04" mode which also took us a while to learn how it works. 

In a different case, our rover could not move in a straight line becasue the weight of the torque was not evenly distributed and we did not have control of the front tyre. The rover would therefore curve in the direction of the heavier side. This affected our ability to smoothly control the car and made our autonomous mode not reach its targets. We corrected the error by removing the front trye and replacing it with two tyres and two DC motors, one on each side of the rover. We also made a few adjustments on the torque to balance its weight.

Our initial full breadboard was too big for the rover and it interfered with the wiring of the entire project. We got rid of the full board and used a small breadboard instead. We attached the ultrasonic sensor at the periphery of the breadboard because this was the only space we could use. This made our rover to be inaccurate in detecting obstacles directly infront of it. The sensor was also too high to detect objects that were half the height of the rover. We soldered the sensor to wires and glued it at the front center of the rover and connected the wires to the breadboard. At this position, the sensor could detect small obstacles at half the height of the rover. 

We also experienced some challenges on how to determine distance and direction that we wanted our rover to move. We had to spend some time to undertand the Phyics and Math behind [differential drive kinematics](http://www.cs.columbia.edu/~allen/F17/NOTES/icckinematics.pdf). We then made our own calculations to find the speed of the rover and the time it would take to make a turn given direction in degrees. 

Lastly, we would have liked to use more components on the project such as a camera that would stream videos or images back to the controlling device, and other sensors that could be used to collect more scientific data. We were not able to attach a camera because we could not find a camera that is supported by Arduino. Also tranferring video streams over bluetooth would have been challenging. We could not add other sensors due to timing and budgetary constraints. 


<p align="center">
  <b>Accessibility</b>
</p>
The total cost of material used in this project could be a huge barrier to its implimentation by other people. To reduce the cost, one might choose to use fewer materials for instance using two DC motors instead of four and using custom-made wheels and chasis from a box or hard-board. 

To control the rover using bluetooth one needs access to a smartphone that can download the BlueFruitConnect app. This might be a huge challenge for those who cannot afford to have a smartphone. However, one could go around this problem by using a Wi-Fi module and impliment a webservice that they can use to send instructions to the rover. 

The rover is not easy to operate easily in autonomous mode becasue there are a lot of interfaces on the app that one needs to navigate before sending commands.  It needs a bit of tech savvines to operate. These issues can be addressed in the future by creating an app that is dedicated to sercive the rover only so that anyone can operate it. 

In its current form, the rover cannot be operated by the visually impared. This can be addressed at the application level to allow the app to accept voice commands. It is not possible to accomodate this at the moment. 

<p align="center">
  <b>Ethical Concerns</b>
</p>
The major ethical concerns of project are its environmental impact and how the rover could be used for malice. The double AA batteries have to be thrown away once their charge is drained contributing to e-waste. This externality, however, can be reduced by using rechargeable batteries. If the circuit boards are not recycled they can also contribute to e-waste that has raised environmental justice concenrs in recent years. We strongly encourage whoever imitates the project to have a recycling or reusing plan after this project. 

The rover's ability to be controlled remotely makes it vulnerable to malicious use such as terrorism and spying which could lead to serious harm on people. We hope the rover will not be put into bad use. We denounce evil use of the rover. 

Lastly, using bluetooth to connect to the rover leaves one's phone vulnerable to hacking ([Bluesnarfing and Bluebugging](https://www.bullguard.com/blog/2018/01/can-a-device-be-hacked-via-bluetooth) ) which could result in serious problems. We urge users to only connect to devices they trust and to always turn off their bluetooth when not in use. 


<p align="center">
  <b>Future Work</b>
</p>

We encourage attaching a camera device that could connect to the controlling device over WiFi to collect visuals. Adding more sensors and storage devices would improve the applications of the rover to help meet the initial goal of the project. Storage devices might also enable storage of paths data that can be used by the project to move back to its place of origin if in autonomous mode. If a GPS device is included on the rover it would be possible to map paths and objects when outdoors. For indoor use, it is possible to use mapping algorithms similar to those used in an iRobot for indoor movement. 

Our autonomous mode can also be upgraded using advanced search algorithms that would enable the rover reach its destination given GPS co-ordinates, or a specific location indoors. To increase the application of the rover, there is need to use bigger, stronger and more flexible wheels to navigate tougher terrains. The DC motors should also be upgraded to provide more power and speed to the rover. 

Lastly, a small speaker can be added to the rover to enable it send audio messages to the controlling agent. For example, a siren or beeping sound could be used in conjuction with the red LIGHT for distress. 




<p align="center">
  <b>References</b>
</p>

1. [Interfacing US-100 Ultrasonic Distance Sensor with Arduino - Electropeak](https://electropeak.com/learn/interfacing-us-100-ultrasonic-distance-sensor-with-arduino/)
2. [ESP32 Series Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
3. [1 Differential Drive Kinematics](http://www.cs.columbia.edu/~allen/F17/NOTES/icckinematics.pdf)
4. [Using ESp32 HW Timers](https://desire.giesecke.tk/index.php/2018/04/22/using-the-hw-timers-of-the-esp32/)
5. [ArduinoBLE](https://www.arduino.cc/en/Reference/ArduinoBLE)
6. [Using DC Motors | Adafruit Motor Shield V2 | Adafruit](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-dc-motors)
7. [ESP32 Technical Tutorials: BLE Notifications](https://www.youtube.com/watch?v=oCMOYS71NIU)




