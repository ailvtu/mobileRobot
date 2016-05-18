/******************
creat by Dash
2016-03-03


-******************/
#if ARDUINO >= 100
    #include <Arduino.h>
#else
   #include <WProgram.h>
  #endif



#ifndef MotorandAs5048_H_
#define MotorandAs5048_H_

#define LeftMotorBrake    4  //  D4 - left  motor brake        control    pin    HIGH = Brake 
#define LeftMotorDire     2  //  D2 - left  motor direction    control    pin    HIGH = Forward   Low = Reverse
#define LeftMotorSpeed     3  //  D3 - left  motor pulse width  modulation pin    0 - 255          Speed and Brake 


#define RightMotorBrake   9  //  D9 - right motor brake        control    pin    HIGH = Brake 
#define RightMotorDir    10  // D10 - right motor direction    control    pin    HIGH = Forward   Low = Reverse
#define RightMotorSpeed    11  // D11 - right motor pulse width  modulation pin    0 - 255          Speed and Brake 


#define as5048b_Address_L 0x40  // left motor 0x40,
#define as5048b_Address_R 0x41  //right motor 0x41

#define AS5048B_ZEROMSB_REG 0x16 //bits 0..7
#define AS5048B_ZEROLSB_REG 0x17 //bits 0..5

#define request_num 2         // request 2 byte 
#define angleRegAdd 0xFE
#define RESOLUTION 16383.0    ////14 bits
//#define circle   64  //circle 64cm

#define forward  0
#define backward  1


class MotorandAs5048
{
public:
  MotorandAs5048();
  ~MotorandAs5048();
  void motorInit();
  void Brake(int side); 
           
       void setZeroReg(void);
       void zeroRegW(uint16_t regVal1,uint16_t regVal2);
       void writeZero(uint8_t address, uint8_t value,uint8_t As5048Address) ;

       void writeReg(uint8_t address,uint8_t As5048Address);
       uint16_t readValue(int as5048b_Address);
       double getPoint(int side);
       void  convertoSpeed(int direction,double &velo1,double &velo2);
       double  getSpeed(int side);
       void  printInf();
       
       void setSpeed(int dirL,int dirR,int pwmL,int pwmR);
      void checkSpeed();

      float vL,vR;

private:
         uint16_t receiveValue_L ;
              uint16_t receiveValue_R ;
              double  speed ;
              double spL1,spL2,spR1,spR2;
             unsigned long lastT,nowT;
              double velo1,velo2;
};

#endif