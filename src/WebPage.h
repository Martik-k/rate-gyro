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
        body { font-family: Arial, sans-serif; text-align: center; background-color: #2c3e50; color: white; padding-top: 50px; }
        .card { background: #34495e; padding: 30px; border-radius: 15px; display: inline-block; box-shadow: 0 4px 8px rgba(0,0,0,0.2); }
        .value { font-size: 3rem; font-weight: bold; color: #2ecc71; margin: 20px 0; }
        .unit { font-size: 1.2rem; color: #bdc3c7; }
    </style>
</head>
<body>
    <div class="card">
        <h2>Angular Velocity</h2>
        <div class="value" id="omega_val">0.00</div>
        <div class="unit">rad / s</div>
    </div>

    <script>
        setInterval(function() {
            fetch('/data')
            .then(response => response.json())
            .then(json => {
                document.getElementById('omega_val').innerText = json.omega.toFixed(2);
            });
        }, 100); 
    </script>
</body>
</html>
)rawliteral";

#endif // WEBPAGE_H
