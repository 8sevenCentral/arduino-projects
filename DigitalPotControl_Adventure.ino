/*
  Digital Pot Control
  
  This example controls an Analog Devices AD5206 digital potentiometer.
  The AD5206 has 6 potentiometer channels. Each channel's pins are labeled
  A - connect this to voltage
  W - this is the pot's wiper, which changes when you set it
  B - connect this to ground.
 
 The AD5206 is SPI-compatible,and to command it, you send two bytes, 
 one with the channel number (0 - 5) and one with the resistance value for the
 channel (0 - 255).  
 
 The circuit:
  * All A pins  of AD5206 connected to +5V
  * All B pins of AD5206 connected to ground
  * An LED and a 220-ohm resisor in series connected from each W pin to ground
  * CS - to digital pin 10  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)
 
 created 10 Aug 2010 
 by Tom Igoe
 
 Thanks to Heather Dewey-Hagborg for the original tutorial, 2005
 
*/


// inslude the SPI library:
#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
const int channel = 0;

int analogInPin = A0;    // select the input pin for the potentiometer
int analogOutPin = 9;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int outputValue = 0;
int fadeValue = 0;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  pinMode(analogOutPin, OUTPUT);  
  // initialize SPI:
  SPI.begin(); 
}

void loop() {
  
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 1, 50);  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);   
  
 // digitalPotWrite(channel, outputValue);

  delay(2);  
  
    // fade in from min to max in increments of 5 points:
  for(int fadeValue = 30 ; fadeValue < 200; fadeValue++) { 
    // sets the value (range from 0 to 255):
    analogWrite(analogOutPin, fadeValue);  
    digitalPotWrite(channel, fadeValue);      
    // wait for 30 milliseconds to see the dimming effect    
    delay(outputValue);     

    
  }
  
  for(int fadeValue = 200 ; fadeValue > 30; fadeValue--) { 
    // sets the value (range from 0 to 255):
    analogWrite(analogOutPin, fadeValue);  
    digitalPotWrite(channel, fadeValue);      
    // wait for 30 milliseconds to see the dimming effect    
    delay(outputValue);     

 
  
  }
 




}

void digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin,LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin,HIGH); 
}
