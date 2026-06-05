#include <Arduino.h>
#include "InfraredSensor.h"


InfraredSensor::InfraredSensor(uint8_t pin) : pin(pin) {
        pinMode(pin, INPUT);
}

bool InfraredSensor::isDetected() {
        return digitalRead(pin);
}
