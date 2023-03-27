#include <Bounce2.h>

/*  Alternating LED's  */
//#include <Bounce.h>


const int inputPin = 4;    // momentary switch
const int ledPin =  13;      // the number of the LED pin
const int relayPin1 =  1;
const int relayPin2 = 2;

byte mode = 0;

//Bounce bouncer = Bounce(inputPin,75); //settup debounce for first push button
Bounce  bouncer  = Bounce();

void setup() 
{ pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  
   // Setup the button
 pinMode( inputPin ,INPUT);
 // Activate internal pull-up (optional) 
 digitalWrite( inputPin ,HIGH);
 // After setting up the button, setup the object
 bouncer .attach( inputPin );
 bouncer .interval(5);
 
}

void loop() {
  bouncer.update ( );    // Update the debouncer for the push button
  switch( mode )
  {
    case 0://------------------------ I'm off and in restmode
      if ( bouncer.read() == HIGH )
      { digitalWrite (ledPin, HIGH);     // switch LED ON
       // digitalWrite (relayPin1, LOW);
       // digitalWrite (relayPin2, HIGH);  // switch relay ON
                                      
        mode = 1;
      }
      break;
    case 1://------------------------ I'm in ON mode, w8 4 keyrelease
      if ( bouncer.read() == LOW )
      
      { digitalWrite (ledPin, HIGH);     // switch LED ON
        // digitalWrite (relayPin1, HIGH);
        // digitalWrite (relayPin2, LOW);  // switch relay ON
      
        mode = 2;
      }
      break;
    case 2://------------------------ I'm ON and in restmode
      if ( bouncer.read() == HIGH )
      { digitalWrite (ledPin, HIGH);     // switch LED ON
        digitalWrite (relayPin1, LOW);
        digitalWrite (relayPin2, LOW);      // switch relay ON
       
        mode = 3;
      }
      break;
    case 3://------------------------ I'm in OFF mode, w8 4 keyrelease
      if ( bouncer.read() == LOW )
      
      { digitalWrite (ledPin, LOW);     // switch LED ON
        // digitalWrite (relayPin1, LOW);
        // digitalWrite (relayPin2, HIGH);      // switch relay ON
        
        mode = 0;
        
      }
      break;
  }//switch


}//loop
