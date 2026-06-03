#pragma once
#include <ESP32Servo.h>
#include "../include/config.h"

class Motor {
private:
    Servo esc;
    int pin;

public:
    Motor(int p); // Конструктор приймає номер піна
    void init();
    void setThrottle(int microSeconds);
};
