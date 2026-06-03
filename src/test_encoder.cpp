// BUILD: 
//   pio run -e test_encoder
// UPLOAD: 
//   pio run -e test_encoder -t upload
// UPLOAD + Serial Monitor: 
//   pio run -e test_encoder -t upload -t monitor

#include <Arduino.h>
#include "encoder.h"

Encoder encoder;

void setup() {
    Serial.begin(115200);
    
    encoder.init();
    
    Serial.println("--- Енкодер AS5600 Тест ---");
    delay(1000);
}

void loop() {
    float angle = encoder.getAngle();
    Serial.printf("Angle: %.2f degrees\n", angle);
    
    delay(100);
}