#include <Wire.h>
//#include <SoftwareSerial.h>
//#include <ComponentObject.h>
//#include <RangeSensor.h>
//#include <SparkFun_VL53L1X.h>
//#include <vl53l1x_class.h>
//#include <vl53l1_error_codes.h>
//#include "SparkFun_VL53L1X.h"
//
//#include <Pixy2.h>
//
//#define SHUTDOWN_PIN 2
//#define INTERRUPT_PIN 3
//#SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

//Pixy2 pixy;
byte x = 0;

void setup()
{
  Wire.begin();                // join i2c bus with address #4
}

void loop() 
{ 
  Wire.beginTransmission(102); // transmit to device #4
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
} 
