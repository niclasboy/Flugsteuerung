#include "pwm.h"

ISR(TIMER3_COMPA_vect) {
    static uint8_t pwm_cnt=0;
    uint8_t tmp=0;
    

    OCR3A += (uint16_t)T_PWM;
        
    if (pwm_setting[0] > pwm_cnt) tmp |= (1<<7);
    //if (pwm_setting[0] > pwm_cnt) debugCounter++;
    if (pwm_setting[1] > pwm_cnt) tmp |= (1<<6);
    if (pwm_setting[2] > pwm_cnt) tmp |= (1<<5);
    if (pwm_setting[3] > pwm_cnt) tmp |= (1<<4);
    if (pwm_setting[4] > pwm_cnt) tmp |= (1<<3);
    if (pwm_setting[5] > pwm_cnt) tmp |= (1<<2);
    if (pwm_setting[6] > pwm_cnt) tmp |= (1<<1);
    if (pwm_setting[7] > pwm_cnt) tmp |= (1<<0);
    PWM_PORT = tmp;                         // PWMs aktualisieren
    if (pwm_cnt==(uint8_t)(PWM_STEPS-1))
    {
        pwm_cnt=0;
    }             
    else
    {
        pwm_cnt++;
    }
        
}

void initMotors(){
    pinMode(MotorEnable1, OUTPUT);
    pinMode(MotorEnable2, OUTPUT);
    pinMode(MotorEnable3, OUTPUT);
    pinMode(MotorEnable4, OUTPUT);
    digitalWrite(MotorEnable1, HIGH);
    digitalWrite(MotorEnable2, HIGH);
    digitalWrite(MotorEnable3, HIGH);
    digitalWrite(MotorEnable4, HIGH);
    PWM_DDR = 0xFF;         // Port als Ausgang    
    // Timer 1 OCRA1, als variablem Timer nutzen
    TCCR3B = 1;             // Timer läuft mit vollem Systemtakt
    TIMSK3 = (1<<OCIE3A);   // Interrupt freischalten
}