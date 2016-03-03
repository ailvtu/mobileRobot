#include <Wire.h>
#include <MotorandAs5048.h>

MotorandAs5048  m;
void setup(){
  Serial.begin(9600);
  m.motorInit();
}
void loop(){
  
 m.goForwaed();
 //m.Brake( RightMotorBrake);
 double sp = m.getSpeed();
  Serial.print("speed:");
 Serial.println(sp);
}

