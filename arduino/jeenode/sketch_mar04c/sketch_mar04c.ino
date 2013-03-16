/*
 * Simple Transmitter Code
 * This code simply counts up to 255 
 * over and over 
 * (TX out of Arduino is Digital Pin 1) 
 */

byte button;
void setup(){
  //2400 baud for the 434 model
  Serial.begin(2400);
  button = 0;
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  //send out to transmitter

  button = digitalRead(2);

  Serial.print(button);


  delay(10);
}


