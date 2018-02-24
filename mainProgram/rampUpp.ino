void rampUpp(int i) {

  int ramp = 1;   //storlek på rampsteg
  int rampDelay = 3; //fördröjning mellan upprampningen

  while (stopState == 0 && posLeftState == 0 && posRightState == 0 && posGraveState == 0) { //vilkor för att kunna köra
    for (int currentSpeed = minSpeed ; currentSpeed <= i; currentSpeed += ramp) {
      analogWrite(motorPin, currentSpeed);
      delay(rampDelay);
    }
  }
}
