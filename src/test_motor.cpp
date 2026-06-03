// BUILD: 
//   pio run -e test_motor
// UPLOAD: 
//   pio run -e test_motor -t upload
// UPLOAD + Serial Monitor: 
//   pio run -e test_motor -t upload -t monitor

#include <Arduino.h>
#include "motor.h"
#include "encoder.h"
#include "../include/config.h"

Motor motor(MOTOR_PIN);

void setup() {
    Serial.begin(115200);

    motor.init();
    
    Serial.println("Wait 3 seconds before start...");
    delay(3000);
    Serial.println("Start");
    
}

void loop() {
    
    for (int speed = 1000; speed <= 1200; speed += 10) {
        motor.setThrottle(speed);
        Serial.printf("Speed: %d us\n", speed);
        delay(200);
    }
    
    delay(2000);
}