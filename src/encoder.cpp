#include "encoder.h"

void Encoder::init() {
    Wire.begin(SDA_PIN, SCL_PIN);
    as5600.begin();
    as5600.setDirection(AS5600_CLOCK_WISE); 
}

float Encoder::getAngle() {
    return as5600.readAngle() * 0.08789; // AS5600 returns 0-4095, multiply by 0.08789 for degrees
}
