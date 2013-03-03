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




  left.write(angle);
  right.write(180-angle);


  delay(10);


}











