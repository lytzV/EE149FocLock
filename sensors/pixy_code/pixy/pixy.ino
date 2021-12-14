#include <Pixy2.h>
#include <ComponentObject.h>
#include <RangeSensor.h>
#include <SparkFun_VL53L1X.h>
#include <vl53l1x_class.h>
#include <vl53l1_error_codes.h>
#include <Wire.h>
#include "SparkFun_VL53L1X.h" 
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
SFEVL53L1X distanceSensor;

Pixy2 pixy;

void setup()
{
  // PIXY CODE
  Serial.begin(115200);
  pixy.init();
  pixy.changeProg("block");

  // DISTANCE CODE
//  Wire.begin();
//  Serial.begin(115200);
//  if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
//  {
//    while (1) {
//      ;
//    }
//  }
}

void loop()
{
  // PIXY CODE
    uint16_t blocks = pixy.ccc.getBlocks();
    if (blocks) { // change the frequency of printing 
        int16_t mx = pixy.ccc.blocks[0].m_x;
        
        byte * data = (byte *) &mx; // prepare data and ship
        //Serial.write(data, sizeof(mx));
        Serial.println(mx);
    }

   // DISTANCE CODE
//    distanceSensor.startRanging(); //Write configuration bytes to initiate measurement
//    while (!distanceSensor.checkForDataReady())
//    {
//      delay(1);
//    }
//    int distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
//    distanceSensor.clearInterrupt();
//    distanceSensor.stopRanging();
//  
//    float distanceInches = distance * 0.0393701;
//    float distanceFeet = distanceInches / 12.0;
//  
//    byte * data = (byte *) &distanceInches;
//  
//    Serial.write(data, sizeof(distanceInches));
}
