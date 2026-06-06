// BUILD: 
//   pio run -e test_mpu6500
// UPLOAD: 
//   pio run -e test_mpu6500 -t upload
// UPLOAD + Serial Monitor: 
//   pio run -e test_mpu6500 -t upload -t monitor

#include <Arduino.h>
#include <Wire.h>
#include "Config.h"
#include "MPU6500.h"

MPU6500 gyro(Wire, GyroRange::DEG_PER_SEC_250);

void setup() {
    Serial.begin(UART_SPEED);

    Wire.begin(IMU_SDA_PIN, IMU_SCL_PIN); 
    
    gyro.begin();

    Serial.println("========= Sensor succesfully started =========");
}

void loop() {
    static float resultArray[3];

    gyro.readGyroRadians(resultArray);

    Serial.printf("Angular acceleration X: %f, Y: %f, Z: %f\n", resultArray[0], resultArray[1], resultArray[2]);
}