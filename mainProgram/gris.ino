void gris(int hastighet){
  if(startState == 1){
    while(stopState == 0 && posLeftState == 0 && posRightState == 0 && posGraveState == 0){ //vilkor för att kunna köra
      rampUpp(hastighet);
      analogWrite(motorPin, hastighet);
    }
  }
}
