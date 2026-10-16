const int IR_RECEIVE_PIN = 4;
const int MAX_PULSES = 40; 
unsigned long spaceDurations[MAX_PULSES];
const int RELAY_PIN = 3;

void setup() {
  Serial.begin(115200);
  pinMode(IR_RECEIVE_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  Serial.println("IR ready");
}

void loop() {
  if (digitalRead(IR_RECEIVE_PIN) == LOW) {
    int spaceCount = 0;

    // Skip first start pulse
    unsigned long pStart = micros();
    while (digitalRead(IR_RECEIVE_PIN) == LOW) {
      if (micros() - pStart > 15000) break;
    }

    // Read pulse times
    while (spaceCount < MAX_PULSES) {
      // Skip pulse
      unsigned long pStart = micros();
      while (digitalRead(IR_RECEIVE_PIN) == LOW) {
        if (micros() - pStart > 3000) break;
      }
      
      // HIGH break measurement
      unsigned long sStart = micros();
      while (digitalRead(IR_RECEIVE_PIN) == HIGH) {
        if (micros() - sStart > 5000) {
          goto packet_done; // end of message
        }
      }
      unsigned long sDuration = micros() - sStart;
      
      spaceDurations[spaceCount++] = sDuration;
    }
    
    packet_done:
    
    if (spaceCount > 10) {
      uint32_t commandCode = 0;
      for (int i = 0; i < spaceCount; i++) {
        if (spaceDurations[i] > 1000) {
          commandCode |= (1UL << i);
        }
      }

      Serial.print("Code received, hex: 0x");
      Serial.println(commandCode, HEX);

      // Example remote: LG AKB72915269

      if (commandCode == 0xDC23F609) {  // LG remote button 1
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("-> Button 1 pressed!");
      } 
      else if (commandCode == 0xDA25F609) {  // LG remote button 2
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("-> Button 2 pressed!");
      }

      // and so on...
      
    }
    
    delay(400);
  }
}
