void selectMode(){
  mode = digitalRead(mode1Pin)*2 + digitalRead(mode2Pin);
}


