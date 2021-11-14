#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define minIn 172 
#define maxIn 1811 
#define minOut 0
#define maxOut 255

static volatile uint8_t newData = 0;
uint8_t buffer[25];
uint8_t rawBuffer[25];
uint8_t stateCounter;
uint8_t feedState;
long _goodFrames;
extern uint8_t rxDataIn[18];  

#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

void initRxProcessing();
long mapper();
void rxProcessing(void *pvParameters);

#ifdef __cplusplus
}
#endif