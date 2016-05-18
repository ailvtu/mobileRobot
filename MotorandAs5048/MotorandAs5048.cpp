/***********************/

/*********************/


#include "MotorandAs5048.h"
#include "Wire.h"

/*****************************

*****************************/
MotorandAs5048::MotorandAs5048(){
	Wire.begin();
	receiveValue_L = 0;
             receiveValue_R = 0;
  	lastT = millis();
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

             spL1 =MotorandAs5048::getPoint(0);
  	spR1 = MotorandAs5048::getPoint(1);
             
	pinMode(LeftMotorSpeed,OUTPUT); 
	pinMode(LeftMotorDire,OUTPUT);                            
	pinMode(LeftMotorBrake,OUTPUT);


	pinMode(RightMotorSpeed,OUTPUT);  
	pinMode(RightMotorDir,OUTPUT);                            
	pinMode(RightMotorBrake,OUTPUT);           
}
/*****************************

*****************************/
void MotorandAs5048::setSpeed(int dirL,int dirR,int pwmL,int pwmR){
	digitalWrite(LeftMotorDire,dirL);                         // drive left  motor forward
	analogWrite(LeftMotorSpeed,pwmL);
	digitalWrite(RightMotorDir,dirR);                         // drive right motor forward
	analogWrite(RightMotorSpeed,pwmR);                            
}
void MotorandAs5048::checkSpeed(){
           

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
double MotorandAs5048::getPoint(int side ){
	double angle;
	if (side==0){
	writeReg(angleRegAdd,as5048b_Address_L);
	receiveValue_L = readValue(as5048b_Address_L);
	angle = (receiveValue_L / RESOLUTION) * 360.0;
	
	}
	if (side ==1){
	writeReg(angleRegAdd,as5048b_Address_R);
	receiveValue_R = readValue(as5048b_Address_R);
	 angle = (receiveValue_R / RESOLUTION) * 360.0;
	}
	return angle;
}
void  MotorandAs5048::convertoSpeed(int direction,double &velo1,double &velo2){
  //the problem is not solving the wheel s have run more one circle
	double errL,errR ;
	unsigned long errTime;
	nowT = millis();
	errTime = (nowT- lastT);
            if(direction==1){   //backward Left motor angle is decreasing and right is opposite
	            	spL2 = MotorandAs5048::getPoint(0);
		if(spL2<spL1)
			{ 
			errL = spL1- spL2;
			}
		else
			{
			spL1 = spL1+360;
			errL = spL1 - spL2;
			spL1 = spL1-360;
			}
		
		velo1 =1000*(errL/360)*64/errTime;  //64:the circle of wheel
		///*****////

		spR2 =MotorandAs5048::getPoint(1);
			if(spR2>spR1)
			{ 
			
			errR = spR2 - spR1;
			}
		else
			{
		
			spR2 = spR2+360;
			errR = spR2 - spR1;
			spR2 = spR2-360;
			}
		
		velo2 = 1000*(errR/360)*64/errTime;
            }
	if(direction==0){//  //backward right angle is decreasing and left opposite
	            	spR2 = MotorandAs5048::getPoint(1);
		if(spR2<spR1)
			{ 
			errR= spR1- spR2;
			}
		else
			{
			spR1 = spR1+360;
			errR = spR1 - spR2;
			spR1 = spR1-360;
			}
		velo2 =1000* (errR/360)*64/errTime;
		/*
		Serial.print("errR:");
		Serial.print(errR);
		Serial.print("   errTime:");
		Serial.print(errTime);
		Serial.print("  velo2:");
	             Serial.println(velo2);*/
		///*****////

		spL2 =MotorandAs5048::getPoint(0);
			if(spL2>spL1)
			{ 
			
			errL = spL2 - spL1;
			}
		else
			{
			
			spL2 = spL2+360;
			errL = spL2 - spL1;
			spL2 = spL2-360;
			}
		
		
		velo1 =  1000*(errL/360)*64/errTime;
/*
		Serial.print("errL:");
		Serial.print(errL);
		Serial.print("   errTime:");
		Serial.print(errTime);
		Serial.print("  velo1:");
	             Serial.println(velo1);*/
            }
      
	//*********/
	spL1 = spL2;
	spR1 = spR2;
	lastT = nowT;
	//Serial.print(velo1);
}

void  MotorandAs5048::printInf(){


	float sumL=0;
	float sumR=0;
	velo1=velo2=0;
	int count = 0;
             for (int i = 0; i < 50; i++)
             {
             MotorandAs5048::convertoSpeed(0,velo1,velo2);
          
             Serial.print("  velo1:");
	Serial.println(velo1);
	Serial.print("  velo2:");
	Serial.println(velo2);   
             //delay(10);
             if(velo1<30&&velo2<30){
             sumL=sumL+velo1;    
             sumR=sumR+velo2;  
             count++;
             }
             }
               
                  Serial.print("count:");
	      Serial.println(count);
   	     Serial.print("sumL:");
	      Serial.println(sumL);
	      Serial.print("sumR:");
	      Serial.println(sumR);

                

             float vL = sumL/(count-1);
              sumL=0;
             float vR = sumR/(count-1);
             sumR=0;
             count=0;
             Serial.print("  vL:");
	Serial.println(vL);
	Serial.print("  vR:");
	Serial.println(vR);
             //delay(10);
           
             
           /*
	Serial.print("  velo1:");
	Serial.println(velo1);
	Serial.print("  velo2:");
	Serial.println(velo2);   */
}

