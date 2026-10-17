#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLedPin = 4; 

IRsend irsend(kIrLedPin);

void setup() {
  Serial.begin(115200);
 
  irsend.begin();
  
  Serial.println("IR sender uses GPIO 4");
}

void loop() {
  Serial.println("Sending IR command...");
  
  // Send remote PWR button 
  irsend.sendNEC(0xEE11F609, 32); 

  delay(5000);
}
