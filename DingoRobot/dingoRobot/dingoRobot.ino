#include <MsTimer2.h>
#include <Wire.h>
#include <MotorandAs5048.h>
#include <PID_v1.h>

#define forward  0
#define backward  1
#define setValue 22

double sum,vel;

MotorandAs5048  m;

double Setpoint_R,Setpoint_L, Input_L, Output_L,Input_R, Output_R;
double Kp=0.5, Ki=6, Kd=0;
PID myPID_L(&Input_L, &Output_L, &Setpoint_L, Kp, Ki, Kd, DIRECT);
PID myPID_R(&Input_R, &Output_R, &Setpoint_R, Kp, Ki, Kd, DIRECT);

void setup(){
  
 Serial.begin(9600);
  m.motorInit();
  m.setZeroReg();
  myPID_L.SetMode(AUTOMATIC);
  myPID_R.SetMode(AUTOMATIC);
  //*****************
  Setpoint_R = setValue*9.21+12.6; //right
  Setpoint_L= setValue*7.03+40.55;//left
  /****************/
//Setpoint_R = 70;//right
 // Setpoint_L= 70;
}
void loop(){

  //*************
PIDCtrol();

 // ***********/
  
/*********************************
collectData();
 *******************************/
}
void PIDCtrol(){
  
   Input_L= filter(10,0);
   Input_R = filter(10,1);
  Serial.print("Setpoint_L: ");
  Serial.print(Setpoint_L);
   Serial.print("Setpoint_R: ");
  Serial.print(Setpoint_R);
   //Input = Input*10; 
   Input_R = 9.21*Input_R+12.65;
   Input_L = 7.03*Input_L+40.55;
  Serial.print("    Input_L:");
  Serial.print(Input_L);
  Serial.print("    Input_R:");
  Serial.print(Input_R);
  myPID_L.Compute();
  myPID_R.Compute();
  Serial.print("   Output_L");
  Serial.print(Output_L);
  Serial.print("   Output_R");
  Serial.println(Output_R);
  m.setSpeed(forward,forward,Output_L,Output_R);
  
}
void PIDCtrol2(){
  
   Input_L= filter(10,0);
   Input_R = filter(10,1);
 // Serial.println(Setpoint_L);
  Serial.println(Setpoint_R);
   //Input = Input*10; 
   Input_R = 9.21*Input_R+12.65;
   Input_L = 7.03*Input_L+40.55;
 // Serial.println(Input_L);
  Serial.println(Input_R);
  myPID_L.Compute();
  myPID_R.Compute();
 // Serial.println(Output_L);
  Serial.println(Output_R);
  m.setSpeed(forward,forward,Output_L,Output_R);
  
}

void collectData(){
  while(Setpoint_L<255){
          m.setSpeed(forward,forward,Setpoint_L,Setpoint_R);
          /*********************
          Serial.print("Setpoint_L: ");
          Serial.print(Setpoint_L);
          Serial.print("Setpoint_R: ");
          Serial.print(Setpoint_R);
          *********************/
           Input_L= filter(10,0);
           Input_R = filter(10,1);
    //    Serial.print("    Input_L:");
          Serial.println(Input_L);
    //      Serial.print("    Input_R:");
        Serial.println(Input_R);
          delay(5000);
          Setpoint_L=Setpoint_L+20;
          Setpoint_R=Setpoint_R+20;
          if(Setpoint_L>255||Setpoint_R>255)
              Setpoint_R= Setpoint_L=70;
  }
}


double filter(int n,int LR){
  sum=0;
  int i = 0;
  while(i<n){
      m.printInf();
      i+=1;
      if(LR ==0)
       {
      if(m.velo2<30&&m.velo2>0)
              sum  = m.velo2+sum;
      }
      else 
     {
     if(m.velo1<30&&m.velo1>0)
              sum  = m.velo1+sum;
     }
  }  
vel = sum/n;
sum=0;
return vel;
}


