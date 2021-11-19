#include "blink.h"

void initLEDs()
{
    xTaskCreate(ledProc, "LEDPROC", 128, NULL, 0, NULL);
}

void ledProc(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
  }
}