#ifndef GYRO_PARAMS_H
#define GYRO_PARAMS_H

#pragma once
#include <Arduino.h>

struct GyroParams {
    float mass;       // m (кг)
    float radius;     // r (м)
    float k;          // жорсткість (Н/м)
    float a;          // плече (м)
    float omega;      // швидкість ротора (рад/с)

    float getMomentOfInertia() const { 
        return 0.5f * mass * radius * radius; 
    }
    
    float getConstantC() const {
        return (-k * pow(a, 2)) / (getMomentOfInertia() * omega);
    }
};

#endif // GYRO_PARAMS_H
