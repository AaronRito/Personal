#include "FastLED.h"

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

#define ANALOG A0
#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    144
CRGB leds[NUM_LEDS];
#define BRIGHTNESS   96
#define FRAMES_PER_SECOND  10
#define SPARKING 10
#define COOLING 20
CRGBPalette16 gPal;

bool gReverseDirection = true;

//Globals
int count = 0;
int zero_flag = 0;
uint8_t real_input;
int zero_counter = 0;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
int input;
int mapped_in;
int choice;


void setup() {
  //Setup Timer2 to fire every 1ms
  TCCR2B = 0x00;        //Disbale Timer2 while we set it up
  TCNT2  = 130;         //Reset Timer Count to 130 out of 255
  TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  
  TCCR2B = 0x05;        //Timer2 Control Reg B: Timer Prescaler set to 128
  delay(3000); // 3 second delay for Fast LED recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
}

void loop()
{
     
  
    
    mapped_in = map(real_input, 0, 900, 0, 255);
    Serial.println(mapped_in);
    if (mapped_in > 0 && mapped_in < 5)
    {

      confetti();
      //FastLED.delay(100);
      
      
    }
//        else if (mapped_in > 8 && mapped_in < 56)    
//    { 
//          uint8_t color_pick = map(mapped_in, 9, 55, 0, 255);
//          CRGB darkcolor  = CHSV(color_pick,255,192); // pure hue, three-quarters brightness
//          CRGB lightcolor = CHSV(gHue,128,255); // half 'whitened', full brightness
//          gPal = CRGBPalette16( gHue, darkcolor, lightcolor, CRGB::White);
//          Fire2012WithPalette();
//          FastLED.delay(30);
//    }
        else if (mapped_in > 4 && mapped_in < 40)
    {
      uint8_t color_pick = map(mapped_in, 4, 74, 0, 255);
      
      fill_solid( leds, NUM_LEDS, CRGB(color_pick++, mapped_in, 200)); 
      //FastLED.delay(20);
     //Serial.println(color_pick);
    }
    else if (mapped_in > 39 && mapped_in < 70)
    {
      for (int i = 0; i < 50; i++)
      {
        fill_rainbow( leds, NUM_LEDS, gHue-mapped_in, 7);
        //FastLED.delay(100);
        gHue++;
        }
     }   
        else if (mapped_in > 69)
    {
      for (int i = 0; i < 250; i++)
      {
        fill_rainbow( leds, NUM_LEDS, gHue-mapped_in, 7);
        addGlitter(175);
        //FastLED.delay(100);
        gHue++;
        }
     }  
  
  
  //fill_solid( leds, NUM_LEDS, CRGB(0, 0, 0));
 FastLED.show();
  gHue++;
}
ISR(TIMER2_OVF_vect)
{
 
    input = analogRead(ANALOG);
 
      real_input = input;


}

void confetti() 
{
  for (int i = 0; i < 15; i++)
  {
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy( leds, NUM_LEDS, 10);
    int pos = random16(NUM_LEDS);
    leds[pos] += CHSV(random8(255), 200, 255);
  }
}
void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = mapped_in;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
void Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}
void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
