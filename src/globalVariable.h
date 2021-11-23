#ifndef globalVariable_h
#define globalVariable_h

#include <avr/io.h>
//#include "Servo/Servo.h"
//Globale Variablen, welche von allen Programmteilen aufgerfen werden können
volatile uint8_t pwm_setting[8];            //PWM Werte
uint8_t rxDataIn[18];                       //Werte der Funkverbindung
uint8_t currentBlinkCode = 0;               //Status LED
uint8_t currentBlinkColor = 1;              // 0=Rot 1=Gelb 2=Grün 3=Blau 4=Weiss
uint8_t failSafe = true;                       //Failsafe bsp. Verbidung zur Fernbedienung verloren.

long debugCounter;

#endif