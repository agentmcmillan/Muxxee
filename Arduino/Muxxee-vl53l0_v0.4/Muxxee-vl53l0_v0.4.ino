#include <EasyNeoPixels.h>
#include <movingAvg.h>
#include <Wire.h>
#include <VL53L0X.h>


// Where are the things are defined constants and variables
int relayPin = 0;                       //defines relay pin number
int pixelPin = 11;                      //location of pixel pin
int onboard = 13;
int slowAvg;                       //placeholder  
int fastAvg;                        //placeholder
int relayCounter = 0;                   //relay counter placeholder
int dist1;
int slowNear;
int fastNear;


//things you can change
int relayOnTime = 35;                   // how long should the relay stay on
int holdingTime = 150;                  //how long till next trigger                        
int minDistance = 100;                   //how close can someone be to the sensor
int maxDistance = 550;                  //whats the max someone should be away from the sensor
int absMax = 700;                        //whats the max instantainous before we check the averages greater then 50 and less than 750
int senseMax = 850;
int midDist = 500;
int slowAvgCnt = 50;                       //how many averages to compare to  
int fastAvgCnt = 15;                        //how many averages to compare to
int discoDelay = 100;
int waitTime = 17;


VL53L0X distSense;                       // define the distance sensor
movingAvg avgDistance1(fastAvgCnt);        // define the fast moving average object
movingAvg avgDistance2(slowAvgCnt);        // define the slow moving average

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
  avgDistance2.begin();                            // initialize the moving average

    
  disco();



}

void loop()
{
   writeEasyNeoPixel(0, 0, 0, 0);
   //relayCounter = 0;
   digitalWrite(12, LOW);
   dist1 = distSense.readRangeContinuousMillimeters();
   fastAvg = avgDistance1.reading(distSense.readRangeContinuousMillimeters());             // calculate the moving average
   slowAvg = avgDistance2.reading(distSense.readRangeContinuousMillimeters());
   // holdingTime = 0;
   slowNear = slowAvg - dist1;
   fastNear = fastAvg - dist1;
   fastNear = abs(fastNear);

   
   if((dist1 < absMax) && (fastNear > 25) ) 
   {
      relay();
      Serial.println("woooooooo"); 
      //printThings();
   }

    
    //avgDistance1.reset();
    //avgDistance2.reset();
    
    
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
    while ( d < 400);
    
    digitalWrite(onboard, LOW);
    delay(holdingTime);
    writeEasyNeoPixel(0, 0, 0, 0);
    
 }
 

void printThings()
{
    Serial.print(dist1);                   // print the individual reading
    Serial.print("mm");
    Serial.println();
    Serial.print(fastAvg);                   // print the moving average
    Serial.println("mm fast avg");
    Serial.print(slowAvg);                   // print the moving average
    Serial.print("mm slow avg");
    Serial.println();
    Serial.println();
    Serial.print(fastNear);                   // print the moving average
    Serial.println("mm fast diff");
    Serial.print(slowNear);                   // print the moving average
    Serial.print("mm slow diff");
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
