#include <FastLED.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#define LED_PIN 5
#define NUM_LEDS 10
CRGB leds[NUM_LEDS];

int R, G, B;


void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  //Serial.begin(9600);
  Blynk.begin("Feyfg_NmoUQRsrC8N-hs4te_2kMCcSbu", "Tosoki", NULL);
}


BLYNK_WRITE(V0) {
  R = param[0].asInt();
  G = param[1].asInt();
  B = param[2].asInt();
  constantColor();
}


void loop() {
  Blynk.run();
}



void constantColor(){
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CRGB(R, G, B);
  }
  FastLED.show();
}
