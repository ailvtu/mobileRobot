#include <Wire.h>

#define as5048b_Address 0x40  // left motor 0x40,right motor 0x41
#define request_num 2         // request 2 byte 
#define angleRegAdd 0xFE
#define RESOLUTION 16384.0    ////14 bits

#define lmbrkpin     4  //  D4 - left  motor brake        control    pin    HIGH = Brake 
#define LeftMotorDire     2  //  D2 - left  motor direction    control    pin    HIGH = Forward   Low = Reverse
#define LeftMotorSpeed     3  //  D3 - left  motor pulse width  modulation pin    0 - 255          Speed and Brake 


#define rmbrkpin     9  //  D9 - right motor brake        control    pin    HIGH = Brake 
#define RightMotorDir    10  // D10 - right motor direction    control    pin    HIGH = Forward   Low = Reverse
#define RightMotorSpeed    11  // D11 - right motor pulse width  modulation pin    0 - 255          Speed and Brake 

void setup() 
{
  Serial.begin(9600);
  Wire.begin();


  pinMode(LeftMotorSpeed,OUTPUT); 
  pinMode(LeftMotorDire,OUTPUT);                            
  pinMode(lmbrkpin,OUTPUT);


  pinMode(RightMotorSpeed,OUTPUT);  
  pinMode(RightMotorDir,OUTPUT);                            
  pinMode(rmbrkpin,OUTPUT);                   
  
}

void loop() 
{ 
  uint16_t receiveValue = 0;
  
      digitalWrite(LeftMotorDire,1);                         // drive left  motor forward
      analogWrite(LeftMotorSpeed,200);
      digitalWrite(RightMotorDir,0);                         // drive right motor forward
      analogWrite(RightMotorSpeed,200);
      delayMicroseconds(500);                            // limit full power to 50uS

  
  writeReg(angleRegAdd);
  receiveValue = readValue();
  double angle = (receiveValue / RESOLUTION) * 360.0;
  Serial.println(angle);
}
/*
write the Register adrress
*/
void writeReg(uint8_t address){
  Wire.beginTransmission(as5048b_Address);
  Wire.write(address);            
  Wire.endTransmission(false);//sends a restart message after transmission
}
/*
  16 bit value got from 2 8bits registers (7..0 MSB + 5..0 LSB) => 14 bits value
*/
uint16_t readValue(void){
   byte readArray[2];
   uint16_t readValue = 0;
   Wire.requestFrom(as5048b_Address, request_num); 
  for (byte i = 0; i < request_num; i++) 
  {
    readArray[i] = Wire.read();
  }
  readValue = (readArray[0] << 6) + (readArray[1] & 0x3F); 
  return readValue;
}

