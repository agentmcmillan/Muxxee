void relay()
{  
  int d =0;
  relayCounter++;
  d = distSense.readRangeContinuousMillimeters();
  Serial.println("relay triggered");
  Serial.println(d);
  digitalWrite(onboard, HIGH);
  digitalWrite(relayPin, HIGH);
  writeEasyNeoPixel(0, 0, 100, 0);
  delay(relayOnTime);
  digitalWrite(relayPin, LOW);
  delay(waitTime); 
  relayAvg = avgDistance1.reading(distSense.readRangeContinuousMillimeters());
  
  Serial.println("relay avg");
  Serial.println(relayAvg);
   
  digitalWrite(onboard, LOW);
  delay(holdingTime);
   
 }
