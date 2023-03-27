//http://www.hexeguitar.com/diy/utility/fv1progsel
//        _______
//D4  1--|   C   |--16  VDD
//D5  2--|   M   |--15  EOUT
//D6  3--|   O   |--14  GS
//D7  4--|   S   |--13  D3
//EIN 5--|   4   |--12  D2
//Q2  6--|   5   |--11  D1
//Q1  7--|   3   |--10  D0
//GND 8--|___2___|--9   Q0

//Q0-2 are from this bad boy up here ^^^^
//S0-2 are the data input pins on the FV-1
                   
const int Q0 = 2;    
const int Q1 = 3;
const int Q2 = 4;
const int S0 = 5;
const int S1 = 6;
const int S2 = 7;


int Q0State;       // current state of Q0
int lastQ0State = LOW;     // previous state of Q0
int Q1State;         // current state of Q1
int lastQ1State = LOW;     // previous state of Q1
int Q2State;         // current state of Q2
int lastQ2State = LOW;     // previous state of Q2

int S0State;         // current state of S0
int S1State;         // current state of S1
int S2State;         // current state of S2

int setting;


void setup() {
  // initialize the input data pins from CMOS4532:
  pinMode(Q0, INPUT);
  pinMode(Q1, INPUT);
  pinMode(Q2, INPUT);
  // initialize the output data pins to the ATMEGA:
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
}

void loop(){
  
   if (Q0State != lastQ0State || Q1State != lastQ1State || Q1State != lastQ1State){
    
   void readQpins();
   void settingUpdate();
      }
}

void readQpins(){
  
Q0State = digitalRead(Q0);
Q1State = digitalRead(Q1);
Q2State = digitalRead(Q2);
  
if(
Q0State = LOW &&
Q1State = LOW &&
Q2State = LOW &&)
{setting = 0}


if(
Q0State = HIGH
Q1State = LOW
Q2State = LOW)
{setting = 1}
      
if(
Q0State = LOW
Q1State = HIGH
Q2State = LOW)
{setting = 2}
      
if(
Q0State = HIGH
Q1State = HIGH
Q2State = LOW)
{setting = 3}
      
if(Q0State = LOW
Q1State = LOW
Q2State = HIGH)
{setting = 4}
        
if(
Q0State = HIGH
Q1State = LOW
Q2State = HIGH)
{setting = 5}
         
if(
Q0State = LOW
Q1State = HIGH
Q2State = HIGH)
{setting = 6}

if(
Q0State = HIGH
Q1State = HIGH
Q2State = HIGH)
{setting = 7}

}



void settingUpdate(){
  
switch (setting);
case 0:
S0State = LOW;
S1State = LOW;
S2State = LOW;

case 1:
S0State = HIGH;
S1State = LOW;
S2State = LOW;

case 2:
S0State = LOW;
S1State = HIGH;
S2State = LOW;
  
case 3:
S0State = HIGH;
S1State = HIGH;
S2State = LOW;
  
case 4:
S0State = LOW;
S1State = LOW;
S2State = HIGH;

case 5:
S0State = HIGH;
S1State = LOW;
S2State = HIGH;

case 6:
S0State = LOW;
S1State = HIGH;
S2State = HIGH;

case 7:
S0State = HIGH;
S1State = HIGH;
S2State = HIGH;

digitalWrite(S0 = S0State);
digitalWrite(S1 = S1State);
digitalWrite(S2 = S2State);
}
