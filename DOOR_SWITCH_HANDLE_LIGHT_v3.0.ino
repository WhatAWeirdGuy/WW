#include <Adafruit_NeoPixel.h> // You must install Adafruit NeoPixel library before compiling
 
//You can have fun here changing the colors for the code
#define PIN 11 // Sets NanoPixel Data Pin
int doorSwitch = 2; // Pin for Door Switch
int fadeTimeRamp = 50; // First Stage Ramp
int fadeTime = 24; // Second Stage Ramp
int LEDstep = 2; // Second Stage Increments
int fadeValue = 0; // INITAL FADE VALUE *DONT TOUCH*
int finalStageFlickerDelay = 40; // Flicker step amount for 'Final Stage'

Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, 11, NEO_GRB + NEO_KHZ800);

uint32_t color1 = strip.Color(0, 225, 100); // Sets NanoPixel Color in RGB; Current Color is = TEAL


void setup() {
  pinMode(doorSwitch, INPUT_PULLUP);
  //pinMode(doorSwitch, HIGH); // for testing, not sure if it actually does anything
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

void loop() {
  if (digitalRead(doorSwitch) == LOW) {
    for (fadeValue; fadeValue >= 10; fadeValue = fadeValue - 10) {
     strip.setBrightness(fadeValue);
        strip.setPixelColor(1, color1); 
        strip.setPixelColor(2, color1); 
        strip.setPixelColor(3, color1); 
        strip.setPixelColor(4, color1); 
        strip.setPixelColor(5, color1); 
        strip.setPixelColor(6, color1); 
        strip.setPixelColor(0, color1);
        strip.show();
        
        Serial.print(" -- Fading Down -- ");
        
        delay(fadeTimeRamp);
    }
    strip.setBrightness(0);
    strip.show();
    fadeValue = 0;
    Serial.println("DOOR CLOSED");
    Serial.println(digitalRead(3));

  } else {
    
    Serial.print("Starting Fade Up :) ");
    
    fadeValue = 0;
    // THE FADE UP LOOP

    while (fadeValue < 40) 
    {
      if (digitalRead(doorSwitch) == LOW) {
        break;
      }

      Serial.print(" STAGE ONE setBrightness is: ");
      Serial.print(fadeValue);

      strip.setBrightness(fadeValue); // Sets Jewel Brightness
      strip.setPixelColor(1, color1); 
      strip.setPixelColor(2, color1); 
      strip.setPixelColor(3, color1); 
      strip.setPixelColor(4, color1); 
      strip.setPixelColor(5, color1);    
      strip.setPixelColor(6, color1); 
      strip.setPixelColor(0, color1);
        
      // wait for 30 milliseconds to see the dimming effect
      strip.show();
      delay(fadeTimeRamp);
      
      fadeValue += 1;
    }

    int r = 10;
    // THE SLOWER FADE FLICKER LOOP
    while (fadeValue < 225) {
      if (digitalRead(doorSwitch) == LOW) {
        break;
      }
      strip.setBrightness(fadeValue + random(-(fadeValue * .1), (fadeValue * .1)));
        strip.setPixelColor(1, color1); 
        strip.setPixelColor(2, color1); 
        strip.setPixelColor(3, color1); 
        strip.setPixelColor(4, color1); 
        strip.setPixelColor(5, color1); 
        strip.setPixelColor(6, color1); 
        strip.setPixelColor(0, color1);
      // wait for 30 milliseconds to see the dimming effect
      strip.show();
      Serial.println(fadeValue);
      delay(fadeTime);
      fadeValue += LEDstep;
    }
    Serial.println(fadeValue);
    int s = 35;
    
    // THE FLICKER LOOP
    while (digitalRead(doorSwitch) == HIGH) {
      if (digitalRead(doorSwitch) == LOW) {
        break;
      }
      strip.setBrightness(255 - s + random(-s, s));
        strip.setPixelColor(1, color1); 
        strip.setPixelColor(2, color1); 
        strip.setPixelColor(3, color1); 
        strip.setPixelColor(4, color1); 
        strip.setPixelColor(5, color1); 
        strip.setPixelColor(6, color1); 
        strip.setPixelColor(0, color1);
        
      strip.show();
      
      delay(finalStageFlickerDelay + random(-10,10));
    }

  Serial.print(digitalRead(2));
  
  }

}
