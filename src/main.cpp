#include "Motor.h"
#include "Encoder.h"
#include "Gyro.h"

Encoder encoder;
Motor motor(MOTOR_PIN);
// C = (k * a^2) / (I * omega)
GyroParams params = {0.1f, 0.05f, 15.0f, 0.03f, 314.0f}; 
Gyro gyro(encoder, params);

void setup() {
    encoder.init();
    motor.init();
}

void loop() {
    gyro.update();
    
    float omega = gyro.getAngularVelocity();
    Serial.printf("External Angular Velocity: %.2f rad/s\n", omega);
    
    delay(10);
}