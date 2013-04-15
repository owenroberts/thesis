/// @dir pingPong
/// Demo of a sketch which sends and receives packets.
// 2010-05-17 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// with thanks to Peter G for creating a test sketch and pointing out the issue
// see http://jeelabs.org/2010/05/20/a-subtle-rf12-detail/

#include <JeeLib.h>

MilliTimer sendTimer;
char payload[] = "a0";
byte needToSend;
int bot = 0;

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
    if (ch == '1') {
      payload[1] = '0';
    } else if (ch == '2') {
     payload[1] = '1';
    } else {
      payload[0] = ch;
    }

    needToSend = 1;
  }

  if (needToSend && rf12_canSend()) {
    needToSend = 0;
    //Serial.println(payload[0]);
    //Serial.println("BOT" + (String)bot);
    rf12_sendStart(0, payload, sizeof payload);
    payload[0] = 'c';
  }

}











