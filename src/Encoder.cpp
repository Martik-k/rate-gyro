#include "Encoder.h"

Encoder::Encoder() {}

void Encoder::init() {
    Wire.begin(SDA_PIN, SCL_PIN);
    as5600.begin();
    as5600.setDirection(AS5600_CLOCK_WISE); 
}

float Encoder::getAngle() {
    return as5600.readAngle() * (TWO_PI / 4096.0);
}
