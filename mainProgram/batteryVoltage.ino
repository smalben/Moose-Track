//läser analogingång för batterispänning
int batteryVoltage (){
  intVoltage == map(analogRead(batteryPin), 0, 1023, 0,255);
//  voltage == analogRead(batteryPin);
//  map(voltage, 0, 1023, 0, 255);
  return (intVoltage);
}
