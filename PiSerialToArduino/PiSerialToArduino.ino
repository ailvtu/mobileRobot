/**
creat by Dash 
2016-02-29
the code is used for arduino UNO to communicate with pi 
**/
#include<stdlib.h>
#define  LED 13
//byte number = 0;
void setup(){
   pinMode(LED, OUTPUT);    
    Serial.begin(9600);
}
void loop(){
  /*
   if (Serial.available())  {
       int com = Serial.read();
       if(com==49){
         digitalWrite(LED,HIGH);
    
         Serial.println(49);
       }else if(com==48){
        digitalWrite(LED,LOW);
        Serial.println(48);
       }
   }*/
   int A = random(30);
    Serial.print(A);
    delay(10);
}

