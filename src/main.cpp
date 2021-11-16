#include "defines.h"
#include "definesCalculated.h"
#include "globalVariable.h"
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "Servo/Servo.h"



void setup() {
  Serial.begin(250000);
  Serial.println("Start");
  delay(50);  
  sei();
}

void loop() {
  
}