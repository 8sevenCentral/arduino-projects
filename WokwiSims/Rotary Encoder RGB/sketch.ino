#include <FastLED.h>
#include <ezButton.h>  // the library to use for SW pin

#define CLK_PIN 2
#define DT_PIN 3
#define SW_PIN 4
#define LED_PIN 7

#define NUM_LEDS    20  // Set the number of LEDs
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

ezButton button(SW_PIN);  // create ezButton object that attach to SW_PIN
CRGB leds[NUM_LEDS];

enum ColorState {
    RED,
    BLUE,
    GREEN
};

ColorState currentColor = RED;
int counter = 0; // Number of LEDs turned on
int CLK_state;
int prev_CLK_state;

void setup() {
    Serial.begin(9600);
    pinMode(CLK_PIN, INPUT);
    pinMode(DT_PIN, INPUT);
    button.setDebounceTime(50);  // set debounce time to 50 milliseconds
    prev_CLK_state = digitalRead(CLK_PIN);
    
    // Initialize all LEDs to off
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
    button.loop();  // MUST call the loop() function first
    CLK_state = digitalRead(CLK_PIN);

    // If the state of CLK is changed, then pulse occurred
    if (CLK_state != prev_CLK_state && CLK_state == HIGH) {
        if (digitalRead(DT_PIN) == HIGH) {
            // Counter-clockwise direction
            if (counter > 0) {
                counter--;
                leds[counter] = CRGB::Black;  // Turn off the LED
            }
        } else {
            // Clockwise direction
            if (counter < NUM_LEDS) {
                // Alternate between half and full brightness
                if (leds[counter].r == 0) {
                    leds[counter] = getColor(currentColor).fadeToBlackBy(128); // Half brightness
                } else if (leds[counter].r < 255) {
                    leds[counter] = getColor(currentColor); // Full brightness
                }
                counter++;
            }
        }

        Serial.print("COUNTER: ");
        Serial.println(counter);
    }

    // Update the LEDs
    FastLED.show();
    prev_CLK_state = CLK_state;

    // Check if the button is pressed
    if (button.isPressed()) {
        changeColor();
    }
}

// Function to get the current color based on the state
CRGB getColor(ColorState colorState) {
    switch (colorState) {
        case RED: return CRGB::Red;
        case BLUE: return CRGB::Blue;
        case GREEN: return CRGB::Green;
        default: return CRGB::Black;
    }
}
// Function to change the color state
void changeColor() {
    currentColor = static_cast<ColorState>((currentColor + 1) % 3); // Cycle through RED, BLUE, GREEN
    // Update all LEDs to the new color regardless of their state
    for (int i = 0; i < NUM_LEDS; i++) {
        // Change the color of the LED regardless of its state
        if (leds[i].r == 0 && leds[i].g == 0 && leds[i].b == 0) {
            // LED is off, just set its color without turning it on
            leds[i] = getColor(currentColor).fadeToBlackBy(255); // Keep it off but set the color
        } else {
            // LED is on, change its color
            leds[i] = getColor(currentColor);
        }
    }
}
