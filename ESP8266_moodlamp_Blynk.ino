#include <FastLED.h>

const int LED_PIN = 5;
const int NUM_LEDS = 10;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {
     for (int led = 0; led < NUM_LEDS; led++) {
        leds[led] = CRGB(0, 0, 0);
        FastLED.show();
        delay(200);
      }

    for (int led = 0; led < NUM_LEDS; led++) {
        leds[led] = CRGB(120, 255, 0);
        FastLED.show();
        delay(200);
      }
    
  
  delay(3000);

  //  for (int val = 255; val > 0; val -= 4) {
  //    for (int led = 0; led < NUM_LEDS; led++) {
  //      leds[led] = CHSV(120, 255, val);
  //      FastLED.show();
  //    }
  //  }
  //  delay(300);


    leds[2].fadeLightBy(255);
    leds[3].fadeLightBy(255);
    FastLED.show();
    delay(2000);
    leds[2].setRGB(120,255,0);
    leds[2].fadeLightBy(230);
    leds[3].setRGB(120,255,0);
    leds[3].fadeLightBy(230);
    FastLED.show();
    delay(2000);
}
