#pragma once
#include <AS5600.h>
#include <Wire.h>
#include "../include/config.h"

class Encoder {
private:
    AS5600 as5600;

public:
    void init();
    float getAngle(); // 0-360
};
