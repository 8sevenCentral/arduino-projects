// This is the firmware for the Adventure Audio Calculator Expression Pedal


// inslude the SPI library:
#include <SPI.h>


void setup() {
  
//
//      ANALOG PIN VOLTAGE READ SET UP
//
//

// initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

//
//       DIGITAL POTENTIOMETER SETUP
//
//

// set pin 10 as the slave select for the digital pot:
  const int slaveSelectPin = 10;
  
  
  // set the slaveSelectPin as an output:
  pinMode(slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin();
  
  
//      TAP TEMPO SETUP
//
//
//

{
  pinMode( 12, INPUT );   /* tap button - press it to set the tempo */
  pinMode( 13, OUTPUT );  /* button state display - not required */
  
  for( int i=2 ; i<12 ; i++ ) 
  {
    pinMode( i, OUTPUT );  /* tempo display light - shows the current tempo */
  }
}


int lastTapState = LOW;  /* the last tap button state */
unsigned long currentTimer[2] = { 500, 500 };  /* array of most recent tap counts */
unsigned long timeoutTime = 0;  /* this is when the timer will trigger next */
unsigned long downTime = 0;     /* for our delayed press reset */

unsigned long indicatorTimeout; /* for our fancy "blink" tempo indicator */
boolean pressTimeout = false;


  
}

void loop() {
  
  //                    TAP TEMPO
  //
  //
  //
  
  
  /* TRANSISTION DETECTION:
     read the button on pin 12, and only pay attention to the
     HIGH-LOW transition so that we only register when the
     button is first pressed down */
     
  int tapState = digitalRead( 12 );
  if( tapState == LOW && tapState != lastTapState ) /* button up->down */
  {
    tap(); /* we got a HIGH-LOW transition, call our tap() function */
    downTime = millis();
    pressTimeout = false;
  }
  

  /* PRESS AND HOLD DETECTION */  
  
  if( tapState == LOW ) /* button is down... */
  {
    /* if we have not triggered before, and the down time is more than 2 seconds... */
    /* 2000 = 2000ms = 2 seconds */
    if( !pressTimeout && ((millis() - downTime ) > 2000 ))
    {
      /* lets hard code a 1/10 delay...
         you can use this to trigger other things as well */
      currentTimer[0] = currentTimer[1] = 100; /* make sure they get averaged to be equal */
      rescheduleTimer(); /* start the timer */
      pressTimeout = true; /* make sure we don't get called again during this press */
    }
  }
  
  lastTapState = tapState; /* keep track of the last state, for transition detection */
  
  
  /* CHECK FOR TIMER TIME OUT */
  if( millis() >= timeoutTime )
  { 
    /* timeout happens */
    indicatorTimeout = millis() + 60;  /* this sets the time when the LED goes off */
    /* and reschedule the timer to keep the pace */
    rescheduleTimer();
  }
  
  /* BUTTON STATE ON LED 13 */
  
  digitalWrite( 13, tapState );
  
  /* display the tap blink on all other LEDs */
  for( int i=2 ; i<12 ; i++ ) {
    if( millis() < indicatorTimeout ) {
      digitalWrite( i, HIGH );
    } else {
      digitalWrite( i, LOW );
    }
  }
}


unsigned long lastTap = 0; /* when the last tap happened */
void tap()
{
  /* we keep two of these around to average together later */
  currentTimer[1] = currentTimer[0];
  currentTimer[0] = millis() - lastTap; /* current = duration since last tap */
  lastTap = millis(); 
  timeoutTime = 0; /* force the trigger to happen immediately - sync and blink! */
}


void rescheduleTimer()
{
  
    /* set the timer to go off again when the time reaches the 
       timeout.  The timeout is all of the "currentTimer" values averaged
       together, then added onto the current time.  When that time has been
       reached, the next tick will happen...
    */
    
    
    timeoutTime = millis() + ((currentTimer[0] + currentTimer[1])/2);
  
  
//
//     DIGITAL POTENTIOMETER 
//
//
//
  
  // go through the six channels of the digital pot:
  for (int channel = 0; channel < 6; channel++) {
    // change the resistance on this channel from min to max:
    for (int level = 0; level < 255; level++) {
      digitalPotWrite(channel, level);
      delay(10);
    }
    // wait a second at the top:
    delay(100);
    // change the resistance on this channel from max to min:
    for (int level = 0; level < 255; level++) {
      digitalPotWrite(channel, 255 - level);
      delay(10);
    }
  }
}


//
//          READ VOLTAGE ON ROTATRY SWITCH
//
//

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);


  
  
  // 
  //           CASE STATEMENT
  //   check rotary switch for wave shape
  //
  //
  //
  
  
  // do some counting loop in each case statement that will change the int value to
  // write to the potentiometer
  
switch (var) {
    case sine:
      //do something when var equals 1
      break;
    case square:
      //do something when var equals 2
      break;
    case sawtooth:
      //do something when var equals 2
      break;
    case triangle:
      //do something when var equals 2
      break;
    case rand:
      //do something when var equals 2
      break;
     
    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
  }


//
//      WRITE VALUE TO POTENTIOMETER
//
//

void digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
}


//              NOTES
//
//
//
/*
    Tap Tempo with Press And Hold
    
    Scott Lawrence
    2006-December-09
    
    An experiment to detect tempo by tapping a button,
    as well as detecting presses of extended periods of time
    
    Press a button connected to digital pin 12.
    LED on pins 2-12 displays the beat pulse
    LED on pin 13 shows the current button state (dim when button is pressed)
    
    Digital Output <--------/\/ 220 ohm /\/----[LED]----> GND
    
    (Digital 13 is wired up to the LED on the NG board.  If you have an older 
     board, drop the standard LED between pin 13 and GND)
     
                     +------> +5 power
                     |
    Digital 12 <-----+----[ switch ]-----/\/ 10k ohm /\/-----> GND

    The behavior of this program is as follows:
      - the LEDs will blink to a specific tempo.
      - the user will tap out a new tempo on the switch (3 taps required)
      - the leds will blink to this new tempo.
        (it actually will blink to the previous two tap delays averaged together)
      - if the user presses and holds the tap button for 2 seconds, it goes to a 
        preset blink rate of 1/10 of a second.
*/

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


