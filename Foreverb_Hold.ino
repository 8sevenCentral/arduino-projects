/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
 
const int ledPin =  9;      // the number of the LED pin
const int scopePin =  13;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status
int sensorValue = 0;  // variable to store the value coming from the sensor
int outputValue = 0;
int rampValue = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  pinMode(scopePin, OUTPUT); 
  
 
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  // print out the value you read:
  Serial.println(sensorValue);
  outputValue = map(sensorValue, 0, 1023, 1, 50);  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue); 
  delay(2);
  
  for(int rampValue = 30 ; rampValue < 200; rampValue++) { 
    // sets the value (range from 0 to 255):
    analogWrite(analogOutPin, rampValue);  
    digitalPotWrite(channel, rampValue);      
      delay(500);
  for(int rampValue = 30 ; rampValue < 200; rampValue++) { 
    // sets the value (range from 0 to 255):
    analogWrite(analogOutPin, rampValue);  
    digitalPotWrite(channel, rampValue);          
    
  }
  
 // else {
    // turn LED off:
   // digitalWrite(ledPin, LOW); 
  //  digitalWrite(scopePin, LOW);
 // }
}
