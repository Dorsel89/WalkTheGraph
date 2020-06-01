#include <phyphoxBle.h>
#include "TFMini.h"

TFMini tfmini;
BleServer server("Arduino");
void setup()
{
    Serial.begin(115200);
    delay(2000);
    Serial1.begin(115200);
    delay(2000);
    server.start();
    tfmini.begin(&Serial1);    
    delay(1000);
    MODE myMode =  MODE::LONG;

    tfmini.setMeasurementMode(myMode);
    tfmini.setOutputCycle(20); // set time for one measurement cycle in multiple of 10ms (20ms/50Hz in this case)

}

void loop()
{

        float distance, strength, integrationTime, timestamp;
        timestamp = millis()/1000.0;
        distance = tfmini.getDistance();
        strength = tfmini.getRecentSignalStrength();
        integrationTime = 1.;//tfmini.getIntegrationTime();
        Serial.println(distance);
        delay(30);
        server.write(distance,strength,timestamp, integrationTime);
}
