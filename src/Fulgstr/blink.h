#ifndef blink_h
#define blink_h

#include "defines.h"
#include "definesCalculated.h"
#include <avr/io.h>
#include <Servo/Servo.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

extern uint8_t rxDataIn[18];  
extern volatile uint8_t pwm_setting[8]; 
extern uint8_t failSafe;

extern long debugCounter;

void initLEDs();
void statusLED(void *pvParameters);
void belLED(void *pvParameters);



#endif