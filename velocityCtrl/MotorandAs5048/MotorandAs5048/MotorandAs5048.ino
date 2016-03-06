#include <Wire.h>
#include <MotorandAs5048.h>
#include <PID_v1.h>

MotorandAs5048  m;
double Setpoint, Input, Output;
double Kp=2, Ki=0, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup(){
  Serial.begin(9600);
  m.motorInit();
  m.setZeroReg();
  Input = analogRead(5);
  Setpoint = 100;
   //turn the PID on
  myPID.SetMode(AUTOMATIC);
  
}
void loop(){
  
 m.goForwaed();
 //m.Brake( RightMotorBrake);
 double sp = m.getSpeed();
 Input = sp;
 myPID.Compute();
 Serial.print("speed:");
 Serial.println(sp);
  analogWrite(6, Output);Serial.print("Output:" );Serial.println(Output);
  delay(1000);
}

