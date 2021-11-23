#ifndef pwm_h
#define pwm_h

#include "defines.h"
#include "definesCalculated.h"
#include <avr/io.h>
#include <Arduino.h>
#include <avr/interrupt.h>
#include <Arduino_FreeRTOS.h>

extern volatile uint8_t pwm_setting[8];
extern long debugCounter;

void initMotors();



#endif