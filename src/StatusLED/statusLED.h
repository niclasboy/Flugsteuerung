#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/io.h>

extern uint8_t currentBlinkCode; 
const int blinkCodes[2][2] = {{100,100},{50,950}};


#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

void initBlinkTask();
void TaskBlink(void *pvParameters);

#ifdef __cplusplus
}
#endif

