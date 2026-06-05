#include <Arduino.h>
#include "MPU6500.h"

MPU6500::MPU6500(TwoWire& i2cWire, const GyroRange gyroRange)
    : i2cWire(i2cWire), gyroRange(gyroRange) {}

void MPU6500::begin() {
    // Init Sensor
    i2cWire.beginTransmission(MPU_ADDR);
    i2cWire.write(REG_PWR_MGMT_1);
    i2cWire.write(0x00);
    i2cWire.endTransmission();
    
    delay(10);

    // Configure Gyroscope Range
    i2cWire.beginTransmission(MPU_ADDR);
    i2cWire.write(GYRO_CONFIG);
    i2cWire.write(gyroRange);
    i2cWire.endTransmission();
}

float MPU6500::getSensitivity() {
    switch (gyroRange) {
        case DEG_PER_SEC_250:  return 131.0;
        case DEG_PER_SEC_500:  return 65.5;
        case DEG_PER_SEC_1000: return 32.8;
        case DEG_PER_SEC_2000: return 16.4;
        default:               return 131.0;
    }
}

void MPU6500::readGyroRadians(float resultArray[3]) {
    i2cWire.beginTransmission(MPU_ADDR);
    i2cWire.write(REG_GYRO_XOUT);
    i2cWire.endTransmission(false);
    
    i2cWire.requestFrom(MPU_ADDR, 6, true);
    
    if (i2cWire.available() == 6) {
        int16_t rawX = (i2cWire.read() << 8) | i2cWire.read();
        int16_t rawY = (i2cWire.read() << 8) | i2cWire.read();
        int16_t rawZ = (i2cWire.read() << 8) | i2cWire.read();

        float sensitivity = getSensitivity();

        float degX = rawX / sensitivity;
        float degY = rawY / sensitivity;
        float degZ = rawZ / sensitivity;

        float radX = degX * (PI / 180.0);
        float radY = degY * (PI / 180.0);
        float radZ = degZ * (PI / 180.0);
        
        resultArray[0] = radX;
        resultArray[1] = radY;
        resultArray[2] = radZ;
    } else {
        resultArray[0] = 0.0;
        resultArray[1] = 0.0;
        resultArray[2] = 0.0;
    }
}
