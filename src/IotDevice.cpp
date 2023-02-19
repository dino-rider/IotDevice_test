#include "IotDevice.h"

// void onMessage(const String &topicStr, const String &message);
void onConnectionEstablished();

IotDevice::IotDevice(EspMQTTClient &_client): client(_client)
{
  // client = _client;
  readCredentials();
  // use credentials here
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  // client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("den-k-89-house/test-device/status", "lost", true);  // You can activate the retain flag by setting the third parameter to true
  
  //adding peripherials to vectors
  outputs.push_back(&onboardLed);
}

void IotDevice::onConnectionEstablishedCallback()
{
  Serial.println("Connected");
  client.subscribe("den-k-89-house/test-device/#", static_cast<EspMQTTCaller*>(this), 0);
  for (Sensor* sensor: sensors)
  {
    (*sensor).subscribe();
  }
  for (Output* output: outputs)
  {
    (*output).subscribe();
  }
  client.publish("den-k-89-house/test-device/status", "ready", true);
}

void IotDevice::cMessageReceivedCallback(const String &topicStr, const String &message)
{
  Serial.print(topicStr);
  Serial.print(" - ");
  Serial.println(message);
  // notify(topicStr, message);
}

void IotDevice::notify(String topic, String message)
{
  // for (Sensor* sensor: sensors)
  // {
  //   (*sensor).onMessage(topic, message);
  // }
  // for (Output* output: outputs)
  // {
  //   (*output).onMessage(topic, message);
  // }
}

void IotDevice::publish(String topic, String message, bool retain)
{
  client.publish(topic, message, retain);
}

void IotDevice::storeCredentials()
{

}

void IotDevice::readCredentials()
{

}

void IotDevice::setMqttCredentials(MqttCredentials)
{

}

void IotDevice::setWifiCredentials(WifiCredentials)
{

}


void IotDevice::process()
{
  client.loop();
}
