#include "blink.h"

void initLEDs()
{
    pinMode(statusLed, OUTPUT);
    pinMode(strobeLed, OUTPUT);
    pinMode(posLight1, OUTPUT);
    pinMode(posLight2, OUTPUT);
    xTaskCreate(statusLED, "StatLed", 128, NULL, 0, NULL);
    xTaskCreate(belLED, "StatLed", 128, NULL, 0, NULL);
}

void statusLED(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    if(failSafe == true){
        digitalWrite(statusLed, HIGH);
        vTaskDelay(200 / portTICK_PERIOD_MS);
        digitalWrite(statusLed, LOW);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    else{
        digitalWrite(statusLed, HIGH);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    }
    //Serial.println(rxDataIn[Lights]);
  }
}

void belLED(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    if(rxDataIn[Lights] == 0)
    {
        digitalWrite(strobeLed, LOW);
        digitalWrite(posLight1, LOW);
        digitalWrite(posLight2, LOW);
    }
    else if (rxDataIn[Lights] == 127)
    {
        digitalWrite(posLight1, HIGH);
        digitalWrite(posLight2, HIGH);
    }
    else if (rxDataIn[Lights] == 255)
    {
        digitalWrite(posLight1, HIGH);
        digitalWrite(posLight2, HIGH);
        digitalWrite(strobeLed, HIGH);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        digitalWrite(strobeLed, LOW);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        digitalWrite(strobeLed, HIGH);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        digitalWrite(strobeLed, LOW);

    }
    vTaskDelay(850 / portTICK_PERIOD_MS); // wait for one second
    //Serial.println(rxDataIn[Lights]);
  }
}