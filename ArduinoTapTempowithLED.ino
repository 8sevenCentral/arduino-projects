

// include the ArduinoTapTempo library
#include <ArduinoTapTempo.h>
#include <SoftwareSerial.h>

// define the pin you want to attach your tap button to
const int BUTTON_PIN = 5;
const int LED_PIN = 13;

int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

// make an ArduinoTapTempo object
ArduinoTapTempo tapTempo;


void setup() {
  // begin serial so we can see the state of the tempo object through the serial monitor
  Serial.begin(9600);

  // setup your button as required by your project
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  void enableSkippedTapDetection();
  
  // get the state of the button
  boolean buttonDown = digitalRead(BUTTON_PIN) == LOW;
  
  // update ArduinoTapTempo
  tapTempo.update(buttonDown);

  Serial.print("bpm: ");
  Serial.println(tapTempo.getBPM());

  long LED_BPM = map(tapTempo.getBPM(), 20, 240, 240, 20);

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= LED_BPM) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_PIN, ledState);
  }
  

  // uncomment the block below to demo many of ArduinoTapTempo's methods
  // note that Serial.print() is not a fast operation, and using it decreases the accuracy of the the tap timing
  
  /*
  Serial.print("len:");
  Serial.print(tapTempo.getBeatLength());
  Serial.print(",\tbpm: ");
  Serial.print(tapTempo.getBPM());
  Serial.print(",\tchain active: ");
  Serial.print(tapTempo.isChainActive() ? "yes" : "no ");
  Serial.print(",\tlasttap: ");
  Serial.print(tapTempo.getLastTapTime());
  Serial.print(",\tprogress: ");
  Serial.print(tapTempo.beatProgress());
  Serial.print(",\tbeat: ");
  Serial.println(tapTempo.onBeat() ? "beat" : "    ");
  */
}
