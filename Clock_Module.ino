
int lastSensorValue = 0;
unsigned int counter1 = 0;
unsigned int counter2 = 0;
unsigned int counter3 = 0;
unsigned int counter4 = 0;
unsigned int counter5 = 0;
unsigned int counter6 = 0;
unsigned int counter7 = 0;
unsigned int counter8 = 0;
unsigned int counter9 = 0;
unsigned int counterTime = 0;


void setup() {
  
  Serial.begin(9600);
  
  pinMode(2, OUTPUT);      // master clock out
  pinMode(3, OUTPUT);      // clock out / 2
  pinMode(4, OUTPUT);      // clock out / 3
  pinMode(5, OUTPUT);      // clock out / 4
  pinMode(6, OUTPUT);      // clock out / 5
  pinMode(7, OUTPUT);      // clock out / 6
  pinMode(8, OUTPUT);      // clock out / 7
  pinMode(9, OUTPUT);      // clock out / 8
  pinMode(10, OUTPUT);      // clock out / 9
  pinMode(A0, INPUT);      // CV read
  
}

void loop() 
{
  
  float sensorValue = analogRead(A0);                 // read the input on analog pin 0:
  unsigned int  voltage = sensorValue * (5.0 / 1023.0);     // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  //Serial.println(voltage);                          // print out the value you read:    
  
  float potVal = map(sensorValue, 0, 1023, 1, 1100);     // Scale voltage from 0-5V to 1-1200 mS  
  //Serial.println(currentmS); 
  
  if(sensorValue == lastSensorValue){
     
        stepUP(); 
  } 
  else{
        calibrate();
        stepUP();
  }
  
        
  if(sensorValue == lastSensorValue){

        delay(sensorValue);
  }
  else{
        calibrate();
        delay(sensorValue);
  
  }
  
  if(sensorValue == lastSensorValue){

        stepDOWN();  
  }
  else{
        calibrate();
        stepDOWN();
  
  }
  
    if(sensorValue == lastSensorValue){

        delay(sensorValue);
    }
  else{
        calibrate();
        delay(sensorValue);
  
  }

}  

int calibrate(){
  
  float sensorValue = analogRead(A0);                 // read the input on analog pin 0:
  unsigned int  voltage = sensorValue * (5.0 / 1023.0);     // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  //Serial.println(voltage);                          // print out the value you read:    
  
  float potVal = map(sensorValue, 0, 1023, 1, 1100);     // Scale voltage from 0-5V to 1-1200 mS  
  //Serial.println(currentmS);      // print out the value you read: 
  
 lastSensorValue = sensorValue; 
  
  

lastSensorValue = sensorValue;   
  
}
  

void stepUP(){
  
  digitalWrite(2, HIGH);
  
  
    if (counter1 == 1){
    digitalWrite(3, HIGH);
    counter1 = counter1 - 2;    
    }
  counter1 = counter1 + 1; 
  
      if (counter2 == 2){
    digitalWrite(4, HIGH);
    counter2 = counter2 - 3;    
    }
  counter2 = counter2 + 1; 
  
        if (counter3 == 3){
    digitalWrite(5, HIGH);
    counter3 = counter3 - 4;    
    }
  counter3 = counter3 + 1; 
  
          if (counter4 == 4){
    digitalWrite(6, HIGH);
    counter4 = counter4 - 5;    
    }
  counter4 = counter4 + 1; 
  
            if (counter5 == 5){
    digitalWrite(7, HIGH);
    counter5 = counter5 - 6;    
    }
  counter5 = counter5 + 1; 
  
            if (counter6 == 6){
    digitalWrite(8, HIGH);
    counter6 = counter6 - 7;    
    }
  counter6 = counter6 + 1; 
  
              if (counter7 == 7){
    digitalWrite(9, HIGH);
    counter7 = counter7 - 8;    
    }
  counter7 = counter7 + 1; 
  
                if (counter8 == 8){
    digitalWrite(10, HIGH);
    counter8 = counter8 - 9;    
    }
  counter8 = counter8 + 1; 
  
  
  
}

void stepDOWN(){
  
        digitalWrite(2, LOW);
        
    if(3 == HIGH){
       digitalWrite(3, LOW);
    }
    else{
       digitalWrite(3, LOW);  
    }  
    
     if(4 == HIGH){
       digitalWrite(4, LOW);
    }
    else{
       digitalWrite(4, LOW);  
    }  
    
         if(5 == HIGH){
       digitalWrite(5, LOW);
    }
    else{
       digitalWrite(5, LOW);  
    }  
    
             if(6 == HIGH){
       digitalWrite(6, LOW);
    }
    else{
       digitalWrite(6, LOW);  
    }  
    
                 if(7 == HIGH){
       digitalWrite(7, LOW);
    }
    else{
       digitalWrite(7, LOW);  
    }  
                     if(8 == HIGH){
       digitalWrite(8, LOW);
    }
    else{
       digitalWrite(8, LOW);  
    }  
                         if(9 == HIGH){
       digitalWrite(9, LOW);
    }
    else{
       digitalWrite(9, LOW);  
    }  
                         if(10 == HIGH){
       digitalWrite(10, LOW);
    }
    else{
       digitalWrite(10, LOW);  
    }  
    
    
    
    
     
}

 
