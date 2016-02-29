

#define lmbrkpin     4  //  D4 - left  motor brake        control    pin    HIGH = Brake 
#define lmdirpin     2  //  D2 - left  motor direction    control    pin    HIGH = Forward   Low = Reverse
#define lmpwmpin     3  //  D3 - left  motor pulse width  modulation pin    0 - 255          Speed and Brake 
#define lmcurpin     6  //  A6 - left  motor current      monitor    pin    0 - 1023         -20A to +20A   

#define rmbrkpin     9  //  D9 - right motor brake        control    pin    HIGH = Brake 
#define rmdirpin    10  // D10 - right motor direction    control    pin    HIGH = Forward   Low = Reverse
#define rmpwmpin    11  // D11 - right motor pulse width  modulation pin    0 - 255          Speed and Brake 
#define rmcurpin     7  //  A7 - right motor current      monitor    pin    0 - 1023         -20A to +20A   

void setup() {
  // put your setup code here, to run once:
  pinMode(lmpwmpin,OUTPUT); 
  pinMode(lmdirpin,OUTPUT);                            
  pinMode(lmbrkpin,OUTPUT);


  pinMode(rmpwmpin,OUTPUT);  
  pinMode(rmdirpin,OUTPUT);                            
  pinMode(rmbrkpin,OUTPUT);                          
}

void loop() {
                                                       
      digitalWrite(lmdirpin,1);                         // drive left  motor forward
      analogWrite(lmpwmpin,200);
      digitalWrite(rmdirpin,0);                         // drive right motor forward
      analogWrite(rmpwmpin,200);
      delayMicroseconds(500);                            // limit full power to 50uS

}
