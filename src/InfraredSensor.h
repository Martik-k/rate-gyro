#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include <cinttypes>


class InfraredSensor {
private:
    const uint8_t pin;

public:
    InfraredSensor(uint8_t pin);

    bool isDetected();
};


#endif // INFRADER_SENSOR_H