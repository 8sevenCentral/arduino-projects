

void setup() {
   pinMode (10, OUTPUT);                                       //Square Out
   pinMode (11, INPUT);                                        //potentiometer
    
   Serial.begin(9600);                                       //  setup serial for potentiometer
  
}

void loop() { 
   
    int sensorValue = analogRead(A0);        //read potentiometer value on pin A0
    
    sensorValue = map(sensorValue, 0, 1023, 20, 2);         //scale sensorValue
    Serial.println(sensorValue);                            //print sensorValue
    unsigned int freq1 = 10000;                              //should range between 25kHz and 50kHz
    unsigned int delayMicro = sensorValue*10; 
    
    
   
   int x = 50;                         //addition scaler for frequency  


/* SINE WAVE */
   

   for (int i = 0; i <= 1023; i = i++)                      //sweep up
   {  
      freq1 = freq1 + x;                                    //increase frequency and add 
      tone(10, freq1);                                      //generate square wave out of pin 10
      int randNumber = random(2,20);
     delay(randNumber);
   }
  
  delayMicroseconds(sensorValue);
   
    for (int i = 0; i <= 1023; i = i++)                     //sweep down
    {
      freq1 = freq1 - x;                                    //increase frequency and add x
      tone(10, freq1);                                    //generate square wave out of pin 10
      int randNumber = random(2,20);
     delay(randNumber);
   }  
   
  delayMicroseconds(sensorValue);
  

  
  /* SQUARE WAVE */

     for (int i = 0; i <= 1023; i = i++)                      //sweep up
   {  
      int randNumber = random(2,20);
      freq1 = 40000 + (10*randNumber);                                    //increase frequency and add 
      tone(10, freq1);                                      //generate square wave out of pin 10
      delay(randNumber);
   }
  
  delayMicroseconds(sensorValue);
   
    for (int i = 0; i <= 1023; i = i++)                     //sweep down
    {
      int randNumber = random(2,20);
      freq1 = 10000 + (10*randNumber);                                    //increase frequency and add x
      tone(10, freq1);                                    //generate square wave out of pin 10
      delay(randNumber);
   }  
   
  delayMicroseconds(sensorValue);
  
}
