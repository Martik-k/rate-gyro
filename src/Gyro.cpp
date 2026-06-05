#include "Gyro.h"
#include <Arduino.h>

Gyro::Gyro(Encoder& enc, GyroParams params) 
    : encoder(enc), config(params) {
    lastTime = micros();
    angularVelocity = 0;
    isInitialized = false;
}

void Gyro::tare() {
    isInitialized = false; 
}

void Gyro::update() {
    float currentRawAngle = encoder.getAngle();
    unsigned long currentTime = micros();
    
    if (!isInitialized) {
        lastRawAngle = currentRawAngle;
        continuousAngle = 0.0f; 
        filteredAngle = 0.0f;
        angularVelocity = 0.0f;
        lastTime = currentTime;
        isInitialized = true;
        return;
    }
    
    float deltaAngle = currentRawAngle - lastRawAngle;
    
    if (deltaAngle > PI) deltaAngle -= TWO_PI;
    if (deltaAngle < -PI) deltaAngle += TWO_PI;
    
    continuousAngle += deltaAngle;
    lastRawAngle = currentRawAngle;
    
    // Коефіцієнт alpha (від 0.0 до 1.0). 
    // Чим менше значення, тим сильніше згладжування, але більша затримка.
    float alpha = 0.1f; 
    filteredAngle = (alpha * continuousAngle) + ((1.0f - alpha) * filteredAngle);
    
    float C = config.getConstantC();
    angularVelocity = filteredAngle * C; 
    
    lastTime = currentTime;
}

void Gyro::setParams(GyroParams newParams) {
    config = newParams;
}

GyroParams Gyro::getParams() const {
    return config;
}

float Gyro::getAngularVelocity() { 
    return angularVelocity; 
}

float Gyro::getAngle() { 
    return filteredAngle; 
}