#include "pitches.h"  

int pushButton = 12;
int soundPin = 8;

long constant = 30000;
int notelength = 20;

void setup(){

  Serial.begin(9600);
  pinMode(soundPin, OUTPUT);
  pinMode(pushButton, INPUT);
}

void loop(){

  int buttonState = digitalRead(pushButton);
  if (buttonState == 1) {
    tone(8, random(400,500), notelength);
    delay(random(20,100));
  }
}














