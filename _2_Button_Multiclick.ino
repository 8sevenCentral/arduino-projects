#define button1 2 
#define button2 3
#define led1 13   // this is actually led1 and relay 1
#define led2 8  
#define led3 9 
#define led4 12    // this is actually led2 and relay 2
#define led5 10
#define led6 11 



// LED variables
boolean ledVal1 = false;    // state of LED 1
boolean ledVal2 = false;    // state of LED 2
boolean ledVal3 = false;    // state of LED 3
boolean ledVal4 = false;    // state of LED 4
boolean ledVal5 = false;    // state of LED 5
boolean ledVal6 = false;    // state of LED 6


//=================================================

void setup() {
  
   // Setup button input pin 1
   pinMode(button1, INPUT);
   digitalWrite(button1, HIGH );

   // Setup button input pin 2
   pinMode(button2, INPUT);
   digitalWrite(button2, HIGH );

   
   // Setup LED output pins
   pinMode(led1, OUTPUT);
   digitalWrite(led1, ledVal1);
   pinMode(led2, OUTPUT);
   digitalWrite(led2, ledVal2);
   pinMode(led3, OUTPUT);
   digitalWrite(led3, ledVal3);
   pinMode(led4, OUTPUT);
   digitalWrite(led4, ledVal4);
   pinMode(led5, OUTPUT);
   digitalWrite(led5, ledVal5);
   pinMode(led6, OUTPUT);
   digitalWrite(led6, ledVal6);
  

}

void loop() {
  
   // Get button event and act accordingly
   int b1 = checkButton1();
   if (b1 == 1) clickEvent1();
   // double click was b2 == 2 but its kind of whack for our purposes
   if (b1 == 3) holdEvent1();
   if (b1 == 4) longHoldEvent1();

   int b2 = checkButton2();
   if (b2 == 1) clickEvent2();
   // double click was b2 == 2 but its kind of whack for our purposes
   if (b2 == 3) holdEvent2();
   if (b2 == 4) longHoldEvent2();
   
}

//=================================================
// Setup button 1 events

void clickEvent1() {
  
  ledVal1 = !ledVal1;
  digitalWrite(led1, ledVal1);
  
  if (ledVal1 == HIGH)
  {
    digitalWrite(led1, HIGH);
  }
  else
  {
    digitalWrite(led1, LOW);
  }
}

void holdEvent1() {
  
  ledVal2 = !ledVal2;
  digitalWrite(led2, ledVal2);

  if (ledVal2 == HIGH)
  {
 
  }
  else
  {

  }
}

void longHoldEvent1() {
  
  ledVal3 = !ledVal3;
  digitalWrite(led3, ledVal3);

  if (ledVal3 == HIGH)
  {
  }
  else
  {
  }
}


//=================================================
// Setup button 2 events

void clickEvent2() {
  
  ledVal4 = !ledVal4;
  digitalWrite(led4, ledVal4);
  
  if (ledVal4 == HIGH)
  {
    digitalWrite(led4, HIGH);
  }
  else
  {
    digitalWrite(led4, LOW);
    }
    
}

void holdEvent2() {
  
  ledVal5 = !ledVal5;
  digitalWrite(led5, ledVal5);

  if (ledVal5 == HIGH)
  {
  }
  else
  {
  }
}

void longHoldEvent2() {
  
  ledVal6 = !ledVal6;
  digitalWrite(led6, ledVal6);

  if (ledVal6 == HIGH)
  {
  }
  else
  {
  }
}


//=================================================
//  MULTI-CLICK:  One Button, Multiple Events

// Button timing variables
int debounce = 20;          // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 50;            // max ms between clicks for a double click event
int holdTime = 1000;        // ms hold period: how long to wait for press+hold event
int longHoldTime = 2500;    // ms long hold period: how long to wait for press+hold event

// Button1 variables
boolean buttonVal1 = HIGH;   // value read from button1
boolean buttonLast1 = HIGH;  // buffered value of the button's previous state
boolean DCwaiting1 = false;  // whether we're waiting for a double click (down)
boolean DConUp1 = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK1 = true;    // whether it's OK to do a single click
long downTime1 = -1;         // time the button was pressed down
long upTime1 = -1;           // time the button was released
boolean ignoreUp1 = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp1 = false;        // when held, whether to wait for the up event
boolean holdEventPast1 = false;    // whether or not the hold event happened already
boolean longHoldEventPast1 = false;// whether or not the long hold event happened already

// Button2 variables
boolean buttonVal2 = HIGH;   // value read from button1
boolean buttonLast2 = HIGH;  // buffered value of the button's previous state
boolean DCwaiting2 = false;  // whether we're waiting for a double click (down)
boolean DConUp2 = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK2 = true;    // whether it's OK to do a single click
long downTime2 = -1;         // time the button was pressed down
long upTime2 = -1;           // time the button was released
boolean ignoreUp2 = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp2 = false;        // when held, whether to wait for the up event
boolean holdEventPast2 = false;    // whether or not the hold event happened already
boolean longHoldEventPast2 = false;// whether or not the long hold event happened already

//=================================================
// Button1 Routine
int checkButton1() {    
   int event1 = 0;
   buttonVal1 = digitalRead(button1);
   // Button pressed down
   if (buttonVal1 == LOW && buttonLast1 == HIGH && (millis() - upTime1) > debounce)
   {
       downTime1 = millis();
       ignoreUp1 = false;
       waitForUp1 = false;
       singleOK1 = true;
       holdEventPast1 = false;
       longHoldEventPast1 = false;
       if ((millis()-upTime1) < DCgap && DConUp1 == false && DCwaiting1 == true)  DConUp1 = true;
       else  DConUp1 = false;
       DCwaiting1 = false;
   }
   // Button released
   else if (buttonVal1 == HIGH && buttonLast1 == LOW && (millis() - downTime1) > debounce)
   {        
       if (not ignoreUp1)
       {
           upTime1 = millis();
           if (DConUp1 == false) DCwaiting1 = true;
           else
           {
               event1 = 2;
               DConUp1 = false;
               DCwaiting1 = false;
               singleOK1 = false;
           }
       }
   }
   // Test for normal click event: DCgap expired
   if ( buttonVal1 == HIGH && (millis()-upTime1) >= DCgap && DCwaiting1 == true && DConUp1 == false && singleOK1 == true && event1 != 2)
   {
       event1 = 1;
       DCwaiting1 = false;
   }
   // Test for hold
   if (buttonVal1 == LOW && (millis() - downTime1) >= holdTime) {
       // Trigger "normal" hold
       if (not holdEventPast1)
       {
           event1 = 3;
           waitForUp1 = true;
           ignoreUp1 = true;
           DConUp1 = false;
           DCwaiting1 = false;
           //downTime = millis();
           holdEventPast1 = true;
       }
       // Trigger "long" hold
       if ((millis() - downTime1) >= longHoldTime)
       {
           if (not longHoldEventPast1)
           {
               event1 = 4;
               longHoldEventPast1 = true;
           }
           
       }
   }
   buttonLast1 = buttonVal1;
   return event1;
}

//=================================================
// Button2 Routine
int checkButton2() {    
   int event2 = 0;
   buttonVal2 = digitalRead(button2);
   // Button pressed down
   if (buttonVal2 == LOW && buttonLast2 == HIGH && (millis() - upTime2) > debounce)
   {
       downTime2 = millis();
       ignoreUp2 = false;
       waitForUp2 = false;
       singleOK2 = true;
       holdEventPast2 = false;
       longHoldEventPast2 = false;
       if ((millis()-upTime2) < DCgap && DConUp2 == false && DCwaiting2 == true)  DConUp2 = true;
       else  DConUp2 = false;
       DCwaiting2 = false;
   }
   // Button released
   else if (buttonVal2 == HIGH && buttonLast2 == LOW && (millis() - downTime2) > debounce)
   {        
       if (not ignoreUp2)
       {
           upTime2 = millis();
           if (DConUp2 == false) DCwaiting2 = true;
           else
           {
               event2 = 2;
               DConUp2 = false;
               DCwaiting2 = false;
               singleOK2 = false;
           }
       }
   }
   // Test for normal click event: DCgap expired
   if ( buttonVal2 == HIGH && (millis()-upTime2) >= DCgap && DCwaiting2 == true && DConUp2 == false && singleOK2 == true && event2 != 2)
   {
       event2 = 1;
       DCwaiting2 = false;
   }
   // Test for hold
   if (buttonVal2 == LOW && (millis() - downTime2) >= holdTime) {
       // Trigger "normal" hold
       if (not holdEventPast2)
       {
           event2 = 3;
           waitForUp2 = true;
           ignoreUp2 = true;
           DConUp2 = false;
           DCwaiting2 = false;
           //downTime = millis();
           holdEventPast2 = true;
       }
       // Trigger "long" hold
       if ((millis() - downTime2) >= longHoldTime)
       {
           if (not longHoldEventPast2)
           {
               event2 = 4;
               longHoldEventPast2 = true;
           }
       }
   }
   buttonLast2 = buttonVal2;
   return event2;
}

