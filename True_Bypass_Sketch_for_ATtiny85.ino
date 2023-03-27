const int button = 5;
const int shunter = 2;
const int relayPos = 13;
const int relayNeg = 4;

const int LED = 0;
const int pulseLength = 200;

void setup (){
  
 pinMode(button, INPUT);
 
 pinMode(relayPos, OUTPUT);
 pinMode(relayNeg, OUTPUT); 
 pinMode(LED, OUTPUT);
 pinMode(shunter, OUTPUT);
 
}

void loop (){
  
  
  if(digitalRead(button)==HIGH){
  digitalWrite(LED, HIGH);
  
  }
  
  if(digitalRead(button)==LOW){
  digitalWrite(LED, LOW);
  }
  
}

