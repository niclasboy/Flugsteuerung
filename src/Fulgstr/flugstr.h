#ifndef flugstr_h
#define flugstr_h

#include "defines.h"
#include "definesCalculated.h"
#include <avr/io.h>
#include <Servo/Servo.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// mainServo[4] 0-180 1 VL 2 VR 3 HL 4 HR
// pwm_setting[8] 0-64 1 VL 2 VR 3 HL 4 HR
extern volatile uint8_t pwm_setting[8];
extern uint8_t rxDataIn[18];  

void applyChanges();
void initServos();


#endif