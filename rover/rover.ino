/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
   Has a characteristic of: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E - used for receiving data with "WRITE"
   Has a characteristic of: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E - used to send data with  "NOTIFY"

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   In this example rxValue is the data received (only accessible inside that function).
   And txValue is the data to be sent, in this example just a byte incremented every second.
*/

/*bluetooth service headers */
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;
char t[4];
int SPEED, MAX_SPEED, MIN_SPEED;



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
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

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
  myMotor2->setSpeed(SPEED);
  myMotor1->setSpeed(SPEED / 10);
}
void turnLeft(){
  myMotor2->setSpeed(SPEED / 10);
  myMotor1->setSpeed(SPEED);
}
void turnStraight(){
  myMotor1->setSpeed(SPEED);
  myMotor2->setSpeed(SPEED);
}
void stopMotion(){
  myMotor2->run(RELEASE);
  myMotor1->run(RELEASE);
}

void moveRight(){
  turnRight();
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
}

void moveLeft(){
  turnLeft();
  myMotor2->run(FORWARD);
  myMotor1->run(FORWARD);
}
void moveRightBack(){
  turnLeft();
  myMotor2->run(BACKWARD);
  myMotor1->run(BACKWARD);
}
void moveLeftBack(){
  turnRight();
  myMotor2->run(BACKWARD);
  myMotor1->run(BACKWARD);
}
void moveForward(){
  turnStraight();
  myMotor2->run(FORWARD);
  myMotor1->run(FORWARD);
}

void moveBackward(){
  turnStraight();
  myMotor2->run(BACKWARD);
  myMotor1->run(BACKWARD);
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
void setup() {
  // put your setup code here, to run once:
SPEED = 100;
MAX_SPEED = 200;
MIN_SPEED = 20;

AFMS.begin();
myMotor1->setSpeed(SPEED);
myMotor2->setSpeed(SPEED);

Serial.begin(115200);

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
}

void loop() {

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
    if (t[3] == '1' && t[2] == '1') increaseSpeed();
    if (t[3] == '1' && t[2] == '2') decreaseSpeed();
    while (t[3] == '1' && t[2] == '3') moveLeftBack();
    while (t[3] == '1' && t[2] == '4') moveRightBack();
    while (t[3] == '1' && t[2] == '5') moveForward();
    while (t[3] == '1' && t[2] == '6') moveBackward();
    while (t[3] == '1' && t[2] == '7') moveLeft();
    while (t[3] == '1' && t[2] == '8') moveRight();
    stopMotion();
   
}
