#ifndef GYRO_H
#define GYRO_H

#pragma once
#include "Encoder.h"
#include "GyroParams.h"

class Gyro {
public:
    Gyro(Encoder& enc, GyroParams params);
    void update();
    void setParams(GyroParams newParams);
    GyroParams getParams() const;
    float getAngularVelocity();
    float getAngle();
    void tare();

private:
    Encoder& encoder;
    GyroParams config;
    
    unsigned long lastTime;
    float angularVelocity;

    bool isInitialized;
    float lastRawAngle;
    float continuousAngle;
    float filteredAngle;
};

#endif // GYRO_H
