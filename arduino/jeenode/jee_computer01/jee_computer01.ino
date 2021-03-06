/// @dir pingPong
/// Demo of a sketch which sends and receives packets.
// 2010-05-17 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// with thanks to Peter G for creating a test sketch and pointing out the issue
// see http://jeelabs.org/2010/05/20/a-subtle-rf12-detail/

#include <JeeLib.h>

MilliTimer sendTimer;
char payload[] = "cv";
byte needToSend;

void setup () {
  Serial.begin(57600);
  Serial.println(57600);
  Serial.println("Send and Receive");
  rf12_initialize(1, RF12_868MHZ, 33);
}

void loop () {


  if (rf12_recvDone() && rf12_crc == 0) {
    Serial.println("OK ");
  }

  if (Serial.available()) {
    char ch = Serial.read();
    Serial.println(ch);
    if (ch == 'o' || ch == 'u' || ch == 'i' || ch == 'p') {
      payload[1] = ch;
    } 
    else {
      payload[0] = ch;
    }

    needToSend = 1;
  }

  if (needToSend && rf12_canSend()) {
    needToSend = 0;
    //Serial.println(payload[0]);
    rf12_sendStart(0, payload, sizeof payload);
    payload[0] = 'c';
    payload[1] = 'v';
  }

}











