#define minServoAngle 0                    //Max Auslenkung
#define maxServoAngle 180                  //Min Auslenkung

#define Servo1BaseAngle 90                 //Basiswert für Servo 1
#define Servo2BaseAngle 90                 //Basiswert für Servo 2
#define Servo3BaseAngle 90                 //Basiswert für Servo 3
#define Servo4BaseAngle 90                 //Basiswert für Servo 4

#define Servo1BaseAngleVTOL 0              //Basiswert für Servo 1
#define Servo2BaseAngleVTOL 0              //Basiswert für Servo 2
#define Servo3BaseAngleVTOL 0              //Basiswert für Servo 3
#define Servo4BaseAngleVTOL 0              //Basiswert für Servo 4

#define MaxVTOLAngle 90                    //Max VTOL Change Angle

#define ThrottleChannel 0                   //Throttel Kanal
#define PitchChannel 2                      //Pitch Kanal
#define YawChannel 3                        //Yaw Kanal
#define RollChannel 1                       //Roll Kanal

#define Mode 6                            //Reserviert für Modi bsp. Pitch/Roll Stabilizer
#define AngleVTOL 7
#define Lights 4                           //Reserviert Beleuchtung einschalten 
#define Direction 5


#define MinPitch -50                        //Eingang kann Servo um 20° negativ Verändern
#define MaxPitch 50                         //Eingang kann Servo um 20° positiv Verändern

#define HeadroomYaw 0                      //Motorleistung Begrenezen um Headroom beim Yawen zu haben
#define MinYaw -20                          //Abnahme der PWM Leistung um 20 "Stufen" von 64. 
#define MaxYaw 20                           //Zunahme der PWM Leistung um 20 "Stufen" von 64. 

#define MinRoll -50                         //Eingang kann Servo um 20° negativ Verändern
#define MaxRoll 50                          //Eingang kann Servo um 20° positiv Verändern



//PWM Settings
#define F_PWM 100                       // PWM-Frequenz in Hz
#define PWM_STEPS 64                   // PWM-Schritte pro Zyklus(1..64)
#define PWM_PORT PORTA                  // Port für PWM
#define PWM_DDR DDRA                    // Datenrichtungsregister für PWM
#define PWM_PORT2 PORTL                  // Port für PWM
#define PWM_DDR2 DDRL                    // Datenrichtungsregister für PWM

//PWM Settings
//Servo Settings
#define Servo1 7
#define Servo2 6
#define Servo3 5
#define Servo4 4
//Servo Settings
//Status LED
#define statusLed 13
#define strobeLed 11
#define posLight1 9
#define posLight2 8
//Status LED


#define DEBUG true