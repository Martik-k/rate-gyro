// BUILD: 
//   pio run -e test_motor
// UPLOAD: 
//   pio run -e test_motor -t upload
// UPLOAD + Serial Monitor: 
//   pio run -e test_motor -t upload -t monitor

#include <Arduino.h>
#include "Motor.h"
#include "Config.h"

Motor motor(MOTOR_PIN);

void setup() {
    Serial.begin(115200);

    delay(2000);

    motor.init();
    
    Serial.println("Wait 3 seconds before start...");
    delay(3000);
    Serial.println("Start");
    
}

void loop() {
    motor.setThrottle(1200); // Be attentive with the value here,
                            // likely the values greater than 1250 can cause too fast spin of the motor
}