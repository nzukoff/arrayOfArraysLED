#include "FastLED.h"
#define LED_PIN1    3
#define LED_PIN2    5
#define LED_PIN3    6
#define LED_PIN4    10
#define NUM_STRIPS  4
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS_PER_STRIP 8
#define BRIGHTNESS 150
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPinX = A0;  
const int analogInPinY = A1;  
const int digitalInPin = 9;  

int JoystickValueX = 0;        // value read from the pot
int JoystickValueY = 0;        // value read from the pot
int JoystickButtonValue = 0;        // value read from the pot

int outputValue = 0;        // value output to the PWM (analog out)
int currentPositionX = 0;
int previousPositionX = 0;
int currentPositionY = 0;
int previousPositionY = 0;
boolean started = false;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN1, COLOR_ORDER>(leds[0], NUM_LEDS_PER_STRIP).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds[1], NUM_LEDS_PER_STRIP).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN3, COLOR_ORDER>(leds[2], NUM_LEDS_PER_STRIP).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN4, COLOR_ORDER>(leds[3], NUM_LEDS_PER_STRIP).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(9600);
  pinMode(digitalInPin, INPUT_PULLUP);  
}


void loop() {

//  // This outer loop will go over each strip, one at a time
//  for(int x = 0; x < NUM_STRIPS; x++) {
//    // This inner loop will go over each led in the current strip, one at a time
//    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
//      leds[x][i] = CRGB::Red;
//      FastLED.show();
//      leds[x][i] = CRGB::Black;
//      delay(100);
//    }
//  }

   // read the input values
  JoystickValueX = analogRead(analogInPinX);
  JoystickValueY = analogRead(analogInPinY);
  JoystickButtonValue = digitalRead(digitalInPin);

//  // print the results to the serial monitor:
//  Serial.print(JoystickValueX);
//  Serial.print(",");
//  Serial.print(JoystickValueY);
//  Serial.print(",");
//  Serial.println(JoystickButtonValue);
//  
//
//  // wait 100 milliseconds before the next loop
//  // for the analog-to-digital converter to settle
//  // after the last reading:
//  delay(5);

  if (started == false) {
    leds[0][0] = CRGB::Red;
    FastLED.show();  
  }
  
  if (JoystickValueX > 900) {    
    started = true;
    leds[previousPositionX][previousPositionY] = CRGB::Black;
    currentPositionX++;
    if (currentPositionX > NUM_STRIPS-1) {
        currentPositionX = 0;
    }    
    previousPositionX = currentPositionX;
    leds[currentPositionX][currentPositionY] = CRGB::Red;
    FastLED.show();
    delay(100);
  }
  
  if (JoystickValueX < 100) {    
    started = true;
    leds[previousPositionX][previousPositionY] = CRGB::Black;
    currentPositionX--;
    if (currentPositionX < 0) {
        currentPositionX = NUM_STRIPS-1;
    }    
    previousPositionX = currentPositionX;
    leds[currentPositionX][currentPositionY] = CRGB::Red;
    FastLED.show();
    delay(100);
  }

    if (JoystickValueY > 900) {    
    started = true;
    leds[previousPositionX][previousPositionY] = CRGB::Black;
    currentPositionY++;
    if (currentPositionY > NUM_LEDS_PER_STRIP-1) {
        currentPositionY = 0;
    }    
    previousPositionY = currentPositionY;
    leds[previousPositionX][currentPositionY] = CRGB::Red;
    FastLED.show();
    delay(100);
  }
  
  if (JoystickValueY < 100) {    
    started = true;
    leds[previousPositionX][previousPositionY] = CRGB::Black;
    currentPositionY--;
    if (currentPositionY < 0) {
        currentPositionY = NUM_LEDS_PER_STRIP-1;
    }    
    previousPositionY = currentPositionY;
    leds[previousPositionX][currentPositionY] = CRGB::Red;
    FastLED.show();
    delay(100);
  }
}
