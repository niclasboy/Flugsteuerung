#define minServoAngle 45                    //Max Auslenkung
#define maxServoAngle (180 - minServoAngle) //Min Auslenkung

#define Servo1BaseAngle 90                  //Basiswert für Servo 1
#define Servo2BaseAngle 90                  //Basiswert für Servo 2
#define Servo3BaseAngle 90                  //Basiswert für Servo 3
#define Servo4BaseAngle 90                  //Basiswert für Servo 4

#define ThrottleChannel 0                   //Throttel Kanal
#define PitchChannel 2                      //Pitch Kanal
#define YawChannel 3                        //Yaw Kanal
#define RollChannel 1                       //Roll Kanal

#define MinPitch -50                        //Eingang kann Servo um 20° negativ Verändern
#define MaxPitch 50                         //Eingang kann Servo um 20° positiv Verändern

#define HeadroomYaw 14                      //Motorleistung Begrenezen um Headroom beim Yawen zu haben
#define MinYaw -20                          //Abnahme der PWM Leistung um 20 "Stufen" von 64. 
#define MaxYaw 20                           //Zunahme der PWM Leistung um 20 "Stufen" von 64. 

#define MinRoll -50                         //Eingang kann Servo um 20° negativ Verändern
#define MaxRoll 50                          //Eingang kann Servo um 20° positiv Verändern

#define Mode -1                             //Reserviert für Modi bsp. Pitch/Roll Stabilizer
#define Lights -1                           //Reserviert Beleuchtung einschalten 

//PWM Settings
#define F_PWM 100                       // PWM-Frequenz in Hz
#define PWM_STEPS 64                   // PWM-Schritte pro Zyklus(1..256)
#define PWM_PORT PORTA                  // Port für PWM
#define PWM_DDR DDRA                    // Datenrichtungsregister für PWM
//PWM Settings
//Servo Settings
#define Servo1 30
#define Servo2 31
#define Servo3 32
#define Servo4 33
//Servo Settings
//Status LED
#define statusR 11
#define statusG 12
#define statusB 13
//Status LED