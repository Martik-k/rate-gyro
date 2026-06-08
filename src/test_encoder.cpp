// BUILD: 
//   pio run -e test_encoder
// UPLOAD: 
//   pio run -e test_encoder -t upload
// UPLOAD + Serial Monitor: 
//   pio run -e test_encoder -t upload -t monitor

#include <Arduino.h>
#include "Encoder.h"

Encoder encoder;

void setup() {
    Serial.begin(UART_SPEED);
    
    encoder.init();
    
    Serial.println("--- Encoder AS5600 Test ---");
    delay(1000);
}

void loop() {
    float angle = encoder.getAngle();
    Serial.printf("Angle: %.2f degrees\n", angle);
    
    delay(100);
}