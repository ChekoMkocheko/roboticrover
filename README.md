# CS435: Embedded Systems Final Report -- Fall 2021 

## Robotic Rover With Object Avoidance 

#### By Assadou Nzigamasabo, Cheko Mkocheko


## Introduction

After nine weeks of learning embedded systems in class, we decided to spend the last four weeks of the semester developing a simple robotic rover that can be controlled by bluetooth or autonomnously by uploading commands to the divice via Bluetooth and can avoid objects on its way. The goal of the project is to design the rover as a tool that can be used by scientists to collect data or to observer phonomena in areas that are not human friendly. We draw our motivation from the Marse Persverance Rover which was launced last March. We felt inspired by the fact that it is possible to put an autonomous vehicle on Mars and leave it to collect data in a way that a human would have done if Mars were accessible. In our project, we have managed to achieve a few functionalities of the Perseverance Rover such as remote control and autonomous control in a limited environment. We believe if we could a longer time than four weeks we could achieved more functionality that better mimicks the rover. 





Helpful Reads:  Differential Drive Kinematics, Esp32 Using HW Timers, ArduinoBLE, Using DC Motors, YouTube


<p align="center">
  <b>Material</b>
</p>

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
|  	|  	| TOTAL | $92.50	|  |





<p align="center">
  <b>Arduino Libraries</b>
</p>

1. BLEDevice
2. BLEServer
3. BLEUtils
4. BLE2902
5. Wire
6. Adafruit_MotorShield
7. utility/Adafruit_MS_PWMServorDriver
8. Math

<p align="center">
  <b>Challenges</b>
</p>

* Ureliable datasheets
* Time
* Limited Resources


<p align="center">
  <b>Future Work</b>
</p>
* Include WiFi-Mode that would allow for introduction of camera to the device to take visuals
* Include data storage to store data for processing and for path tracking
* Include GPS for mapping outdoors
* Include mapping and searching algorithms if the rover is to be used in a confined environment
* Include more sensors for data collection (temperature, humidity, pressure, winds etc)
* Use stronger wheels and stronger DC motors that can withstand tougher terrain
* Add LED lights for communication with user (eg. notifications)




<p align="center">
  <b>References</b>
</p>

1. [Interfacing US-100 Ultrasonic Distance Sensor with Arduino - Electropeak](https://electropeak.com/learn/interfacing-us-100-ultrasonic-distance-sensor-with-arduino/)
2. [ESP32 Series Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
3. [1 Differential Drive Kinematics](http://www.cs.columbia.edu/~allen/F17/NOTES/icckinematics.pdf)
4. [Using ESp32 HW Timers](https://desire.giesecke.tk/index.php/2018/04/22/using-the-hw-timers-of-the-esp32/)
5.[ArduinoBLE](https://www.arduino.cc/en/Reference/ArduinoBLE)
6. [Using DC Motors | Adafruit Motor Shield V2 | Adafruit](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-dc-motors)
7. [ESP32 Technical Tutorials: BLE Notifications](https://www.youtube.com/watch?v=oCMOYS71NIU)




