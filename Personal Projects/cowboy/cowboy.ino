#include "FastLED.h"
#include "Timer.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif
Timer t;
#define DATA_PIN    10
#define X_IN A2
#define Y_IN A3
#define Z_IN A4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    60
CRGB leds[NUM_LEDS];
uint8_t x_flag = 0;
uint8_t y_flag = 0;
uint8_t z_flag = 0;
uint8_t x_color = 0;
uint8_t y_color = 0;
uint8_t z_color = 0;
int m = 0;
int n = 30;
int g = 0;
#define BRIGHTNESS          200
#define FRAMES_PER_SECOND  30

void setup() {
  Serial.begin(9600);
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  int tickEvent = t.every(100, takeReading);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  Serial.print(analogRead(X_IN));
  Serial.print(",");
  Serial.print(analogRead(Y_IN));
  Serial.print(",");
  Serial.println(analogRead(Z_IN));
  // Call the current pattern function once, updating the 'leds' array
  //gPatterns[gCurrentPatternNumber]();
 int value =analogRead(X_IN);
 int valuey =analogRead(Y_IN);
 x_color = map(value, 450, 590, 50, 250);
 y_color = map(value, 600, 650, 0, 170);
 int z = analogRead(Z_IN);
 g = g +1;
 if (g > NUM_LEDS -1)
{
  g = 0;   
}
  if (z > 540)
  {
    for (int i = 0 ; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::White;
    }
    FastLED.show();
    FastLED.delay(10);
    for (int i = 0 ; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
    }
  }
  else
  {
    for (int i = g ; i < NUM_LEDS   ; i++)
    {
      leds[i] = CHSV(x_color, 255, 255);
    }
    leds[m] = CHSV(y_color,255,255);
    leds[m-1] = CHSV(x_color, 255, 255);
    m = m + 1;
    if (m > 30)
    {
      m = 0;
    }
    leds[n] = CHSV(z_color,255,255);
    leds[n-1] = CHSV(x_color, 255, 255);
    n = n - 1;
    if (n < 2)
    {
      n = 30;
    }
  }
  // send the 'leds' array out to the actual LED strip
  
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  //EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  t.update();
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
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
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void takeReading()
{
  Serial.print(analogRead(X_IN));
  Serial.print(",");
  Serial.print(analogRead(Y_IN));
  Serial.print(",");
  Serial.println(analogRead(Z_IN));
}

