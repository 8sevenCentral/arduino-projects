// controls relay bypass switching firmware and clock signal for the FV-1

const int button = 1;
const int relayPos = 3;
const int LED = 0;
const int pulseLength = 200;

void setup (){
  
 pinMode(button, INPUT);
 pinMode(relayPos, OUTPUT);
 pinMode(LED, OUTPUT);
 
}

void loop (){

  if(digitalRead(button)==HIGH){
  digitalWrite(relayPos, HIGH);
  digitalWrite(LED, HIGH);
  boolean clickStatus = true;
 
  }
  
  if(digitalRead(button)==LOW){
  digitalWrite(LED, LOW);
  
  }
  
  if(digitalRead(button)==LOW){
  digitalWrite(relayNeg, HIGH);
  delay(pulseLength);
  digitalWrite(relayNeg, LOW);
  
  }
}

