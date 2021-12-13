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
We used the rechargeable battery to provide 5v power to the Huzzah board, while the motors were powered by the AA batteries which provided 3.5v. 


<p align="center">
  <b>Arduino Libraries</b>
</p>
We found this libraries very useful in our development. They have good documentation that is easy to follow for a biginner. 

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
  <b>Shedule</b>
</p>
We did not stick up to our initial schedule due to parts arriving late
Original schedule:
* Week 1: Connecting all parts and configure all pins
* Week 2: Impliment self driving and bluetooth modes with obstacle avoidance
* Week 3: Assemble all code and begin testing
* Week 4: Prepare for final Presentation and write Up

Actual schedule:
* Week 1: Planning and ordering of parts 
* Week 2: Connecting all parts, configure pins and motor movements
* Week 3: Object detection and avoidance, and autonomous driving mode
* Week 4: Distance and Speed Calculations;  Turning at an Angle and Returning to original course
* Week 5: Website and final write up

<p align="center">
  <b>Methods</b>
</p>

<p align="center">
  <b>Challenges</b>
</p>

We had a difficult time understanding how to use UART mode to read the distance directly from the chip of the utlrasonic sensor. The ducomentation provided by the manufacturer did not provide clear instructions on how to "Serial UART" by connecting the jumper at the right place. After spending many unproductive hours, we decided to switch to "HC-SR04" mode which also took us a while to learn how it works. 

In a different case, our rover could not move in a straight line becasue the weight of the torque was not evenly distributed and we did not have control of the front tyre. The rover would therefore curve in the direction of the heavier side. This affected our ability to smoothly control the car and made our autonomous mode not reach its targets. We corrected the error by removing the front trye and replacing it with two tyres and two DC motors, one on each side of the rover. We also made a few adjustments on the torque to balance its weight.

Our initial full breadboard was too big for the rover and it interfered with the wiring of the entire project. We got rid of the full board and used a small breadboard instead. We attached the ultrasonic sensor at the periphery of the breadboard because this was the only space we could use. This made our rover to be inaccurate in detecting obstacles directly infront of it. The sensor was also too high to detect objects that were half the height of the rover. We soldered the sensor to wires and glued it at the front centor of the rover and connected the wires to the breadboard. At this position, the sensor could detect small obstacles at half the height of the rover. 

We also experienced some challenges on how to determine distance and direction that we wanted our rover to move. We had to spend some time to undertand the Phyics and Math behind [differential drive kinematics](http://www.cs.columbia.edu/~allen/F17/NOTES/icckinematics.pdf). We then made our own calculations to find the speed of the rover and the time it would take to make a turn given direction in degrees. 

Lastly, we would have liked to use more components on the project such as a camera that would stream videos or images back to the controlling device, and other sensors that could be used to collect more scientific data. We were not able to attach a camera because we could not find a camera that is supported by Arduino. Also tranferring video streams over bluetooth would have been challenging. We could not add other sensors due to timing and budgetary constraints. 


<p align="center">
  <b>Future Work</b>
</p>

We encourage attaching a camera device that could connect to the controlling device over WiFi to collect visuals. Adding more sensors and storage devices would improve the applications of the rover to help meet the initial goal of the project. Storage devices might also enable storage of paths data that can be used by the project to move back to its place of origin if in autonomous mode. If a GPS device is included on the rover it would be possible to map paths and objects when outdoors. For indoor use, it is possible to use mapping algorithms similar to those used in an iRobot for indoor movement. 

Our autonomous mode can also be upgraded using advanced search algorithms that would enable the rover reach its destination given GPS co-ordinates, or a specific location indoors. To increase the application of the rover, there is need to use bigger, stronger and more flexible wheels to navigate tougher terrains. The DC motors should also be upgraded to provide more power and speed to the rover. 

Lastly, a small speaker and LED lights can be added to the rover to enable it send visual and audio messages to the controlling agent. For example, a flashing LED light wooudl be useful if the rover cannot find a path due to objects around it. 




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




