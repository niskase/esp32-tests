const int IR_RECEIVE_PIN = 4;
const int MAX_PULSES = 40; 
unsigned long spaceDurations[MAX_PULSES];

void setup() {
  Serial.begin(115200);
  pinMode(IR_RECEIVE_PIN, INPUT_PULLUP);
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

      // and so on...
      
    }
    
    delay(400);
  }
}
