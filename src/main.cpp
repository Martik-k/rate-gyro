#include <Arduino.h>
#include "motor.h"
#include "encoder.h"
#include "../include/config.h"

Motor motor(MOTOR_PIN);
Encoder encoder;

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

    /*
    float angle = encoder.getAngle();
    Serial.printf("Angle: %.2f degrees\n", angle);
    
    // Приклад логіки: якщо кут > 90 градусів, трохи крутимо мотор
    if (angle > 90.0) {
        motor.setThrottle(1100);
    } else {
        motor.setThrottle(1000);
    }
    
    delay(100);
    */
}