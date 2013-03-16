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

#define ledPin 4

SoftwareServo spine;
int angle = 90;
int spineAngle = 90;
int spineLimit = 45;

boolean start = true;

static void blinkLed() {
  Serial.println("blink");
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);  


}

void setup () {
  Serial.begin(57600);
  Serial.println(57600);
  Serial.println("Send and Receive");
  rf12_initialize(1, RF12_868MHZ, 33);
  pinMode(ledPin, OUTPUT);
  //pinMode(15, OUTPUT);
  spine.attach(5);
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
    case 'k':
      
      if (spineAngle < angle + spineLimit) {
        Serial.println(spineAngle);
        spineAngle += 4;
        spine.write(spineAngle);
        SoftwareServo::refresh();
      } 
      break;
    case 'l':
      
      if (spineAngle > angle - spineLimit) {
        Serial.println(spineAngle);
        spineAngle -= 4;
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
      if (spineAngle < spineAngle + spineLimit) {
        spineAngle += 4;
        //writeServo(spine, spineAngle);
      } 
      break;
    case 'l':
      if (spineAngle > spineAngle - spineLimit) {
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



