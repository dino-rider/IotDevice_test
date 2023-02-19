#pragma once
#include <Arduino.h>

// Control led outputs in the background

class LedBlinker
{
public:
  LedBlinker() {}
  LedBlinker(int led_pin);
  ~LedBlinker();
  void process();
  void setMode(int _mode);
  bool toggle();
  bool startAsService(int coreNumber);
  void stopService();
  bool isStartedAsService();
  bool wait_for_input(void);

private:
  static void taskRunner(void *parameter);
  int led_pin;
  unsigned int blink_interval = 500;
  unsigned long lastBlinkTime = 0;
  int mode = 0;
  bool state = 0;
  TaskHandle_t xHandle = NULL;
};