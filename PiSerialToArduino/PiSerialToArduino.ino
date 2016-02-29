/**
creat by Dash 
2016-02-29
the code is used for arduino UNO to communicate with pi 
**/
#define  LED 13
//byte number = 0;
void setup(){
   pinMode(LED, OUTPUT);    
    Serial.begin(9600);
}
void loop(){
   if (Serial.available())  {
       int com = Serial.read();
       if(com==49){
         digitalWrite(LED,HIGH);
         Serial.println("LED  TURN ON ");
       }else if(com==48){
        digitalWrite(LED,LOW);
         Serial.println("LED  TURN OFF ");
       }
   }
}

