// a walking cycle?

#include <Servo.h>      // include the servo library

Servo right;      
Servo left;

int angle = 90;
int limit = 45;

boolean start = true;
boolean offset = false;

int d = 250;

void setup() { 
  Serial.begin(9600);       // initialize serial communications

  right.attach(5);
  left.attach(6);
} 

void loop() 
{ 

  if (start) {
    left.write(90);
    right.write(90);
    start = false;
  }

  int inputFront = analogRead(A2);
  Serial.println(inputFront);
  if (inputFront > 800) {
    if (angle < angle + limit) {
      angle += 1;
    } else if (inputFront < 200) {
      angle -= 1;
    }
  }
    


  if ( Serial.available()) {
    char ch = Serial.read();

    switch(ch) {
    case 'w':
      if (angle < angle + limit) {
        angle += 1;
      }
      break;
    case 's':
      if (angle > limit) {
        angle -= 1;
      }
      break;
    }
  }


  left.write(angle);
  right.write(180-angle);


  delay(10);


}











