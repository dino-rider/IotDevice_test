#include "IotDevice.h"
#include "config.h"

EspMQTTClient client(
                      CONFIG_SSID,
                      CONFIG_PASS,
                      CONFIG_MQTTBROKER,
                      CONFIG_MQTTNAME,
                      CONFIG_MQTTPORT
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