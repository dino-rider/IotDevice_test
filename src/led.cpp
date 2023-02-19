#include "led.h"

LedBlinker::LedBlinker(int _led_pin) : led_pin(_led_pin)
{
  pinMode(led_pin, OUTPUT);
}

LedBlinker::~LedBlinker()
{
  if (this->xHandle != NULL)
  {
    this->stopService();
  }
}

// 0 = off, 1 = on, 2 = blink
void LedBlinker::setMode(int _mode)
{
  if (mode != _mode)
  {
    mode = _mode;
  }
}

bool LedBlinker::toggle()
{
  state = !state;
  digitalWrite(led_pin, state);
  return state;
}

void LedBlinker::process()
{
  switch (mode)
  {
  case 0:
    if (state == 0)
    {
      break;
    }
    else
    {
      state = 0;
      digitalWrite(led_pin, 0);
      // Serial.println("led off");
    }
    break;

  case 1:
    if (state == 1)
    {
      break;
    }
    else
    {
      state = 1;
      digitalWrite(led_pin, 1);
      // Serial.println("led on");
    }
    break;

  case 2:
    if ((millis() - lastBlinkTime) > blink_interval)
    {
      toggle();
      lastBlinkTime = millis();
    }
    break;
  default:
    break;
  }
}

bool LedBlinker::startAsService(int coreNumber)
{
  if (coreNumber != 1 & coreNumber != 0)
  {
    // invalid core number given
    return false;
  }
  if (coreNumber == 1)
  {
    // disableCore1WDT(); // we have to disable the Watchdog timer to prevent it from rebooting the ESP all the time another option would be to add a vTaskDelay but it would slow down the stepper
  }
  else if (coreNumber == 0)
  {
    // disableCore0WDT(); // we have to disable the Watchdog timer to prevent it from rebooting the ESP all the time another option would be to add a vTaskDelay but it would slow down the stepper
  }

  xTaskCreatePinnedToCore(
      LedBlinker::taskRunner, /* Task function. */
      "LedBlinker",           /* String with name of task (by default max 16 characters long) */
      2000,                   /* Stack size in bytes. */
      this,                   /* Parameter passed as input of the task */
      1,                      /* Priority of the task, 1 seems to work just fine for us */
      &this->xHandle,         /* Task handle. */
      coreNumber              /* the cpu core to use, 1 is where usually the Arduino Framework code (setup and loop function) are running, core 0 by default runs the Wifi Stack */
  );
  return true;
}

void LedBlinker::taskRunner(void *parameter)
{
  LedBlinker *inputRef = static_cast<LedBlinker *>(parameter);
  for (;;)
  {
    inputRef->process();
    vTaskDelay(100);
  }
}

void LedBlinker::stopService()
{
  vTaskDelete(this->xHandle);
  this->xHandle = NULL;
}

bool LedBlinker::isStartedAsService()
{
  return (this->xHandle != NULL);
}