#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "Motor.h"
#include "Encoder.h"
#include "Gyro.h"
#include "Config.h" 
#include "WebPage.h"
#include "MPU6500.h"

// pio run -e main -t upload
// 192.168.4.1

const char* ssid = "ESP32_Gyro";
const char* password = "password123"; 

WebServer server(80);

Encoder encoder;
Motor motor(MOTOR_PIN);
GyroParams params = {0.1f, 0.05f, 15.0f, 0.03f, 314.0f}; 
Gyro gyro(encoder, params);

TwoWire I2C_IMU = TwoWire(1);
MPU6500 mpu(I2C_IMU, GyroRange::DEG_PER_SEC_250);

void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

void handleData() {
    float omega = gyro.getAngularVelocity();
    
    float imuData[3];
    mpu.readGyroRadians(imuData);

    String json = "{";
    json += "\"omega\":" + String(omega) + ",";
    json += "\"imu_z\":" + String(imuData[2]); 
    json += "}";
    
    server.send(200, "application/json", json);
}

void setup() {
    encoder.init();

    I2C_IMU.begin(IMU_SDA_PIN, IMU_SCL_PIN);
    
    mpu.begin();
    
    delay(2000);
    motor.init(); 
    delay(2000);
    
    motor.setThrottle(1200);

    WiFi.softAP(ssid, password);
    
    server.on("/", handleRoot);
    server.on("/data", handleData);
    
    server.begin();
}

void loop() {
    gyro.update();
    
    server.handleClient();
}
