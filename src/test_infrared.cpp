// BUILD: 
//   pio run -e test_infrared
// UPLOAD: 
//   pio run -e test_infrared -t upload
// UPLOAD + Serial Monitor: 
//   pio run -e test_infrared -t upload -t monitor

#include <Arduino.h>
#include <InfraredSensor.h>

InfraredSensor sensor(20);

void setup() {
    Serial.begin(115200);
}

void loop() {}