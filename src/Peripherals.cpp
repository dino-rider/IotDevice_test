#include "Peripherals.h"
#include "Arduino.h"
#include "IotDevice.h"

void Peripheral::publish(const String message, bool retain)
{
 device->publish(topic, message, retain);
}

void Peripheral::subscribe()
{
  device->getClient()->subscribe(topic, static_cast<EspMQTTCaller*>(this), 0);
}

void Peripheral::storeState()
{

}

void Peripheral::readState()
{

}

Peripheral::Peripheral(IotDevice *_device, String _topic): device(_device)
{
  topic = device->getMainTopic()+"/"+_topic;
}

String Peripheral::read()
{
  return "test";
}

void Peripheral::setTopic(String _topic)
{
  topic = device->getMainTopic()+"/"+_topic;
}

String Peripheral::getTopic()
{
 return topic;
}

void Peripheral::cMessageReceivedCallback(const String &topicStr, const String &message)
{

}

Output::Output(IotDevice *_device, String _topic): Peripheral(_device, _topic)
{

}

void Output::cMessageReceivedCallback(const String &topicStr, const String &message)
{
  execute(message);
}

LedOutput::LedOutput(IotDevice *_device, String _topic, byte _ledPin): Output(_device,_topic) ,ledPin(_ledPin), state(false)
{
  pinMode(ledPin, OUTPUT);
  Serial.print("onBoardLed topic:");
  Serial.println(topic);
}

void LedOutput::execute(String command)
{
  if (command == "ON")
  {
    Serial.println("Onboard LED ON");
    digitalWrite(ledPin, HIGH);
    return;
  }
  if (command == "OFF")
  {
    Serial.println("Onboard LED OFF");
    digitalWrite(ledPin, LOW);
    return;
  }
}