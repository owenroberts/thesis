/// @dir pingPong
/// Demo of a sketch which sends and receives packets.
// 2010-05-17 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// with thanks to Peter G for creating a test sketch and pointing out the issue
// see http://jeelabs.org/2010/05/20/a-subtle-rf12-detail/

#include <JeeLib.h>
#include <SoftwareServo.h>


MilliTimer sendTimer;
char payload[] = "cv2";
byte needToSend;

SoftwareServo spine;
int angle = 90;
int spineAngle = 90;
int spineLimit = 45;

SoftwareServo right;
SoftwareServo left;
SoftwareServo back;

float refreshMillis = 0;

int frontAngle = 90;
int backAngle = 70;
int limit = 45;

int sitInt = 5;
int spineInt = 4;

boolean start = true;

#define soundPin 15

long constant = 30000;
int notelength = 20;
int s = 0;


void setup () {
  Serial.begin(57600);
  Serial.println(57600);
  Serial.println("Send and Receive");
  rf12_initialize(1, RF12_868MHZ, 33);
  pinMode(16, OUTPUT);
  right.attach(4);
  left.attach(5);
  back.attach(16);
  spine.attach(7);
  pinMode(soundPin, OUTPUT);

  //left.setMinimumPulse(2000);
  //right.setMinimumPulse(2000);
}

void loop () {
  if (start) {
    spine.write(spineAngle);
    left.write(frontAngle);
    right.write(180-frontAngle);
    back.write(backAngle);
    start = false;
    SoftwareServo::refresh();
  }

  if (refreshMillis + 20 < millis()) {
    SoftwareServo::refresh();
    refreshMillis = millis();
  }

  if (rf12_recvDone() && rf12_crc == 0) {
    //Serial.println("OK ");
    char vh = rf12_data[1];
    char ch = rf12_data[0];
    char bot = rf12_data[2];
    
    if (bot == '1') {

    switch(vh) {
      case 'o':
      talk(1);
      break;
    case 'i':
      talk(5);
      break;
    case 'u':
      talk(10);
      break;
    case 'p':
      purr(10);
      break;
    }


    switch(ch) {

      //front legs forward
    case 'w':
      if (frontAngle < angle + limit) {
        frontAngle += sitInt;
        right.write(frontAngle);
        left.write(180-frontAngle);
      }
      break;

      //front legs back
    case 's':
      if (frontAngle > limit) {
        frontAngle -= sitInt;
        right.write(frontAngle);
        left.write(180-frontAngle);
      }
      break;

      //back legs forward
    case 'd':
      if(backAngle < angle + limit) {
        backAngle += sitInt;
        back.write(backAngle);
      }
      break;

      //back legs back
    case 'f':
      if (backAngle > limit) {
        backAngle -= sitInt;
        back.write(backAngle);
      }
      break;

      //spine right
    case 'z':
      if (spineAngle < angle + spineLimit) {
        spineAngle += spineInt;
        spine.write(spineAngle);
      } 
      break;

      //spine left
    case 'x':
      if (spineAngle > angle - spineLimit) {
        spineAngle -= spineInt;
        spine.write(spineAngle);
      }
      break;

      //walk1
    case 'r':
      SoftwareServo::refresh();
      right.write(frontAngle+20);
      delay(100);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(100);
      SoftwareServo::refresh();
      right.write(frontAngle);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      left.write(180-frontAngle-20);
      delay(100);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(100);
      SoftwareServo::refresh();
      left.write(180 - frontAngle);
      break;
      
      case 't':
      SoftwareServo::refresh();
      right.write(frontAngle-20);
      delay(100);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(100);
      SoftwareServo::refresh();
      right.write(frontAngle);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      left.write(180-frontAngle+20);
      delay(100);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(100);
      SoftwareServo::refresh();
      left.write(180-frontAngle);
      break;



    case 'e':
      SoftwareServo::refresh();
      right.write(frontAngle+20);
      delay(200);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(200);
      SoftwareServo::refresh();
      right.write(frontAngle);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      left.write(180-frontAngle-20);
      delay(200);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(200);
      SoftwareServo::refresh();
      left.write(180-frontAngle);
      break;
      
    case 'k':
      SoftwareServo::refresh();
      right.write(frontAngle+40);
      delay(400);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(400);
      SoftwareServo::refresh();
      right.write(frontAngle);
      SoftwareServo::refresh();
      break;
      
    case 'l':
      SoftwareServo::refresh();
      left.write(180-frontAngle-40);
      delay(400);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(400);
      SoftwareServo::refresh();
      left.write(180-frontAngle);
      SoftwareServo::refresh();
      break;
      
    case 'm':
      SoftwareServo::refresh();
      back.write(backAngle-40);
      delay(400);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(400);
      SoftwareServo::refresh();
      back.write(backAngle);
      SoftwareServo::refresh();
      break;
      

    SoftwareServo::refresh();
    }

    
    needToSend = 1;
    }

  }

  if (sendTimer.poll(1000))
    needToSend = 1;

  if (needToSend && rf12_canSend()) {
    needToSend = 0;
    //Serial.println(payload[0]);
    rf12_sendStart(0, payload, sizeof payload);
    payload[0] = 'c';
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








