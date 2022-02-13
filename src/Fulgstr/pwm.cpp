#include "pwm.h"

ISR(TIMER3_COMPA_vect) {
    static uint8_t pwm_cnt=0;
    uint8_t tmp=0;
    uint8_t tmp2=0;

    OCR3A += (uint16_t)T_PWM;
        
    if (pwm_setting[0] > pwm_cnt) tmp |= (1<<5);
    if (pwm_setting[1] > pwm_cnt) tmp |= (1<<4);
    if (pwm_setting[2] > pwm_cnt) tmp |= (1<<6);
    if (pwm_setting[3] > pwm_cnt) tmp |= (1<<7);
    if (pwm_setting[4] > pwm_cnt) tmp2 |= (1<<4);
    if (pwm_setting[5] > pwm_cnt) tmp2 |= (1<<5);
    if (pwm_setting[6] > pwm_cnt) tmp2 |= (1<<3);
    if (pwm_setting[7] > pwm_cnt) tmp2 |= (1<<2);
    PWM_PORT = tmp;                         // PWMs aktualisieren
    PWM_PORT2 = tmp2;                         // PWMs aktualisieren
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
    PWM_DDR = 0xFF;         // Port als Ausgang  
    PWM_DDR2 = 0xFF;         // Port als Ausgang    
    // Timer 1 OCRA1, als variablem Timer nutzen
    TCCR3B = 1;             // Timer läuft mit vollem Systemtakt
    TIMSK3 = (1<<OCIE3A);   // Interrupt freischalten
}