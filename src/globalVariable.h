#include <avr/io.h>
#include "Servo/Servo.h"
//Globale Variablen, welche von allen Programmteilen aufgerfen werden können
volatile uint8_t pwm_setting[8];            //PWM Werte
Servo mainServo[4];                         //Servos
uint8_t rxDataIn[18];                       //Werte der Funkverbindung
uint8_t currentBlinkCode = 0;               //Status LED
bool failSafe = true;                       //Failsafe bsp. Verbidung zur Fernbedienung verloren.
