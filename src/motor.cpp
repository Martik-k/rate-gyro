#include "motor.h"

Motor::Motor(int p) : pin(p) {}

void Motor::init() {
    esc.attach(pin, 1000, 2000);
    esc.writeMicroseconds(1000);
}

void Motor::setThrottle(int microSeconds) {
    if (microSeconds < 1000) microSeconds = 1000;
    if (microSeconds > 2000) microSeconds = 2000;
    
    esc.writeMicroseconds(microSeconds);
}