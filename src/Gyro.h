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
private:
    Encoder& encoder;
    GyroParams config;
    float angularVelocity;
    float lastAngle;
    unsigned long lastTime;
};

#endif // GYRO_H
