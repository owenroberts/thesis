// standging and sitting, pretty smooth
//perhaps a walking cycle


#include <Servo.h>      // include the servo library
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

#define pushButton 10
#define soundPin 9

long constant = 30000;
int notelength = 20;

Servo right;      
Servo left;
Servo back;
Servo spine;

int angle = 90;
int backAngle = 70;
int limit = 45;
int spineAngle = 90;
int spineLimit = 45;

boolean start = true;
boolean offset = false;

int d = 250;

void setup() { 
  Serial.begin(9600);       // initialize serial communications

  right.attach(8);
  left.attach(6);
  back.attach(7);
  spine.attach(5);
  
  pinMode(soundPin, OUTPUT);
  pinMode(pushButton, INPUT);

} 

void loop() 
{ 

  int buttonState = digitalRead(pushButton);
  if (buttonState == 1) {
    tone(soundPin, freqs[random(sizeof(freqs))], 40);
    delay(random(20, 40));
  }

  if (start) {
    left.write(90);
    right.write(90);
    back.write(90);
    start = false;
  }

  if ( Serial.available()) {
    char ch = Serial.read();

    switch(ch) {

    case 'w':
      if (angle < angle + limit) {
        angle += 10;
        writeServo(left, angle);
        writeServo(right, 180-angle);
      }
      break;

    case 's':
      if (angle > limit) {
        angle -= 10;
        writeServo(left, angle);
        writeServo(right, 180-angle);
      }
      break;

    case 'd':
      if(backAngle < backAngle + limit) {
        backAngle += 10;
        writeServo(back, backAngle);
      }
      break;

    case 'f':
      if (backAngle > limit) {
        backAngle -= 10;
        writeServo(back, backAngle);
      }
      break;

    case 'e':
      Serial.println("walk");
      walk(left);
      delay(40);
      walk(right);
      break;
    case 'r':
      Serial.println("two");
      twoWalk(right, left);
      break;
    case 't':
      Serial.println("2");
      twoWalk2(right, left);
      break;
    case 'k':
      if (spineAngle < spineAngle + spineLimit) {
        spineAngle += 4;
        writeServo(spine, spineAngle);
      } 
      break;
    case 'l':
      if (spineAngle > spineAngle - spineLimit) {
        spineAngle -= 4;
        writeServo(spine, spineAngle);
      }
      break;
    }
  }
}

void writeServo(Servo _s, int _a) {
  Servo s = _s;
  int a = _a;
  s.write(a);
  delay(10);
}

void walk(Servo _s) {
  Servo s = _s  ;
  //delay between servo moves
  int d = 10;
  int r = 4;
  int t = 10;

  for (int i = 1; i < t; i++) {
    angle += r;
    s.write(angle);
    delay(d);
  }
  for (int i = 1; i < t; i++) {
    angle -= r;
    s.write(angle);
    delay(d);
  }
}

void twoWalk(Servo _r, Servo _l) {
  int d = 20;
  int r = 3;
  int t = 8;
  int w = 50;

  Servo right = _r;
  Servo left = _l;

  for (int i = 1; i < t; i++) {
    angle += r;
    right.write(180-angle);
    delay(d);
  }
  angle = angle - r*t;
  delay(w);
  for (int i = 1; i < t; i++) {
    angle += r;
    left.write(angle);
    delay(d);
  }
  angle = angle - r*t;
  delay(w);
  for (int i = 1; i < t; i++) {
    angle -= r;
    right.write(180-angle);
    delay(d);
  }
  angle = angle + r*t;
  delay(w);
  for (int i = 1; i < t; i++) {
    angle -= r;
    left.write(angle);
    delay(d);
  }
  angle = angle + r*t;
  delay(w);

}

void twoWalk2(Servo _r, Servo _l) {
  int d = 20;
  int r = 3;
  int t = 8;
  int w = 50;

  Servo right = _r;
  Servo left = _l;

  for (int i = 1; i < t; i++) {
    angle -= r;
    right.write(180-angle);
    delay(d);
  }
  angle = angle + r*t;
  delay(w);
  for (int i = 1; i < t; i++) {
    angle -= r;
    left.write(angle);
    delay(d);
  }
  angle = angle + r*t;
  delay(w);

  for (int i = 1; i < t; i++) {
    angle += r;
    right.write(180-angle);
    delay(d);
  }
  angle = angle - r*t;
  delay(w);
  for (int i = 1; i < t; i++) {
    angle += r;
    left.write(angle);
    delay(d);
  }
  angle = angle - r*t;
  delay(w);
}














