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
int relayCounter;


//things you can change
int relayOnTime = 35;                   // how long should the relay stay on
int holdingTime = 150;                  //how long till next trigger                        
int minDistance = 100;                   //how close can someone be to the sensor
int maxDistance = 850;                  //whats the max someone should be away from the sensor
int absMax = 600;                        //whats the max instantainous before we check the averages greater then 50 and less than 750
int senseMax = 850;
int midDist = 500;
int slowAvgCnt = 50;                       //how many averages to compare to  
int fastAvgCnt = 15;                        //how many averages to compare to
int discoDelay = 100;
int waitTime = 75;


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
   writeEasyNeoPixel(0, 0, 0, 0);
   digitalWrite(12, LOW);
   dist0 = distSense.readRangeContinuousMillimeters();
   fastAvg = avgDistance1.reading(distSense.readRangeContinuousMillimeters());             // calculate the moving average
   printThings();
   if((dist0 < absMax) && (fastAvg > minDistance) ) 
   {
      relay();
      Serial.println("woooooooo"); 
      printThings();
   }

    avgDistance1.reset();
}


void relay()
{  
  int d =0;
    relayCounter++;
    digitalWrite(onboard, HIGH);
    digitalWrite(relayPin, HIGH);
    writeEasyNeoPixel(0, 0, 100, 0);
    delay(relayOnTime);
    digitalWrite(relayPin, LOW);
    
    do { 
      delay(waitTime); 
      d = distSense.readRangeContinuousMillimeters();
    } 
    while ( d < maxDistance);
    
    digitalWrite(onboard, LOW);
    delay(holdingTime);
    writeEasyNeoPixel(0, 0, 0, 0);
    
 }
 

void printThings()
{
    Serial.print(dist0);                   // print the moving average
    Serial.print("d0");
    Serial.println();
    Serial.print(fastAvg);                   // print the moving average
    Serial.print(" fastAvg");
    Serial.println();
    Serial.println();
    //avgDistance1.reset();
    //avgDistance2.reset();
}

void disco()
{
  writeEasyNeoPixel(0, 200, 0, 0);
  delay(discoDelay);
  writeEasyNeoPixel(0, 0, 200, 0);
  delay(discoDelay);
  writeEasyNeoPixel(0, 0, 0, 200);
  delay(discoDelay);
  writeEasyNeoPixel(0, 200, 100, 0);
  delay(discoDelay);  
  writeEasyNeoPixel(0, 0, 200, 100);
  delay(discoDelay);
  writeEasyNeoPixel(0, 100, 0, 200);
  delay(discoDelay);
  writeEasyNeoPixel(0, 0, 0, 0);
  delay(discoDelay);
  writeEasyNeoPixel(0, 200, 0, 100);
  delay(discoDelay);  
  writeEasyNeoPixel(0, 100, 200, 0);
  delay(discoDelay);
  writeEasyNeoPixel(0, 0, 100, 200);
  delay(discoDelay);
writeEasyNeoPixel(0, 200, 200, 200);
  delay(discoDelay);  
  }
