/// @dir pingPong
/// Demo of a sketch which sends and receives packets.
// 2010-05-17 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// with thanks to Peter G for creating a test sketch and pointing out the issue
// see http://jeelabs.org/2010/05/20/a-subtle-rf12-detail/

#include <JeeLib.h>

Port leds (1);
MilliTimer sendTimer;
const int payloadCount = 6; // the number of integers in the payload message
int payload[payloadCount];
byte needToSend;

#define buttonPin 4
#define ledPin 5

static void sendLed (byte on) {
  leds.mode(OUTPUT);
  leds.digiWrite(on);
}

static void receiveLed (byte on) {
  leds.mode2(OUTPUT);
  leds.digiWrite2(!on); // inverse, because LED is tied to VCC
}

void setup () {
  Serial.begin(57600);
  Serial.println(57600);
  Serial.println("Send and Receive");
  rf12_initialize(1, RF12_868MHZ, 33);
  pinMode(buttonPin, INPUT);
}

void loop () {    
  int buttonState = digitalRead(buttonPin);
  payload[0] = buttonState;
  for( int i= 1; i < payloadCount; i++)
  {
    payload[i] = 0;   
  }


  if (rf12_recvDone() && rf12_crc == 0) {
    receiveLed(1);
    Serial.print("OK ");
    for (byte i = 0; i < rf12_len; ++i) {
      Serial.print(rf12_data[i]);
      Serial.print(char(rf12_data[i]));

    }
    Serial.println();
    delay(100); // otherwise led blinking isn't visible
    receiveLed(0);
  }

  if (sendTimer.poll(3000))
    needToSend = 1;

  if (needToSend && rf12_canSend()) {
    needToSend = 0;

    sendLed(1);
    rf12_sendStart(0, payload, sizeof payload);
    delay(100); // otherwise led blinking isn't visible
    sendLed(0);
  }
}

