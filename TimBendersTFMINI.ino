#include <phyphoxBle.h>
#include "TFmini.h"

TFmini tfmini;
BleServer server("Arduino");
void setup()
{
    server.start();
    Serial1.begin(TFmini::DEFAULT_BAUDRATE);
    tfmini.attach(Serial1);
    tfmini.setDetectionPattern(TFmini::DetectionPattern::Fixed);
    tfmini.setDistanceMode(TFmini::DistanceMode::Long);
    delay(2000);
}

void loop()
{
    if (tfmini.available())
    {
        float distance, strength, integrationTime, timestamp;
        timestamp = millis()/1000.0;
        distance = tfmini.getDistance();
        strength = tfmini.getStrength();
        integrationTime = tfmini.getIntegrationTime();
        Serial.println(distance);
        delay(30);
        server.write(distance,strength,timestamp, integrationTime);
    }
}
