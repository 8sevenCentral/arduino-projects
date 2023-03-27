/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 
 */
 
int led1 = 11;
int led2 = 10;
int led3 = 9;
int led4 = 6;
int brightness = 0;    // how bright the LED is
int brightness2 = 61.4;
int brightness3 = 55.6;
int brightness4 = 7;
int fadeAmount = 5; // how many points to fade the LED by
int fadeAmount2 = 5;
int fadeAmount3 = 5;
int fadeAmount4 = 5;



void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
} 

void loop()  { 
  // set the brightness of pin 9:
  analogWrite(led1, brightness);
  analogWrite(led2, brightness2);   
  analogWrite(led3, brightness3);   
  analogWrite(led4, brightness4);  
   

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;
    brightness2 = brightness2 + fadeAmount2;
      brightness3 = brightness3 + fadeAmount3;
        brightness4 = brightness4 + fadeAmount4;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) 
    fadeAmount = -fadeAmount ; 
  if (brightness2 == 0 || brightness2 == 255) 
    fadeAmount2 = -fadeAmount2 ; 
  if (brightness3 == 0 || brightness3 == 255) 
    fadeAmount3 = -fadeAmount3 ; 
  if (brightness4 == 0 || brightness4 == 255) 
    fadeAmount4 = -fadeAmount4 ; 
    
  if (fadeAmount4 == 0 || fadeAmount3 == 255) 
    fadeAmount4 = -fadeAmount3 ; 
  

    { 
  }    
 
  // wait for 30 milliseconds to see the dimming effect    
  delay(10); 
  
 }  

