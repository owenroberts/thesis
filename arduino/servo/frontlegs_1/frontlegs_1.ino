// standging and sitting, pretty smooth

#include <Servo.h>      // include the servo library

Servo right;      
Servo left;
Servo back;

int angle = 90;
int backAngle = 90;
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
      }
      break;
    case 's':
      if (angle > limit) {
        angle -= 10;
      }
      break;
    case 'd':
      if(backAngle < backAngle + limit) {
        backAngle += 10;
        Serial.println(backAngle);
      }
      break;
    case 'f':
      if (backAngle > limit) {
        backAngle -= 10;
        Serial.println(backAngle);
      }
      break;
    }
  }


  left.write(angle);
  right.write(180-angle);
  back.write(backAngle);


  delay(10);


}












