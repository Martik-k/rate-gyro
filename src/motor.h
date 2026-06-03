#ifndef MOTOR_H
#define MOTOR_H


#include <ESP32Servo.h>
#include "config.h"

class Motor {
private:
    Servo esc;
    int pin;

public:
    Motor(int pwmPin);
    void init();
    void setThrottle(int microSeconds);
};


#endif // MOTOR_H
