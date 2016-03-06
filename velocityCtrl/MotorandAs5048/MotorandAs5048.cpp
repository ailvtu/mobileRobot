/***********************/

/*********************/


#include "MotorandAs5048.h"
#include "Wire.h"

/*****************************

*****************************/
MotorandAs5048::MotorandAs5048(){
	receiveValue_L = 0;
             receiveValue_R = 0;
	return;
}
/*****************************

*****************************/
MotorandAs5048::~MotorandAs5048(){
	return;
}
/*****************************

*****************************/
void MotorandAs5048::motorInit(){
             
             Wire.begin();

	pinMode(LeftMotorSpeed,OUTPUT); 
	pinMode(LeftMotorDire,OUTPUT);                            
	pinMode(LeftMotorBrake,OUTPUT);


	pinMode(RightMotorSpeed,OUTPUT);  
	pinMode(RightMotorDir,OUTPUT);                            
	pinMode(RightMotorBrake,OUTPUT);           
}
/*****************************

*****************************/
void MotorandAs5048::goForwaed(){
	digitalWrite(LeftMotorDire,1);                         // drive left  motor forward
	analogWrite(LeftMotorSpeed,200);
	digitalWrite(RightMotorDir,0);                         // drive right motor forward
	analogWrite(RightMotorSpeed,200);                            
}
/*****************************

*****************************/

void MotorandAs5048::Brake(int side){
	digitalWrite(side,1);
}

/*****************************
write the Register adrress
*****************************/

void MotorandAs5048::writeReg(uint8_t address,uint8_t As5048Address){
	Wire.beginTransmission(As5048Address);
	Wire.write(address);            
	Wire.endTransmission(false);//sends a restart message after transmission
}
/*****************************
16 bit value got from 2 8bits registers (7..0 MSB + 5..0 LSB) => 14 bits value
*****************************/
uint16_t MotorandAs5048::readValue(int as5048b_Address){
	byte readArray[2];
	uint16_t readValue = 0;
	Wire.requestFrom(as5048b_Address,request_num); 
	for (byte i = 0; i < request_num; i++) 
		{
		readArray[i] = Wire.read();
		}
	readValue = (readArray[0] << 6) + (readArray[1] & 0x3F); 
	return readValue;
	}

/*********
**********/
void MotorandAs5048::setZeroReg(void) {
             writeReg(angleRegAdd,as5048b_Address_L);
	uint16_t zero1 = MotorandAs5048::readValue(as5048b_Address_L);
	writeReg(angleRegAdd,as5048b_Address_R);
	uint16_t zero2 = MotorandAs5048::readValue(as5048b_Address_R);
	MotorandAs5048::zeroRegW(zero1,zero2);
	return;
}

/**************************************************************************/

/**************************************************************************/
void MotorandAs5048::zeroRegW(uint16_t regVal1,uint16_t regVal2) {

	MotorandAs5048::writeZero(AS5048B_ZEROMSB_REG, (uint8_t) (regVal1 >> 6),as5048b_Address_L);
	MotorandAs5048::writeZero(AS5048B_ZEROLSB_REG, (uint8_t) (regVal1 & 0x3F),as5048b_Address_L);

	MotorandAs5048::writeZero(AS5048B_ZEROMSB_REG, (uint8_t) (regVal2 >> 6),as5048b_Address_R);
	MotorandAs5048::writeZero(AS5048B_ZEROLSB_REG, (uint8_t) (regVal2 & 0x3F),as5048b_Address_R);
	return;
}

void MotorandAs5048::writeZero(uint8_t address, uint8_t value,uint8_t As5048Address) {

	Wire.beginTransmission(As5048Address);
	Wire.write(address);
	Wire.write(value);
	Wire.endTransmission();

	return;
}


/*******************

******************/
double MotorandAs5048::getSpeed(){
	writeReg(angleRegAdd,as5048b_Address_L);
	receiveValue_L = readValue(as5048b_Address_L);
	writeReg(angleRegAdd,as5048b_Address_R);
	receiveValue_R = readValue(as5048b_Address_R);
	double angle1 = (receiveValue_L / RESOLUTION) * 360.0;
	double angle2 = (receiveValue_R / RESOLUTION) * 360.0;
             speed = (angle1+angle2);//never compute
	return speed;
}