#include "wavetable.h";

WaveTable wt;

const int LEDfade =  9;      // the number of the LED pin
const int pot = A0;


// Variables will change:
long previousMillis = 0;        // will store last time LED was updated
int wavStep = 0;
int dir = 1;                    // direction - 1 = UP, 0 = DOWN
int potVal = 0;
int freq = 0;
int MIN = 0;
int MAX = 255;
int i = 0;

const byte sinA [] = 
{0, 4, 8, 13, 17, 22, 26, 31, 35, 39, 44, 48, 53, 57, 61, 65, 
70, 74, 78, 83, 87, 91, 95, 99, 103, 107, 111, 115, 119, 123, 
127, 131, 135, 138, 142, 146, 149, 153, 156, 160, 163, 167, 
170, 173, 177, 180, 183, 186, 189, 192, 195, 198, 200, 203, 
206, 208, 211, 213, 216, 218, 220, 223, 225, 227, 229, 231, 
232, 234, 236, 238, 239, 241, 242, 243, 245, 246, 247, 248, 
249, 250, 251, 251, 252, 253, 253, 254, 254, 254, 254, 254, 255};



// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 10;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(LEDfade, OUTPUT);
  pinMode(pot, INPUT);
  Serial.begin(9600); //For debugging
}

void loop() {
  potVal = analogRead(pot);
  freq = map(potVal, 0, 1023, 1, 255);
  unsigned long currentMillis = micros()/1000;

  if(currentMillis - previousMillis > interval && dir == 1) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    i = i + freq;
    if(i >= MAX) {
       i = MAX;
       dir = 0;
    }
    sendValues(i);
  }
  
  if(currentMillis - previousMillis > interval && dir == 0) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    i = i - freq;
    if(i <= MIN) {
       i = MIN;
       dir = 1;
    }
    sendValues(i);
  }
}

void sendValues(int v){
  
  Serial.print("step: ");
  Serial.print(v);
  Serial.print("\tvalue: ");

  int v2 = map(v, 0, 255, 0, sizeof(sinA));
  Serial.println(sinA[v2]);
  
  analogWrite(LEDfade, v); // set the LED brightness   
}

/*void orig(){
  potVal = analogRead(pot);
  freq = map(potVal, 0, 1023, 1, 255);

  unsigned long currentMillis = micros()/1000;
  
  if(currentMillis - previousMillis > interval && dir == 1) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    i = i + freq;
      if(i >= MAX) {
         i = MAX;
         dir = 0;
         }
    analogWrite(LEDfade, i); // set the LED brightness           
    }
  
  if(currentMillis - previousMillis > interval && dir == 0) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    i = i - freq;
      if(i <= MIN) {
         i = MIN;
         dir = 1;
      }
    analogWrite(LEDfade, i); // set the LED brightness           
    }

 Serial.println(i);
}*/

