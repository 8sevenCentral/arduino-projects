/*
 
 Originally written as " 4-Way Button:  Click, Double-Click, Press+Hold, and Press+Long-Hold Test Sketch" By Jeff Saltzman
 Oct. 13, 2009
 
 Modified by Christian Terjesen to use with a shift register
 January, 2015
 
 To keep a physical interface as simple as possible, this sketch demonstrates generating four output events from a single push-button.
 1) Click:  rapid press and release
 2) Double-Click:  two clicks in quick succession
 3) Press and Hold:  holding the button down
 4) Long Press and Hold:  holding the button for a long time 
 */

#define buttonPin 1      // analog input pin to use as a digital input
#define Pin1 13          // digital output pin 1
#define Pin2 2           // digital output pin 2
#define Pin3 5           // digital output pin 3
#define Pin4 6           // digital output pin 4
#define relayPin1 3      // digital output pin for relaypin1
#define relayPin2 4      // digital output pin for relaypin2

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

boolean clickStatus = false;
boolean dClickStatus = false;
boolean shortHoldStatus = false;
boolean longHoldStatus = false;

/*====================================================*/

boolean Val1 = false;    // state of single click loop
boolean Val2 = false;    // state of double click loop
boolean Val3 = false;    // state of short hold loop
boolean Val4 = false;    // state of long hold loop

boolean latch = LOW;
boolean dClick = LOW;
boolean shortHold = LOW;
boolean longHold = LOW;

/*====================================================*/

byte patternA = B00000000;
byte patternB = B00000001;
byte patternC = B00001110;
byte patternD = B00001111;
byte patternE = B10000000;
byte patternF = B10000001;
byte patternG = B10001111;
byte patternH = B10001110;

/*====================================================*/

byte patternA[1] = { 
  patternA, 100,
byte patternB[1] = { 
  patternB, 100,
byte patternC[1] = {  
  patternC, 100,
byte patternD[1] = {  
  patternD, 100,
byte patternE[1] = {   
  patternE, 100, 
byte patternF[1] = {  
  patternF, 100,
byte patternG[1] = { 
  patternG, 100,
byte patternH[1] = {  
  patternH, 100, 
};

/*=================================================*/

void setup() {
  // Set button input pin
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH );
  // Set LED output pins
  pinMode(Pin1, OUTPUT);
  digitalWrite(Pin1, Val1);
  pinMode(Pin2, OUTPUT);
  digitalWrite(Pin2, Val2);
  pinMode(Pin3, OUTPUT);    
  digitalWrite(Pin3, Val3);
  pinMode(Pin4, OUTPUT);    
  digitalWrite(Pin4, Val4);

  pinMode(relayPin1, OUTPUT);    
  digitalWrite(relayPin1, LOW);
  pinMode(relayPin2, OUTPUT);    
  digitalWrite(relayPin2, LOW);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  
}

/*=================================================*/

void loop() {
  // Get button event and act accordingly
  int b = checkButton();
  if (b == 1) clickEvent();
  if (b == 2) doubleClickEvent();
  if (b == 3) holdEvent();
  if (b == 4) longHoldEvent();
  
  
  /*
  switch (index) {
    case 1:
      
      break;
    case 2:
      //do something when var equals 2
      break;
    case 3:
      //do something when var equals 1
      break;
    case 4:
      //do something when var equals 2
      break;
    case 5:
      //do something when var equals 1
      break;
    case 6:
      //do something when var equals 2
      break;
    case 7:
      //do something when var equals 1
      break;
    default: 
      // if nothing else matches, do the default
      // default is optional
  }
*/

  byte data = B00000000;
  
  int b = checkButton();  // Get button event and act accordingly
  
  switch (b)
  {
    case 1:
      data = clickEvent();
      break;
    case 2:
      data = doubleClickEvent();
      break;
    case 3:
      data = holdEvent();
      break;
    case 4:
      data = longHoldEvent();
      break;
    default: 
      // if nothing else matches, do the default
      // default is optional
  }
  
  if (data)
  {
	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, MSBFIRST, data);
	digitalWrite(latchPin, HIGH);
  }
}

/*=================================================*/
// Events to trigger

void clickEvent() {
  Val1 = !Val1;

  if (latch) {  // set relay
    digitalWrite (Pin1, Val1);
    digitalWrite (relayPin1, HIGH);
    delay(15);
    digitalWrite (relayPin1, LOW);
  } 
  else {  // reset relay
    digitalWrite (Pin1, Val1);
    digitalWrite (relayPin2, HIGH);
    delay(15);
    digitalWrite (relayPin2, LOW);
  }
  latch = !latch;
  
  clickStatus = !clickStatus;
  return patternA;
  
/*=================================================*/  

}
void doubleClickEvent() {
  Val2 = !Val2;
  
  {
  if (clickStatus)
  {
	  return patternA;
  }
  else if (dClickStatus)
  {
	  return patternA;
  }
  else
  {
	  return patternB;
  }
  
  /*
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, patterns[index * 2]);
  digitalWrite(latchPin, HIGH);
  delay(patterns[(index * 2) + 1]);
  index++;
  if (index >= count){
    index = 0;
  }
  
  */
 

/*=================================================*/

}
void holdEvent() {
  Val3 = !Val3;
  
    if (clickStatus)
  {
	  return patternA;
  }
  else if (dClickStatus)
  {
	  return patternA;
  }
  else
  {
	  return patternB;
  }
}
  
/*
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, patterns[index * 2]);
  digitalWrite(latchPin, HIGH);
  delay(patterns[(index * 2) + 1]);
  index++;
  if (index >= count){
    index = 0;
    */
 
/*=================================================*/

}
void longHoldEvent() {
  Val4 = !Val4;
  
    if (clickStatus)
  {
	  return patternA;
  }
  else if (dClickStatus)
  {
	  return patternA;
  }
  else
  {
	  return patternB;
  }
  
  
  /*
   digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, patterns[index * 2]);
  digitalWrite(latchPin, HIGH);
  delay(patterns[(index * 2) + 1]);
  index++;
  if (index >= count){
    index = 0;
  }
*/

}

//=================================================
//  MULTI-CLICK:  One Button, Multiple Events

// Button timing variables
int debounce = 20;          // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 150;            // max ms between clicks for a double click event
int holdTime = 1000;        // ms hold period: how long to wait for press+hold event
int longHoldTime = 2500;    // ms long hold period: how long to wait for press+hold event

/*=================================================*/

// Button variables
boolean buttonVal = HIGH;   // value read from button
boolean buttonLast = HIGH;  // buffered value of the button's previous state
boolean DCwaiting = false;  // whether we're waiting for a double click (down)
boolean DConUp = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK = true;    // whether it's OK to do a single click
long downTime = -1;         // time the button was pressed down
long upTime = -1;           // time the button was released
boolean ignoreUp = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp = false;        // when held, whether to wait for the up event
boolean holdEventPast = false;    // whether or not the hold event happened already
boolean longHoldEventPast = false;// whether or not the long hold event happened already

/*=================================================*/

int checkButton() {    
  int event = 0;
  buttonVal = digitalRead(buttonPin);
  // Button pressed down
  if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > debounce)
  {
    downTime = millis();
    ignoreUp = false;
    waitForUp = false;
    singleOK = true;
    holdEventPast = false;
    longHoldEventPast = false;
    if ((millis()-upTime) < DCgap && DConUp == false && DCwaiting == true)  DConUp = true;
    else  DConUp = false;
    DCwaiting = false;
  }
  // Button released
  else if (buttonVal == HIGH && buttonLast == LOW && (millis() - downTime) > debounce)
  {        
    if (not ignoreUp)
    {
      upTime = millis();
      if (DConUp == false) DCwaiting = true;
      else
      {
        event = 2;
        DConUp = false;
        DCwaiting = false;
        singleOK = false;
      }
    }
  }
  // Test for normal click event: DCgap expired
  if ( buttonVal == HIGH && (millis()-upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true && event != 2)
  {
    event = 1;
    DCwaiting = false;
  }
  // Test for hold
  if (buttonVal == LOW && (millis() - downTime) >= holdTime) {
    // Trigger "normal" hold
    if (not holdEventPast)
    {
      event = 3;
      waitForUp = true;
      ignoreUp = true;
      DConUp = false;
      DCwaiting = false;
      //downTime = millis();
      holdEventPast = true;
    }
    // Trigger "long" hold
    if ((millis() - downTime) >= longHoldTime)
    {
      if (not longHoldEventPast)
      {
        event = 4;
        longHoldEventPast = true;
      }
    }
  }
  buttonLast = buttonVal;
  return event;
}



