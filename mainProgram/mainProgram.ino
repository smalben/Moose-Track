#include <Arduino.h>
#include <avr/io.h>
#include <avr/wdt.h>

//utgångar Pin
int motorPin = 10;
int dirPin = 9;     //HIGH == out, LOW == in
int buzzerPin = 11;
int ledPin = 12;

//ingångar Pin
int startPin = 2;
int stopPin = 3;
int mode1Pin = 4;    //0 == älg, 1 == gris
int mode2Pin = 5;    //0 == klassisk/långsam, 1 == ny typ/snabb
int shotSensPin = 6;
int posGravePin = 14;
int posLeftPin = 15; //ska vara 15
int posRightPin = 16; //ska vara 16
int batteryPin = A7;

//ingångar värden
volatile int startState = 0;
volatile int stopState = 0;
boolean shotSensState = false; //skottsensor
boolean posGraveState = false; //lägesgivare höger ände
boolean posLeftState = false; //lägesgivare vänster startposition
boolean posRightState = false; //lägesgivare höger startposition
int mode = 0; //körläge, älg/gris osv.
int intVoltage;
int ut = 1; //utgående körriktning, höger
int in = 0; //ingående körriktning, vänster

//löphastigheter, justera dessa vid behov
int pigSlow = 150;
int pigFast = 200;
int mooseSpeed = 180;
int initSpeed = 150;
int minSpeed = 70;

// the setup routine runs once when you press reset
void setup()  {
  wdt_disable(); //stäng av watchdog timern, används för att göra reset med stoppknappen

  Serial.begin(9600);
  Serial.print("STARTING...");

  //interrupt
  attachInterrupt(digitalPinToInterrupt(stopPin), stopp, RISING);
  attachInterrupt(digitalPinToInterrupt(startPin), start, RISING);

  //sätt in/utgångar
  pinMode(motorPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(startPin, INPUT);
  pinMode(stopPin, INPUT);
  pinMode(mode1Pin, INPUT);
  pinMode(mode2Pin, INPUT);
  pinMode(shotSensPin, INPUT);
  pinMode(posGravePin, INPUT);
  pinMode(posLeftPin, INPUT);
  pinMode(posRightPin, INPUT);

  //Vänta tills startknapp trycks
  while (startState == 0) {}

  //kör tavlan till startpositionen, 3 pip innan, 3 snabba pip efter
  while (startState == 1) {
//    beep1();
    initTarget();
//    beep2();
    break;
  }

}

void loop()  {
  //läs körsekvens
  selectMode();
  batteryVoltage();

  switch (mode) {
    case 0:
      klassiskTyp();
      break;
    case 1:
      nyTyp();
      break;
    case 2:
      gris(pigSlow);
      break;
    case 3:
      gris(pigFast);
      break;
  }
  while (stopState == 1) {
  }
}

