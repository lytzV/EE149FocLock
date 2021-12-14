#include <Wire.h>
#include <SoftwareSerial.h>
#include <ComponentObject.h>
#include <RangeSensor.h>
#include <SparkFun_VL53L1X.h>
#include <vl53l1x_class.h>
#include <vl53l1_error_codes.h>
#include "SparkFun_VL53L1X.h"

#include <Pixy2.h>

#define SHUTDOWN_PIN 2
#define INTERRUPT_PIN 3
SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

Pixy2 pixy;

void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onRequest(requestEvent); // register event
  Serial.begin(115200);           // start serial for output

  pixy.init();
  pixy.changeProg("block");

//  Wire.begin();
//  if (distanceSensor.init() == false) 
//    Serial.println("Sensor online!");
}

void loop() 
{ 
  delay(100); 
} 

// function that executes whenever data is received from master 
// this function is registered as an event, see setup() 
void requestEvent() 
{
//  // PIXY CODE
  uint16_t blocks = pixy.ccc.getBlocks();
  if (blocks) { // change the frequency of printing 
    int16_t mx = pixy.ccc.blocks[0].m_x;
  
    byte * data = (byte *) &mx; // prepare data and ship
    Wire.write(data, 1);
    //Serial.println(mx);
  }
//  
//  // DISTANCE CODE
//  distanceSensor.startRanging(); //Write configuration bytes to initiate measurement
//   while (!distanceSensor.checkForDataReady())
//   {
//     delay(1);
//   }
//   int distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
//   distanceSensor.clearInterrupt();
//   distanceSensor.stopRanging();
// 
//   float distanceInches = distance * 0.0393701;
//   float distanceFeet = distanceInches / 12.0;
// 
//   byte * data = (byte *) &distanceInches;
// 
//   Wire.write(data, 1);
}
