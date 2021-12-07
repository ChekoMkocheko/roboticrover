/*bluetooth service headers */
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <math.h>


BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
bool isAuto = false;
uint8_t txValue = 0;
char t[4];
int SPEED, MAX_SPEED, MIN_SPEED;
void automode(void);


// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

/*bluetooth service macros*/
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"


/*motor control headers */
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *rightBack = AFMS.getMotor(1);
Adafruit_DCMotor *leftBack = AFMS.getMotor(2);
Adafruit_DCMotor *rightFront = AFMS.getMotor(3);
Adafruit_DCMotor *leftFront = AFMS.getMotor(4);



const int trigPin = 16;
const int echoPin = 17;

#define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
#define FULL_ROTATION 800000
#define DIST_OFFSET 70000
void dist(void);
unsigned int duration;
volatile int echoduration = 0;
float distanceCm;
float distanceInch;
float destDist;
float destAngle;

/*handles connecting and disconnecting to the bluetooth server */
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};



void turnRight(){
  leftBack->setSpeed(SPEED);
  leftFront->setSpeed(SPEED);
  rightBack->setSpeed(SPEED / 10);
  rightFront->setSpeed(SPEED / 10);
}
void turnLeft(){
  rightBack->setSpeed(SPEED);
  rightFront->setSpeed(SPEED);
  leftBack->setSpeed(SPEED / 10);
  leftFront->setSpeed(SPEED / 10);
}
void turnStraight(){
  leftBack->setSpeed(SPEED);
  leftFront->setSpeed(SPEED);
  rightBack->setSpeed(SPEED);
  rightFront->setSpeed(SPEED);
}
void stopMotion(){
  leftBack->run(RELEASE);
  leftFront->run(RELEASE);
  rightBack->run(RELEASE);
  rightFront->run(RELEASE);
}

void moveRight(){
  turnRight();
  leftBack->run(FORWARD);
  leftFront->run(FORWARD);
  rightBack->run(FORWARD);
  rightFront->run(FORWARD);
}

void moveLeft(){
  turnLeft();
  leftBack->run(FORWARD);
  leftFront->run(FORWARD);
  rightBack->run(FORWARD);
  rightFront->run(FORWARD);
}

void moveForward(){
  dist();
  turnStraight();
  if(echoduration > 1500 || echoduration == 0){
    leftBack->run(FORWARD);
    leftFront->run(FORWARD);
    rightBack->run(FORWARD);
    rightFront->run(FORWARD);
  }

}

void moveBackward(){
  turnStraight();
  leftBack->run(FORWARD);
  leftFront->run(FORWARD);
  rightBack->run(BACKWARD);
  rightFront->run(BACKWARD);
}
void increaseSpeed(){
  if (SPEED + 5 < MAX_SPEED){
    SPEED = SPEED + 5;
  }
  Serial.println(SPEED);
}
void decreaseSpeed(){
  if (SPEED > MIN_SPEED){
    SPEED = SPEED - 5;
  }
  Serial.println(SPEED);
}
 

/*gets data from bluetooth client*/
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++){
          //Serial.print(rxValue[i]);
          t[i]=rxValue[i];
   
        }
        Serial.print(t);
        Serial.println();
        Serial.println("*********");
      }
    }
};
void dist() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  echoduration = duration;
  Serial.println(duration);
}
void setup() {
Serial.begin(115200);
//Serial1.begin(9600);

//DC motors setup
SPEED = 100;
MAX_SPEED = 200;
MIN_SPEED = 20;

AFMS.begin();
leftBack->setSpeed(SPEED);
rightBack->setSpeed(SPEED);
leftFront->setSpeed(SPEED);
rightFront->setSpeed(SPEED);

//bluetooth (bluefruit) setup

  // Create the BLE Device
  BLEDevice::init("UART Service");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );
                     
  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                       CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");

  //ultrasonic sensor setup
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}
//void avoidObject(){
//  
//}
 /**
  * driveMotor is responsible for interpreting the inputs from bluetooth. We programmed different behaviors
  * to the buttons in order to respond move the robot and be able to switch from auto to manual, increase and decrease speed,
  * turn right and left, and move forward and backwards.
  */
// void adjust(int timevar, int angle){
//  int dist = timevar * SPEED;
//  
// }
 void turnAngle(int angle){
  if (angle > 0){
    moveRight();
    delay(FULL_ROTATION * angle/ (SPEED * 360) );
  }
  if (angle < 0){
    moveLeft();
    delay(FULL_ROTATION * angle * -1 / (SPEED * 360));
  }
 
 }
 void moveDist(int travelDist){
  moveForward();
  delay(70000 * travelDist / (11 * SPEED));
  stopMotion();
 }
 void automode(){
 if(echoduration > 1500 || echoduration == 0) {
  //moveForward();
  dist();
 }
 else{
    stopMotion();
    turnAngle(90);
    moveDist(20);
    //stopMotion();
    //dist();
  }
 }
void driveMotor(){
  if (isAuto){
    if (t[3] == '1' && t[2] == '4') isAuto = false;
    automode();
  }
  else{
    if (t[3] == '1' && t[2] == '1') increaseSpeed();
    if (t[3] == '1' && t[2] == '2') decreaseSpeed();
    if (t[3] == '1' && t[2] == '3') isAuto = true;
    while (t[3] == '1' && t[2] == '5' && (echoduration > 1500 || echoduration == 0)) moveForward();
    while (t[3] == '1' && t[2] == '6') moveBackward();
    while (t[3] == '1' && t[2] == '7') moveLeft();
    while (t[3] == '1' && t[2] == '8') moveRight();
    stopMotion();
    if(!(echoduration > 1500 || echoduration == 0)){
      dist();
  }
  }
 
}

/**
 * This function handles all of the communications between the bluetooth app (Bluefruit connect) and the rover.
 * It is not only responsible for advertising our bluetooth server, for recognizing and connecting to a bluetooth device,
 * and for handling disconnection (re-advertise).
 */
void communicateWithApp(){
  if (deviceConnected) {
        pTxCharacteristic->setValue(&txValue, 1);
        pTxCharacteristic->notify();
        txValue++;
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent
  }

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}
void loop() {
 
    communicateWithApp(); //handles all the communications with bluetooth
    driveMotor();

}
