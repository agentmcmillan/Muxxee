void relay2()
{  
  test1 = slowAvg - fastAvg;
  test2 = test1 - dist0;
  abs(test1);
  abs(test2);
  //writeEasyNeoPixel(0, 100, 100, 0);
  while( test1 < delta);

  
Serial.println();
Serial.println();  
Serial.println(test1);
Serial.println(test2);

   
 }
