#include "IotDevice.h"

EspMQTTClient client(
                      "TP-Link_EB4A",
                      "61151369",
                      "test.mosquitto.org",
                      "den-k-test0003",
                      1883
                      );
IotDevice device{client};

void onConnectionEstablished()
{
  device.onConnectionEstablishedCallback();
};



void setup()
{
  Serial.begin(115200);
}

void loop()
{
  device.process();
}