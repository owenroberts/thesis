/*
* Simple Receiver Code
 * (TX out of Arduino is Digital Pin 1)
 * (RX into Arduino is Digital Pin 0)
 */

int incomingByte = 0;
#define LED_PIN 4

void setup(){
  //2400 baud for the 434 model

  Serial.begin(2400);
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  // read in values, debug to computer
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.println(incomingByte, DEC);

    if (incomingByte = 1) {
      digitalWrite(LED_PIN, 1);

    }

  }

  incomingByte = 0;

}


