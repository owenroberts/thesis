#include "pitches.h"  




#define soundPin 15

long constant = 30000;
int notelength = 20;
int s = 0;

void setup(){   

  Serial.begin(9600);
  pinMode(soundPin, OUTPUT);
  // pinMode(pushButton, INPUT);
}

void loop(){

  if (Serial.available()) {
    char ch = Serial.read();
    Serial.println(ch);

    switch(ch) {
    case 'o':
      talk(2);
      break;
    case 'i':
      talk(10);
      break;
    case 'u':
      talk(20);
      break;
    case 'p':
      purr(20);
      break;
    }



  }
}

void talk(int num) {
  for (int j = 0; j < num; j++) {
    for (int i = 0; i < random(3); i++) {
      tone(soundPin, random(100,200), 30);
      delay(random(20, 40));
    }
    delay(random(100, 200));
  }

}

void purr(int num) {
  for (int j = 0; j < num; j++) {
    for (int i = 0; i < random(3); i++) {
      tone(soundPin, random(100,200), 30);
      delay(random(40, 80));
    }
  }
  for (int j = 0; j < num; j++) {
    for (int i = 0; i < random(3); i++) {
      tone(soundPin, random(0,100), 30);
      delay(random(40, 80));
    }
  }
  for (int j = 0; j < num; j++) {
    for (int i = 0; i < random(3); i++) {
      tone(soundPin, random(150,200), 30);
      delay(random(40, 80));
    }
  }

}





















