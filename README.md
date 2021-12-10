# roboticrover
A simple robot using Arduino

Goal:   A rover that can be used by scientists for data collection or observations in environments that are not friendly to humans.


Motivation: Mars Perseverance Rover which is collecting data on its own using preloaded instructions


Achievements: The rover can be controlled smoothly using bluetooth; it can be operated in autonomous mode in a limited environment


Shortcomings: No data collection sensors and storage components  have been added yet


Helpful Reads:  Differential Drive Kinematics, Esp32 Using HW Timers, ArduinoBLE, Using DC Motors, YouTube

Material:

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





Arduino Libraries: 

BLEDevice

BLEServer

BLEUtils

BLE2902

Wire

Adafruit_MotorShield

utility/Adafruit_MS_PWMServorDriver

Math

# Challenges #

* Ureliable datasheets
* Time
* Limited Resources

# Future Work: # 
* Include WiFi-Mode that would allow for introduction of camera to the device to take visuals
* Include data storage to store data for processing and for path tracking
* Include GPS for mapping outdoors
* Include mapping and searching algorithms if the rover is to be used in a confined environment
* Include more sensors for data collection (temperature, humidity, pressure, winds etc)
* Use stronger wheels and stronger DC motors that can withstand tougher terrain
* Add LED lights for communication with user (eg. notifications)



References 

Interfacing US-100 Ultrasonic Distance Sensor with Arduino - Electropeak
https://electropeak.com/learn/interfacing-us-100-ultrasonic-distance-sensor-with-arduino/

ESP32 Series Datasheet
https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf

1 Differential Drive Kinematics
http://www.cs.columbia.edu/~allen/F17/NOTES/icckinematics.pdf

Using ESp32 HW Timers
https://desire.giesecke.tk/index.php/2018/04/22/using-the-hw-timers-of-the-esp32/

ArduinoBLE
https://www.arduino.cc/en/Reference/ArduinoBLE

Using DC Motors | Adafruit Motor Shield V2 | Adafruit
https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-dc-motors

ESP32 Technical Tutorials: BLE Notifications
https://www.youtube.com/watch?v=oCMOYS71NIU




