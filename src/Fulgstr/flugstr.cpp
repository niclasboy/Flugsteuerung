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
    int yaw, roll, pitch;
    byte speedIn;
    pitch = map(rxDataIn[PitchChannel], 0, 255, MinPitch, MaxPitch);
    yaw = map(rxDataIn[YawChannel], 0, 255, MinYaw, MaxYaw);
    roll = map(rxDataIn[RollChannel], 0, 255, MinRoll, MaxRoll);
    servoAngle[0] = Servo1BaseAngle ;
    servoAngle[1] = Servo2BaseAngle;
    servoAngle[2] = Servo3BaseAngle + pitch - roll; //Hinten Links Servo
    servoAngle[3] = Servo4BaseAngle - pitch - roll; //Hinten Rechts Servo
    speedIn = map(rxDataIn[ThrottleChannel], 0, 255, 0, 64 - HeadroomYaw); //Eigentlich bis 
    motorSpeed[0] = speedIn + yaw;
    motorSpeed[1] = speedIn - yaw;
    motorSpeed[2] = speedIn + yaw;
    motorSpeed[3] = speedIn - yaw;    
    //Serial.println(rxDataIn[Direction]);
    if(rxDataIn[Direction] == 0)
    {
        pwm_setting[0] = constrain(motorSpeed[0],0,64);
        pwm_setting[2] = constrain(motorSpeed[1],0,64);
        pwm_setting[4] = constrain(motorSpeed[2],0,64);
        pwm_setting[6] = constrain(motorSpeed[3],0,64);
        pwm_setting[1] = 0;
        pwm_setting[3] = 0;
        pwm_setting[5] = 0;
        pwm_setting[7] = 0;
    }
    else if(rxDataIn[Direction] == 255)
    {
        pwm_setting[1] = constrain(motorSpeed[0],0,64);
        pwm_setting[3] = constrain(motorSpeed[1],0,64);
        pwm_setting[5] = constrain(motorSpeed[2],0,64);
        pwm_setting[7] = constrain(motorSpeed[3],0,64);
        pwm_setting[0] = 0;
        pwm_setting[2] = 0;
        pwm_setting[4] = 0;
        pwm_setting[6] = 0;
    }
    else
    {
        pwm_setting[1] = 0;
        pwm_setting[3] = 0;
        pwm_setting[5] = 0;
        pwm_setting[7] = 0;
        pwm_setting[0] = 0;
        pwm_setting[2] = 0;
        pwm_setting[4] = 0;
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
} 
