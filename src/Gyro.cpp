#include "Gyro.h"
#include <Arduino.h>

Gyro::Gyro(Encoder& enc, GyroParams params) 
    : encoder(enc), config(params) {
    lastAngle = 0;
    lastTime = micros();
    angularVelocity = 0;
}

void Gyro::update() {
    float currentAngle = encoder.getAngle();
    unsigned long currentTime = micros();
    
    float dt = (float)(currentTime - lastTime) / 1000000.0f;
    
    float deltaAngle = currentAngle - lastAngle;
    if (deltaAngle > 180.0f) deltaAngle -= 360.0f;
    if (deltaAngle < -180.0f) deltaAngle += 360.0f;
    
    float C = config.getConstantC();
    
    angularVelocity = currentAngle * C; 
    
    lastAngle = currentAngle;
    lastTime = currentTime;
}

void Gyro::setParams(GyroParams newParams) {
    config = newParams;
}

GyroParams Gyro::getParams() const {
    return config;
}

float Gyro::getAngularVelocity() { return angularVelocity; }
float Gyro::getAngle() { return encoder.getAngle(); }