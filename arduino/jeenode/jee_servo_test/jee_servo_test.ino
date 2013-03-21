/// @dir pingPong
/// Demo of a sketch which sends and receives packets.
// 2010-05-17 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// with thanks to Peter G for creating a test sketch and pointing out the issue
// see http://jeelabs.org/2010/05/20/a-subtle-rf12-detail/

#include <JeeLib.h>
#include <SoftwareServo.h>


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

int frontAngle = 90;
int backAngle = 70;
int limit = 45;

int sitInt = 5;
int spineInt = 4;

boolean start = true;


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

  //spine.setMaximumPulse(1600);
}

void loop () {
  if (start) {
    spine.write(90);

    start = false;
  }

  if ( Serial.available()) {
    char ch = Serial.read();
    payload[0] = ch;
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
    case 'k':
      if (spineAngle < spineAngle + spineLimit) {
        spineAngle += spineInt;
        spine.write(spineAngle);
      } 
      break;
      
    //spine left
    case 'l':
      if (spineAngle > spineAngle - spineLimit) {
        spineAngle -= spineInt;
        spine.write(spineAngle);
      }
      break;


    }

    SoftwareServo::refresh();
  }




  if (rf12_recvDone() && rf12_crc == 0) {
    //Serial.println("OK ");
    char ch = rf12_data[0];
    //Serial.println(ch);
    switch(ch) {
    case 'k':
      if (spineAngle < angle + spineLimit) {
        spineAngle += 4;
        //writeServo(spine, spineAngle);
      } 
      break;
    case 'l':
      if (spineAngle > angle - spineLimit) {
        spineAngle -= 4;
        //writeServo(spine, spineAngle);
      }
      break;
    }
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




