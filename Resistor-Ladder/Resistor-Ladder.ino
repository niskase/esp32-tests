#include <Arduino.h>

const int analogPin = 4;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  int rawValue = analogRead(analogPin);
  float voltage = (rawValue / 4095.0) * 3.3;
  
  if (voltage < 1.5) {
    // No button prsessed
  } 
  else if (voltage >= 1.49 && voltage < 1.54) {
      Serial.println(String("-> Top button pressed! ") + voltage + String("V"));
      delay(500);
      
    } 
  else if (voltage >= 1.86 && voltage < 1.90) {
      Serial.println(String("-> Middle button pressed! ") + voltage + String("V"));
      delay(500);
    } 
  else if (voltage >= 2.17 && voltage < 2.20) {
      Serial.println(String("-> Bottom button pressed! ") + voltage + String("V"));
      delay(500);
    } 
  else {
      Serial.println(String("-> Many buttons pressed! ") + voltage + String("V"));
      delay(500);
    }

  delay(20);
}
