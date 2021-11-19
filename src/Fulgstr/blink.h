#ifndef blink_h
#define blink_h

#include "defines.h"
#include "definesCalculated.h"
#include <avr/io.h>
#include <Servo/Servo.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

extern uint8_t rxDataIn[18];  

void initLEDs();
void ledProc(void *pvParameters);


#endif