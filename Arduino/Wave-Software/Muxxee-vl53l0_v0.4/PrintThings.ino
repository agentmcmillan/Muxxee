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
