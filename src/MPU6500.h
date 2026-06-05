#ifndef MPU6500_H
#define MPU6500_H

#include <Wire.h>

enum GyroRange {
    DEG_PER_SEC_250 = 0x00,
    DEG_PER_SEC_500 = 0x08,
    DEG_PER_SEC_1000 = 0x10,
    DEG_PER_SEC_2000 = 0x18
};

class MPU6500 {
private:
    static constexpr int MPU_ADDR = 0x68;       // Default I2C address of the MPU-6500
    static constexpr int REG_PWR_MGMT_1 = 0x6B; // Write 0x00 here to wake the sensor from sleep
    static constexpr int REG_GYRO_XOUT = 0x43;  // Read 6 sequential bytes starting here for X, Y, Z data of the angular acceleration
    static constexpr int GYRO_CONFIG = 0x1B;    // Sets max range limits (0x00=250, 0x08=500, 0x10=1000, 0x18=2000 dps)

    TwoWire& i2cWire;

    const GyroRange gyroRange;

    float getSensitivity();

public:
/**
     * @brief Constructs the sensor object and stores the hardware preferences.
     * * @param i2cWire Reference to the TwoWire I2C bus (e.g., Wire).
     * @param gyroRange The desired full-scale range limit for the gyroscope.
     */
    MPU6500(TwoWire& i2cWire, GyroRange gyroRange=GyroRange::DEG_PER_SEC_250);

    /**
     * @brief Initializes the physical hardware over I2C.
     * Wakes the sensor from sleep mode and writes the selected configuration ranges.
     * @note This must be called inside setup() AFTER calling Wire.begin().
     */
    void begin();

    /**
     * @brief Reads the current rotational speed from the sensor.
     * Fetches raw I2C data, applies the correct sensitivity divisor, and converts to radians.
     * * @param writeArray A 3-element float array where the [X, Y, Z] results will be stored in rad/s.
     */
    void readGyroRadians(float writeArray[3]);
};

#endif // MPU6500_H