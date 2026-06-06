#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <Arduino.h>

const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ESP32 Gyro App</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; background-color: #2c3e50; color: white; padding-top: 20px; }
        .container { display: flex; flex-direction: column; align-items: center; gap: 20px; }
        .card { background: #34495e; padding: 20px 30px; border-radius: 15px; width: 80%; max-width: 300px; box-shadow: 0 4px 8px rgba(0,0,0,0.2); }
        h2 { margin-top: 0; font-size: 1.5rem; color: #ecf0f1; border-bottom: 1px solid #7f8c8d; padding-bottom: 10px; }
        .value { font-size: 2.5rem; font-weight: bold; color: #2ecc71; margin: 10px 0; }
        .imu-row { display: flex; justify-content: center; gap: 15px; margin: 10px 0; font-size: 1.5rem; font-weight: bold; }
        .imu-val { color: #f1c40f; }
        .unit { font-size: 1rem; color: #bdc3c7; font-weight: normal; }
    </style>
</head>
<body>
    <div class="container">
        <div class="card">
            <h2>Mechanical Gyro</h2>
            <div class="value" id="omega_val">0.00</div>
            <div class="unit">rad / s</div>
        </div>

        <div class="card">
            <h2>IMU (MPU6500)</h2>
            <div class="imu-row">
                <span>Z:</span>
                <span id="imu_z" class="imu-val">0.00</span>
            </div>
            <div class="unit" style="margin-top: 10px;">rad / s</div>
        </div>
    </div>

    <script>
        setInterval(function() {
            fetch('/data')
            .then(response => response.json())
            .then(json => {
                document.getElementById('omega_val').innerText = json.omega.toFixed(2);
                document.getElementById('imu_z').innerText = json.imu_z.toFixed(2);
            });
        }, 100); 
    </script>
</body>
</html>
)rawliteral";

#endif // WEBPAGE_H
