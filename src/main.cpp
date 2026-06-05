#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "Motor.h"
#include "Encoder.h"
#include "Gyro.h"
#include "Config.h" 
#include "WebPage.h"

// 192.168.4.1

const char* ssid = "ESP32_Gyro";
const char* password = "password123"; 

WebServer server(80);

Encoder encoder;
Motor motor(MOTOR_PIN);
GyroParams params = {0.1f, 0.05f, 15.0f, 0.03f, 314.0f}; 
Gyro gyro(encoder, params);

void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

void handleData() {
    float omega = gyro.getAngularVelocity();
    String json = "{\"omega\":" + String(omega) + "}";
    server.send(200, "application/json", json);
}

void setup() {
    encoder.init();
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