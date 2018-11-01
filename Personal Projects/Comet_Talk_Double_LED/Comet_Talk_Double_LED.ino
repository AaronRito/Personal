// MirroringSample - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up four NEOPIXEL strips on four
// different pins, and show the same thing on all four of them, a simple bouncing dot/cyclon type pattern

#include "FastLED.h"

#define NUM_LEDS_PER_STRIP 150
CRGB leds[NUM_LEDS_PER_STRIP];
uint8_t gHue = 0;
int frame = 0;
int flag = 0;

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  // tell FastLED there's 60 NEOPIXEL leds on pin 4
  FastLED.addLeds<NEOPIXEL, 3>(leds, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin 5
  FastLED.addLeds<NEOPIXEL, 11>(leds, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin 6
  //FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS_PER_STRIP);

  // tell FastLED there's 60 NEOPIXEL leds on pin 7
  //FastLED.addLeds<NEOPIXEL, 7>(leds, NUM_LEDS_PER_STRIP);
}

void loop() {
//  for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
//    // set our current dot to red
//    leds[i] = CRGB::Red;
//    FastLED.show();
//    // clear our current dot before we move on
//    leds[i] = CRGB::Black;
//    delay(1);
//  }
//
//  for(int i = NUM_LEDS_PER_STRIP-1; i >= 0; i--) {
//    // set our current dot to red
//    leds[i] = CRGB::Red;
//    FastLED.show();
//    // clear our current dot before we move on
//    leds[i] = CRGB::Black;
//    delay(1);
//  }
//juggle();
//bpm();
//rainbowWithGlitter();
//confetti();
//sinelon();
if (flag == 0)
{
  juggle();
  frame = frame+1;
  if (frame > 300)
  {
    frame =0;
    flag = 1;
  }
}
else if (flag == 1)
{
  bpm();
  frame = frame+1;
  if (frame > 250)
  {
    frame =0;
    flag = 2;
  }
}
else
{
  sinelon();
  frame = frame+1;
  if (frame > 400)
  {
    frame =0;
    flag = 0;
  }
}
FastLED.delay(frame/10);
gHue = gHue+1;
}
void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS_PER_STRIP, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS_PER_STRIP) ] += CRGB::White;
  }
}
void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS_PER_STRIP, 10);
  int pos = random16(NUM_LEDS_PER_STRIP);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS_PER_STRIP, 20);
  int pos = beatsin16(13,0,NUM_LEDS_PER_STRIP);
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS_PER_STRIP; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS_PER_STRIP, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS_PER_STRIP)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
