#pragma once
#include <Arduino.h>
#include <vector>
#include <map>
#include "EspMQTTClient.h"
#include "Peripherals.h"
// #include "WebInterface.h"

class EspMQTTClient;
class Sensor;
class Output;
class LedOutput;

class MqttCredentials
{
  String mqttClientName;
  String mqttServerIp;
  String qttUsername;
  String mqttPassword;
  String mqttServerPort;
};

class WifiCredentials
{
  String wifiSsid;
  String wifiPassword;
};

class IotDevice: public EspMQTTCaller
{
private:
  String mainTopic = "den-k-89-house/test-device";
  EspMQTTClient &client;
  std::vector< Sensor* > sensors;
  std::vector< Output* > outputs;
  // WebInterface winterface;
  MqttCredentials mqtt;
  WifiCredentials wifi;
  void notify(String topic, String message);
  void storeCredentials();
  void readCredentials();
  // set up peripherials
  LedOutput onboardLed{this, "light_0", 2};
public:
  EspMQTTClient* getClient(){return &client;};
  IotDevice(EspMQTTClient &_client);
  void onConnectionEstablishedCallback();
  void cMessageReceivedCallback(const String &topicStr, const String &message);
  void publish(String topic, String message, bool retain);
  void process();
  int  getStatus();
  String getMainTopic(){return mainTopic;};
  void setMqttCredentials(MqttCredentials);
  void setWifiCredentials(WifiCredentials);
};
