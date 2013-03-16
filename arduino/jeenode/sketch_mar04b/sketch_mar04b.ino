/* ReadAnAnalogPin
Reads an analog pin (AIO) on a JeeNode port and prints to the serial monitor.
Useful for quick debugging.
*/

#include <JeeLib.h> 

Port port (1);    // port to read

void setup(){
    Serial.begin(57600);   // std JeeLabs serial rate
}

void loop(){
    int value =  port.anaRead();
    Serial.println (value); 
    delay(100);
}
