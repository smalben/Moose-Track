void initTarget(){ //startsekvens som kör tavlan till startpositionen
  const long intervalSilent = 1500;
  const long intervalBeep = 500;
  unsigned long previousMillis = 0;
  int buzzerState = 0;
  
  digitalWrite(dirPin, in);

  while (digitalRead(stopPin) == 0 && digitalRead(posGravePin) == 0){
    if(digitalRead(posGravePin) == HIGH){
      analogWrite(motorPin, 0);    //stoppa tavlan vid startpositionen
      return;
    }
    analogWrite(motorPin, initSpeed);
    
    //piper när tavlan kör till startpositionen
    if(buzzerState == LOW && millis() - previousMillis >= intervalSilent) {
      previousMillis = millis();
      buzzerState = HIGH;
      digitalWrite(buzzerPin, buzzerState);
    }
       
    if(buzzerState == HIGH && millis() - previousMillis >= intervalBeep) {
      previousMillis = millis();   
      buzzerState = LOW;
      digitalWrite(buzzerPin, buzzerState);
    }
  }
  buzzerState = 0;
  digitalWrite(buzzerPin, buzzerState);
  return;
}
