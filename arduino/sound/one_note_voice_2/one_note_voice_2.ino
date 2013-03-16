#include "pitches.h"  


int freqs[] = {
  18, 20, 40, 94, 220, 208, 233, 247, 262,
  277, 294, 311, 330, 331, 332, 333,
  330,331,332,333,334,335,336,337,338,339,
  340,341,342,343,344,34330,331,332,333,334,
  335,336,337,338,339,340,341,342,343,344,345,
  346,347,348,349,350,351,352,353,354,355,356,
  357,358,359,360,361,362,363,364,365,366,367,
  368,369,370,371,372,373,374,375,376,377,378,
  379,380,381,382,383,384,385,386,387,388,389,
  390,391,392,393,394};

#definte pushButton 13
#define soundPin 9

long constant = 30000;
int notelength = 20;
int s = 0;

void setup(){

  Serial.begin(9600);
  pinMode(soundPin, OUTPUT);
  pinMode(pushButton, INPUT);
}

void loop(){

  int buttonState = digitalRead(pushButton);
  Serial.println(buttonState);
  if (buttonState == 1) {
    tone(soundPin, freqs[random(sizeof(freqs))], 40);
    delay(random(20, 80));
  }
}

















