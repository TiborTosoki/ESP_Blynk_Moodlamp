#include <FastLED.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#define LED_PIN 5
#define NUM_LEDS 10
CRGB leds[NUM_LEDS];

int lightMode;                                         // mode: 1-Constant color, 2-One color breathing, 3-Random colors breathing, 4-Fade to random colors,
//                                                // 5-"Loading" one color, 6-"Loading" random colors, 7-Rainbow, 8-Wipe, 9-"Knight Rider",
int R, G, B;
bool state = true;                                // ON-true/OFF-false
int fadeDelay = 30;                               // all modes
int brightness; int fadeAmount = 1; int hue;      // mode 1/2, mode 5 (hue)
int currentHue = 0; int targetHue = 0;            // mode 3

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  //Serial.begin(9600);
  Blynk.begin("Feyfg_NmoUQRsrC8N-hs4te_2kMCcSbu", "Tosoki", NULL);
}


BLYNK_WRITE(V0) {
  R = param[0].asInt();
  G = param[1].asInt();
  B = param[2].asInt();
}

BLYNK_WRITE(V1) {
  lightMode = param.asInt();
}

BLYNK_WRITE(V2) {
  //  if(!((param.asInt() && state) || (!param.asInt() && !state))) {
  //      stateOnOff();
  //    }
  stateOnOff(param.asInt());
}

BLYNK_WRITE(V3) {
  fadeDelay = param.asInt();
}

BLYNK_WRITE(V4) {
  brightness = param.asInt();
}


void loop() {
  Blynk.run();

  switch (lightMode) {
    case 1: constantColor();
      break;
    case 2: breathingOneColor();
      break;
    case 3: breathingMultipleRandomColor();
      break;
    case 4: fadeToRandomColors();
      break;
    case 5: loadingOneColor();
      break;
    case 6: loadingToRandomColors();
      break;
    case 7: rainbow();
      break;
    case 8: wipe();
      break;
  }
}



//***** mode 1 - constant color *****
void constantColor() {
  fill_solid(leds, NUM_LEDS, CRGB(R, G, B));
  FastLED.setBrightness(brightness);
  FastLED.show();
}


//***** mode 2 - Breathing - one color *****
void breathingOneColor() {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i].setRGB(R, G, B);
    leds[i].fadeLightBy(brightness);
  }
  FastLED.show();

  brightness = brightness + fadeAmount;
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
  FastLED.delay(fadeDelay);    // 1-50
}



//***** mode 3 - Breathing - random colors *****
void breathingMultipleRandomColor() {
  if (brightness == 0) {
    hue = random(256);
  }

  fill_solid(leds, NUM_LEDS, CHSV(hue, 255, brightness));
  FastLED.show();

  brightness = brightness + fadeAmount;
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
  FastLED.delay(fadeDelay);    // 1-50
}



//***** mode 4 - Fading to random colors *****
void fadeToRandomColors() {
  if (currentHue == targetHue) {
    targetHue = random(256);
  }

  fill_solid(leds, NUM_LEDS, CHSV(currentHue, 255, 255));
  FastLED.show();

  if (currentHue > targetHue) {
    currentHue--;
  }
  if (currentHue < targetHue) {
    currentHue++;
  }
  FastLED.delay(fadeDelay * 3);
}



//***** mode 5 - "Loading" with one color *****
void loadingOneColor() {
  for (int i = 0; i < NUM_LEDS; i++) {
    for (int j = 256; j > 0; j -= 2) {
      leds[i].setRGB(R, G, B);
      leds[i].fadeLightBy(j);
      FastLED.show();
    }
    FastLED.delay(fadeDelay);
  }

  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB(R, G, B);
      leds[i].fadeLightBy(j);
      delay(fadeDelay / 20);
    }
    FastLED.show();
  }
  FastLED.delay(200);
}



//***** mode 6 - "Loading" intro random colors *****
void loadingToRandomColors() {
  for (int i = 0; i < NUM_LEDS; i++) {
    for (int j = 256; j > 0; j -= 2) {
      leds[i].setHSV(hue, 255, 255);
      leds[i].fadeLightBy(j);
      FastLED.show();
    }
    FastLED.delay(fadeDelay);
  }
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setHSV(hue, 255, 255);
      leds[i].fadeLightBy(j);
      FastLED.delay(fadeDelay / 19);
    }
    FastLED.show();
  }
  FastLED.delay(200);

  hue = random(256);
}


//***** mode 7 - Rainbow *****
void rainbow() {
  fill_rainbow(leds, NUM_LEDS, hue, 15);     // 15 = delta hue
  FastLED.setBrightness(brightness);
  FastLED.show();
  EVERY_N_MILLISECONDS(20) {
    hue++;
  }
  FastLED.delay(fadeDelay / 5);
}



void wipe() {

}

//***** Turn lights ON/OFF *****
//void stateOnOff() {
//  if (state) {
//    FastLED.setBrightness(0);
//    state = false;
//  } else {
//    FastLED.setBrightness(255);
//    state = true;
//  }
//}

void stateOnOff(int state) {
  if (!state) {
    FastLED.setBrightness(0);
  } else {
    FastLED.setBrightness(255);
  }
}
