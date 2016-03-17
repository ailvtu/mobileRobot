#include <MsTimer2.h>
#include <Wire.h>
#include <MotorandAs5048.h>
#include <PID_v1.h>

#define forward  0
#define backward  1


MotorandAs5048  m;

//double Setpoint, Input, Output;
//double Kp=2, Ki=0, Kd=0;
//PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup(){
 Serial.begin(9600);
  m.motorInit();
  m.setZeroReg();

 
//  Input = velo1*10;
//  Setpoint = 255;
//   //turn the PID on
//  myPID.SetMode(AUTOMATIC);
  
  // MsTimer2::set(100, timerGetSpeed); // 500ms period
  // MsTimer2::start();
m.setSpeed(forward,forward,255,255);
}
void loop(){
 //m.Brake( RightMotorBrake);
/*
 GetSpeed();
 Serial.print("LV:");
 Serial.println(velo1);
  Serial.print("RV:");
 Serial.println(velo2);
 */

 m.printInf();
//Serial.println(m.velo1);
//Serial.println(m.velo2);
// Input = 200;
// myPID.Compute();
// Serial.println(Output);
// digitalWrite(LeftMotorDire,1);    
// analogWrite(LeftMotorSpeed,Output);
  //analogWrite(6, Output);Serial.print("Output:" );Serial.println(Output);
 delay(100);
}


