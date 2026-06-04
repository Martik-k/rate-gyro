#ifndef ENCODER_H
#define ENCODER_H

#pragma once
#include <AS5600.h>
#include <Wire.h>
#include "Config.h"

class Encoder {
private:
    AS5600 as5600;

public:
    Encoder();
    void init();
    float getAngle(); // 0-360
};

#endif // ENCODER_H