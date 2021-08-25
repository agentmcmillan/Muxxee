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
