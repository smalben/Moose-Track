void stopp(){
//  detachInterrupt(digitalPinToInterrupt(startPin));
//  detachInterrupt(digitalPinToInterrupt(stopPin));
  
  analogWrite(motorPin, 0);
  digitalWrite(buzzerPin, LOW);
  stopState = 1;
  startState = 0;
  
  boolean buttonActive = false;
  boolean longPressActive = false;
  long buttonTimer = 0;
  long longPressTime = 2000;
  
  while(digitalRead(startPin) == LOW){
    if (digitalRead(stopPin) == HIGH) {
      if (buttonActive == false) { //starta tiden när knappen trycks
        buttonActive = true;
        buttonTimer = millis();
      }
      if (millis() - buttonTimer > longPressTime) { //kolla om knappen tryckts tillräckligt länge
        wdt_enable(WDTO_30MS); //starta om vid lång stopptryckning
        while(1) {};
      }
    }
    else {
      buttonActive = false;
    }
  }
//  attachInterrupt(digitalPinToInterrupt(stopPin), stopp, RISING);
//  attachInterrupt(digitalPinToInterrupt(startPin), start, RISING);
}

void start(){
  startState = 1;
  stopState = 0;
  
}
