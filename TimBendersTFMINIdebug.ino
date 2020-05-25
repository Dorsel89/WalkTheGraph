#include <phyphoxBle.h>
#include "TFmini.h"

TFmini tfmini;
BleServer server("Arduino");
void setup()
{
    Serial.begin(115200);
    delay(2000);
    server.start();
    Serial1.begin(TFmini::DEFAULT_BAUDRATE);
    tfmini.attach(Serial1);
    delay(1000);

    const TFmini::DetectionPattern myPattern = TFmini::DetectionPattern::Fixed;
    tfmini.setDetectionPattern(myPattern);
    delay(1000);
    while (Serial1.available()) {
      Serial.write(Serial1.read());
    }

    const TFmini::DistanceMode myMode = TFmini::DistanceMode::Long;

    tfmini.setDistanceMode(myMode);
    
    while (Serial1.available()) {
      Serial.write(Serial1.read());
    }
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
