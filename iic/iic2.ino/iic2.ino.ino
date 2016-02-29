// Written by Dash
// 2016/02/21 

#include <Wire.h>
const byte SLAVE_ADDRESS = 0x41;
void setup () 
  {
  Wire.begin ();
  Serial.begin(9600);  
 
  } 
  // end of setup
void loop () 
  {
    uint16_t zero = readValue(0x16);
    Serial.println(zero);
    //  zeroRegW(zero);
   delay (20);
  }  // end of loop

 uint16_t readValue(uint8_t address){
  uint8_t Byte2Read = 2;
  byte requestResult;
  byte readArray[2];
  uint16_t  readValue = 0;
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(address);
  requestResult = Wire.endTransmission(false);

  Wire.requestFrom(SLAVE_ADDRESS,Byte2Read);
  for(byte i = 0;i<Byte2Read;i++){
      readArray[i] = Wire.read();
  }
  readValue = (((uint16_t)readArray[0])<<6);
  readValue +=  (readArray[1]&0x3F);
//  Serial.println(readArray[0], BIN);
//  Serial.println(readArray[1], BIN);
//  Serial.println(readValue, BIN);

   return readValue;
 }
void writeReg(uint8_t address,uint8_t value){
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();

  return;
}

void zeroRegW(uint16_t regVal){
  writeReg(0x16,(uint8_t) (regVal >> 6));
  writeReg(0x17, (uint8_t) (regVal & 0x3F));
  return;
}

uint8_t AddressRegR(void){
  return readReg8(0x15);
}
uint8_t readReg8(uint8_t address) {
  
  uint8_t readValue;
  byte requestResult;
  uint8_t nbByte2Read = 1;
  
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(address);
  requestResult = Wire.endTransmission(false);

  Wire.requestFrom(SLAVE_ADDRESS, nbByte2Read);
  readValue = (uint8_t) Wire.read();
  
  return readValue;
}

