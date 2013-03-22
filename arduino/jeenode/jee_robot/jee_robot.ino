/// @dir pingPong
/// Demo of a sketch which sends and receives packets.
// 2010-05-17 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// with thanks to Peter G for creating a test sketch and pointing out the issue
// see http://jeelabs.org/2010/05/20/a-subtle-rf12-detail/

#include <JeeLib.h>
#include <SoftwareServo.h>

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


MilliTimer sendTimer;
char payload[] = "sv";
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
  //pinMode(15, OUTPUT);
  right.attach(4);
  left.attach(5);
  back.attach(6);
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

    switch(vh) {
    case 'o':
      for (int i = 0; i < 2; i++) {
        tone(soundPin, freqs[random(sizeof(freqs))], 40);
        delay(random(20, 80));
      }
      break;
    case 'i':
      for (int i = 0; i < 10; i++) {
        tone(soundPin, freqs[random(sizeof(freqs))], 40);
        delay(random(20, 80));
      }
      break;
    case 'u':
      for (int i = 0; i < 20; i++) {
        tone(soundPin, freqs[random(sizeof(freqs))], 40);
        delay(random(20, 80));
      }
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
      if (spineAngle < spineAngle + spineLimit) {
        spineAngle += spineInt;
        spine.write(spineAngle);
      } 
      break;

      //spine left
    case 'x':
      if (spineAngle > spineAngle - spineLimit) {
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
      left.write(frontAngle-20);
      delay(100);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(100);
      SoftwareServo::refresh();
      left.write(frontAngle);
      break;



    case 'e':
      SoftwareServo::refresh();
      right.write(frontAngle+20);
      delay(500);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(500);
      SoftwareServo::refresh();
      right.write(frontAngle);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      left.write(frontAngle-20);
      delay(500);
      SoftwareServo::refresh();
      SoftwareServo::refresh();
      delay(500);
      SoftwareServo::refresh();
      left.write(frontAngle);
      break;

    }

    SoftwareServo::refresh();

  }

  if (sendTimer.poll(1000))
    needToSend = 1;

  if (needToSend && rf12_canSend()) {
    needToSend = 0;
    //Serial.println(payload[0]);
    rf12_sendStart(0, payload, sizeof payload);
    payload[0] = 's';
  }

}








