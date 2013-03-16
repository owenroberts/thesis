// standging and sitting, pretty smooth
//perhaps a walking cycle

#include <Servo.h>      // include the servo library

Servo right;      
Servo left;
Servo back;

int angle = 90;
int backAngle = 70;
int limit = 45;

boolean start = true;
boolean offset = false;

int d = 250;

void setup() { 
  Serial.begin(9600);       // initialize serial communications

  right.attach(5);
  left.attach(6);
  back.attach(7);

} 

void loop() 
{ 

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














