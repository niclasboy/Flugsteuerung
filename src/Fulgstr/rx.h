#ifndef rx_h
#define rx_h

#include "defines.h"
#include "definesCalculated.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#define SBUS_FAILSAFE_INACTIVE 0
#define SBUS_FAILSAFE_ACTIVE   1
#define SBUS_STARTBYTE         0x0f
#define SBUS_ENDBYTE           0x00
#define SBUS_FAILSAFE          0x08

#define minIn 172 
#define maxIn 1811 
#define minOut 0
#define maxOut 255


extern uint8_t rxDataIn[18]; 
extern uint8_t failSafe;


void initRx();
void rxProcessing(void *pvParameters);



#endif