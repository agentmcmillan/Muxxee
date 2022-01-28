#include <EasyNeoPixels.h>
#include <movingAvg.h>
#include <Wire.h>
#include <VL53L0X.h>


// Where are the things are defined constants and variables
int relayPin = 0;                       //defines relay pin number
int pixelPin = 11;                      //location of pixel pin
int onboard = 13;
int dist0;
int fastAvg;
int slowAvg;
int relayCounter;
int relayAvg;
int test1;
int test2;


//things you can change
int relayOnTime = 35;                   // how long should the relay stay on
int holdingTime = 150;                  //how long till next trigger                        
int minDistance = 100;                   //how close can someone be to the sensor
int maxDistance = 750;                  //whats the max someone should be away from the sensor
int senseMax = 450;
int midDist = 500;
int slowAvgCnt = 25;                       //how many averages to compare to  
int fastAvgCnt = 10;                        //how many averages to compare to
int discoDelay = 100;
int waitTime = 100;
int delta = 250;
int delta2 = 400;


VL53L0X distSense;                       // define the distance sensor
movingAvg avgDistance1(fastAvgCnt);        // define the fast moving average object
//movingAvg avgDistance2(slowAvgCnt);        // define the slow moving average

void setup()
{
  setupEasyNeoPixels(pixelPin, 1);      //addresses the pixel on the button board
  pinMode(relayPin, OUTPUT);            //sets the relayout pin
  pinMode(onboard, OUTPUT);
  Serial.begin(9600);                   //serial console speed
  Wire.begin();                         //start i2c
  Serial.println("setup"); 
  //scannning for the sensor
  distSense.setTimeout(500);
  if (!distSense.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  distSense.startContinuous();
  avgDistance1.begin();                            // initialize the moving average
  disco();
}

void loop()
{
   Serial.println("alive"); 
   Serial.println(distSense.readRangeContinuousMillimeters());
   writeEasyNeoPixel(0, 0, 0, 0);
   digitalWrite(12, LOW);
   dist0 = distSense.readRangeContinuousMillimeters();
   fastAvg = avgDistance1.reading(distSense.readRangeContinuousMillimeters());  // calculate the moving average
   if((dist0 < maxDistance) && (fastAvg > minDistance) ) 
   {
   relay2();
   Serial.println("woooooooo"); 
   //printThings();
   }
   avgDistance1.reset();
}



 
