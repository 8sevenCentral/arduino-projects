int potpin = A0;
int val;
int LDR = A1;       // select the input pin for the LDR
int ledPin = 13;   // select the pin for the LED
int val2 = 0;       // variable to store the value coming from the sensor

void setup() {
  pinMode(LDR, INPUT);       // declare the LDR as an INPUT
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
}

void loop() {
val = analogRead(potpin);
val = map(val, 0, 1023, 0, 179);
analogWrite(3,val);
delay(15);
analogWrite(5,val);
delay(15);

val2 = analogRead(LDR);       // read the value from the sensor
digitalWrite(ledPin, HIGH);  // turn the ledPin on
delay(val2);                  // stop the program for some time
digitalWrite(ledPin, LOW);   // turn the ledPin off
delay(val2); 
}
