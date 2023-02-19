#pragma once
#include "Arduino.h"
#include "EspMQTTClient.h"
// #include "IotDevice.h"

class IotDevice;

class Peripheral: public EspMQTTCaller
{
protected:
  
  IotDevice *device;
  String topic;
  void storeState();
  void readState();
public:
  Peripheral(IotDevice *_device, String _topic);
  void publish(String message, bool retain);
  void subscribe();
  String read();
  void setTopic(String);
  String getTopic();
  virtual void cMessageReceivedCallback(const String &topicStr, const String &message);
};

class Sensor: public Peripheral
{
public:
  Sensor(IotDevice *_device, String _topic);
  virtual void onChange(){};
  virtual void cMessageReceivedCallback(const String &topicStr, const String &message);
};

class Output: public Peripheral
{
public:
  Output(IotDevice *_device, String _topic);
  virtual void execute(String command) {Serial.println(command);};
  virtual void cMessageReceivedCallback(const String &topicStr, const String &message);
};

class LedOutput: public Output
{
private:
  byte ledPin;
  bool state;
public:
  LedOutput(IotDevice *_device, String _topic, byte _ledPin = 2);
  void execute(String command);
};
