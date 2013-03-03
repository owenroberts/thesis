// a walking cycle?

#include <Servo.h>      // include the servo library

Servo right;      
Servo left;

int angle = 90;
int limit = 45;

boolean start = true;
boolean offset = false;

boolean toggle = false;

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

  if (toggle) {
    angle += 10;
    toggle = false;
  } 
  else if (!toggle) {

    angle -= 10;
    toggle = true;
  }


  left.write(angle);
  right.write(angle);


  delay(100);


}












