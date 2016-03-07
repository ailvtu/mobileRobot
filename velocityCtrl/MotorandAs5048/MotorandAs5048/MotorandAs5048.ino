#include <MsTimer2.h>
#include <Wire.h>
#include <MotorandAs5048.h>
#include <PID_v1.h>

MotorandAs5048  m;
double Setpoint, Input, Output;
double Kp=2, Ki=0, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
double sp1,sp2;
void setup(){
  
  Serial.begin(9600);
  m.motorInit();
  m.setZeroReg();
  
  Input = analogRead(5);
  Setpoint = 100;
   //turn the PID on
  myPID.SetMode(AUTOMATIC);
  // MsTimer2::set(100, timerGetSpeed); // 500ms period
  // MsTimer2::start();
  sp1 = m.getSpeed(0);
  
}
void loop(){
  
 m.goForwaed();
 //m.Brake( RightMotorBrake);
 GetSpeed(0);
 GetSpeed(1);
 myPID.Compute();
 
  //analogWrite(6, Output);Serial.print("Output:" );Serial.println(Output);
 delay(1000);
}
void GetSpeed(int side){
  
  double errL,errR ;
 // Serial.print("L:");
 //  Serial.println(spL2);
   /*
   spL1 = m.getSpeed(1);
   Serial.print("R:");
   Serial.println(spL1);
  */
  //sp2 = m.getSpeed(1);
  if(side == 0){
    sp2 = m.getSpeed(0);
    if(sp2<sp1)
  { 
 errL = sp1- sp2;
  }else
  {
  sp1 = sp1+360;
  errL = sp1 - sp2;
  }
  Serial.print("errL:");
 Serial.println(errL);
  ///*****////
  }
  
  if(side ==1){
    sp2 = m.getSpeed(1);
    if(sp2>sp1)
  { 
 errR = sp2 - sp1;
  }else
  {
  sp2 = sp2+360;
  errR = sp2 - sp1;
  }
  Serial.print("errR:");
 Serial.println(errR);
  }

  //*********/

 
  sp1 = sp2;
}
