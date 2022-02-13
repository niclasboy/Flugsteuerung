#include "flugstr.h"

int motorSpeed[4];
int servoAngle[4];
Servo mainServo[4];

void initServos(){
    mainServo[0].attach(Servo1);
    mainServo[1].attach(Servo2);
    mainServo[2].attach(Servo3);
    mainServo[3].attach(Servo4);
}


void applyChanges(){//Called by RX in
    int yaw, roll, pitch, vtolAngle;
    int speedIn;
    pitch = map(rxDataIn[PitchChannel], 0, 255, MinPitch, MaxPitch);
    yaw = map(rxDataIn[YawChannel], 0, 255, MinYaw, MaxYaw);
    roll = map(rxDataIn[RollChannel], 0, 255, MinRoll, MaxRoll);
    vtolAngle = map(rxDataIn[AngleVTOL], 0, 255, 0, MaxVTOLAngle);
    speedIn = map(rxDataIn[ThrottleChannel], 0, 255, 0, 64 - HeadroomYaw); //Eigentlich bis 
    if (rxDataIn[Direction] == 255 && rxDataIn[Mode] == 0) //Nur im Normalflugmodus Erlauben
    {
        speedIn = -speedIn; //SpeedInwird negativ
    }

    if(rxDataIn[Mode] == 0)
    {
        //Normaler Flugmodus
        servoAngle[0] = Servo1BaseAngle - roll;
        servoAngle[1] = Servo2BaseAngle - roll;
        servoAngle[2] = Servo3BaseAngle + pitch - roll; //Hinten Links Servo
        servoAngle[3] = Servo4BaseAngle - pitch - roll; //Hinten Rechts Servo
        
        motorSpeed[0] = speedIn + yaw;
        motorSpeed[1] = speedIn - yaw;
        motorSpeed[2] = speedIn + yaw;
        motorSpeed[3] = speedIn - yaw; 
    }
    else
    {
        //Senkrechtstart
        servoAngle[0] = Servo1BaseAngleVTOL + vtolAngle;
        servoAngle[1] = Servo2BaseAngleVTOL + vtolAngle;
        servoAngle[2] = Servo3BaseAngleVTOL + vtolAngle; //Hinten Links Servo
        servoAngle[3] = Servo4BaseAngleVTOL + vtolAngle; //Hinten Rechts Servo

        motorSpeed[0] = speedIn + pitch + roll;
        motorSpeed[1] = speedIn + pitch - roll;
        motorSpeed[2] = speedIn - pitch + roll;
        motorSpeed[3] = speedIn - pitch - roll; 
    }

   
    if(motorSpeed[0] >= 0)
    {
        pwm_setting[0] = constrain(motorSpeed[0],0,64);
        pwm_setting[1] = 0;
    }
    else
    {
        pwm_setting[1] = constrain(motorSpeed[0],0,64);
        pwm_setting[0] = 0;
    }
    if(motorSpeed[1] >= 0)
    {
        pwm_setting[2] = constrain(motorSpeed[1],0,64);
        pwm_setting[3] = 0;
    }
    else
    {
        pwm_setting[3] = constrain(motorSpeed[1],0,64);
        pwm_setting[2] = 0;
    }
    if(motorSpeed[2] >= 0)
    {
        pwm_setting[4] = constrain(motorSpeed[2],0,64);
        pwm_setting[5] = 0;
    }
    else
    {
        pwm_setting[5] = constrain(motorSpeed[2],0,64);
        pwm_setting[4] = 0;
    }
    if(motorSpeed[3] >= 0)
    {
        pwm_setting[6] = constrain(motorSpeed[3],0,64);
        pwm_setting[7] = 0;
    }
    else
    {
        pwm_setting[7] = constrain(motorSpeed[3],0,64);
        pwm_setting[6] = 0;
    }
    
    
    
    servoAngle[0] = constrain(servoAngle[0],minServoAngle,maxServoAngle);
    servoAngle[1] = constrain(servoAngle[1],minServoAngle,maxServoAngle);
    servoAngle[2] = constrain(servoAngle[2],minServoAngle,maxServoAngle);
    servoAngle[3] = constrain(servoAngle[3],minServoAngle,maxServoAngle);
    mainServo[0].write(servoAngle[0]);    
    mainServo[1].write(servoAngle[1]);    
    mainServo[2].write(servoAngle[2]);    
    mainServo[3].write(servoAngle[3]);

    #if DEBUG

        Serial.print("Thro:   ");
        Serial.print(speedIn);
        Serial.print("  ");
        Serial.print("Roll:   ");
        Serial.print(roll);
        Serial.print("  ");
        Serial.print("Elev:   ");
        Serial.print(pitch);
        Serial.print("  ");
        Serial.print("YAW:   ");
        Serial.print(yaw);
        Serial.print("  ");
        Serial.print("VTOL:   ");
        Serial.print(vtolAngle);
        Serial.print("  ");

        Serial.print("Servos:   ");
        Serial.print(servoAngle[0]);
        Serial.print("  ");
        Serial.print(servoAngle[1]);
        Serial.print("  ");
        Serial.print(servoAngle[2]);
        Serial.print("  ");
        Serial.print(servoAngle[3]);
        Serial.print("  ");
        Serial.print("Motor:   ");
        Serial.print(motorSpeed[0]);
        Serial.print("  ");
        Serial.print(motorSpeed[1]);
        Serial.print("  ");
        Serial.print(motorSpeed[2]);
        Serial.print("  ");
        Serial.println(motorSpeed[3]);
    #endif

} 
