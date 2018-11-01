#include <MIDI.h>
#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 150

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define DATA_PIN1 4
#define DATA_PIN2 5
#define DATA_PIN3 6

// Define the arrays of leds
CRGB leds[NUM_LEDS];
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

// MIDI library init
MIDI_CREATE_DEFAULT_INSTANCE();

// a rotating color
uint8_t gpal =0;
uint8_t gsat = 255;
int sat_flag = 0;
// Offset for the gradients
uint8_t offset = 18;
uint8_t sat = 75;
// This function handels the MIDI channel message for note on. Assign your fucntions to the channel you want to use.
// FASTLED uses all the interrupt registers, causing MIDI to miss an occasional message, you can read about it here:
// https://github.com/FastLED/FastLED/wiki/Interrupt-problems
// It's annoying but works 90% of the time, perhaps multithreading for consecutive messages?? better controller?
void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  // get your variables. MIDI pitch and velocity are from 0-127, so multiplying by 2 is good for 8 bit LEDS.
  int chan = channel;
  uint8_t note = pitch*2 + 30;
  uint8_t bright = velocity*2;
  uint8_t touch_sat = velocity*2;
  
  // handle the channel message
  switch(chan)
  {
    case 1: // I dont use channel one for LEDS as the clock tends to reside here.....
      break;
    case 2: // This fills the whole strip without looping
    {
        fill_gradient(leds1, 0, CHSV( note, gsat, bright), NUM_LEDS, CHSV( note + offset, gsat, bright),SHORTEST_HUES);
        //fill_solid(leds1, NUM_LEDS, CHSV( note,  255, bright));
        FastLED.show();
        break;
    }
    case 3:
    {
        fill_gradient(leds3, 0, CHSV( note, gsat, bright), NUM_LEDS, CHSV( note + offset, gsat, bright),SHORTEST_HUES);
        FastLED.show();
        break;
    }
    case 4:
    {
        fill_gradient(leds, 0, CHSV( note,  255, bright), NUM_LEDS, CHSV( note + offset, gsat, bright),SHORTEST_HUES);
        fill_gradient(leds1, 0, CHSV( note + offset,  255, bright), NUM_LEDS, CHSV( note, gsat, bright),SHORTEST_HUES);
        fill_gradient(leds2, 0, CHSV( note,  255, bright), NUM_LEDS, CHSV( note + offset, gsat, bright),SHORTEST_HUES);
        fill_gradient(leds3, 0, CHSV( note + offset,  255, bright), NUM_LEDS, CHSV( note, gsat, bright),SHORTEST_HUES);
        FastLED.show();
        break;
    }
    case 5:
    { 
      for (int i = 0; i < 10; i++)
      {
        fadeToBlackBy( leds, NUM_LEDS, 10);
        fadeToBlackBy( leds1, NUM_LEDS, 10);
        fadeToBlackBy( leds2, NUM_LEDS, 10);
        fadeToBlackBy( leds3, NUM_LEDS, 10);
        int pos = random16(NUM_LEDS);
        leds[pos] += CHSV( note + random8(64), 200, 255);
        pos = random16(NUM_LEDS);
        leds1[pos] += CHSV( note + random8(64), 200, 255);
        pos = random16(NUM_LEDS);
        leds2[pos] += CHSV( note + random8(64), 200, 255);
        pos = random16(NUM_LEDS);
        leds3[pos] += CHSV( note + random8(64), 200, 255); 
        gpal++;
        FastLED.show();
      }
      break;
    }
    case 6:
    {
      int pos = 0;
      while ( pos < 5)
      {
        bpm(note);
        FastLED.show();
        pos++;
      }
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds3, NUM_LEDS, CRGB(0,0,0));
      FastLED.show();
      break;
    }
    case 7:
      break;
    case 8:
      break;
    case 9: //Kick, fills a color
    {
        
      fill_solid(leds2, NUM_LEDS, CHSV(gpal, gsat, bright));
      gpal++;
      FastLED.show();
      break;
    }
    case 10:// Hi Hat fills all evens w rainbow
    {
      for (int k = 0; k < NUM_LEDS; k++)       
      {
        if (k %2 == 0)
        {
          leds[k] = CHSV( gpal, gsat, bright);
          leds1[k] = CHSV( gpal + 50, gsat, bright);
          leds2[k] = CHSV( gpal + 100, gsat, bright);
          leds3[k] = CHSV( gpal + 150, gsat, bright);
        }
        gpal++;
      }
      FastLED.show();
      break;
    }
    case 11: // Clap fills the odd LEDs w a rainbow
    {     
      for (int k = 0; k < NUM_LEDS; k++)       
      {
        if (k %2 == 0)
          leds[k] = CHSV( gpal +50, gsat - sat, bright);
        gpal++;
      }
      FastLED.show();
      break;
    }
    case 12: // Snare fills the odd leds w a color
    {
      for (int k = 0; k < NUM_LEDS; k++)      
      {
        if (k %2 != 0)
          leds[k] = CHSV( gpal-50, gsat, bright);
      }
      gpal++;
      FastLED.show();
      break;
    }
    case 13:
      break;
    case 14:
      break;
    case 15:
      break;
    case 16: // This is a white strobe DANGER: use cation when increasing brightness, high amps needed.
    {
      fill_solid(leds, NUM_LEDS, CHSV(0,0,100));
      fill_solid(leds1, NUM_LEDS, CHSV(0,0,100));
      fill_solid(leds2, NUM_LEDS, CHSV(0,0,100));
      fill_solid(leds3, NUM_LEDS, CHSV(0,0,100));
      FastLED.show();
      break;
    } 
    default:
      break;
  }
  gpal++; // a color rotation for good measure.
  
  if (sat_flag == 0)
  { 
    gsat = gsat - 5;
    if (gsat < 160)
        sat_flag = 1;
  }
  else if (sat_flag == 1)
  {
    gsat = gsat + 5;
    if (gsat > 245)
      sat_flag = 0;
  }
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  int chan = channel;
  switch(chan)
  {
    case 1:
      break;
    case 2:
    {
      for (int k = 0; k < NUM_LEDS; k++)         
        leds1[k].fadeToBlackBy( 200 ); 
      //FastLED.show(); 
      break;
    }
    case 3:
    {
      for (int k = 0; k < NUM_LEDS; k++)         
        leds3[k].fadeToBlackBy( 255 ); 
      FastLED.show(); 
      break;
    }
    case 4:
    {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds3, NUM_LEDS, CRGB(0,0,0)); 
      FastLED.show();
      break;
    }
    case 5: 
    {    
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds3, NUM_LEDS, CRGB(0,0,0));
      FastLED.show();
      break;
    }
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
    {
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
      FastLED.show();
      break;
    }
    case 10:
    {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds3, NUM_LEDS, CRGB(0,0,0));
      FastLED.show();
      break;
    }
    case 11:
    {
      for (int k = 0; k < NUM_LEDS; k++)       
      {
        if (k %2 == 0)
          leds[k] = CHSV(0, 255, 0);      
      } 
      FastLED.show();
      break;
    }
    case 12:
    {
      for (int k = 0; k < NUM_LEDS; k++)      
      {
        if (k %2 != 0)
          leds[k] = CHSV( 0, 255, 0);
      }
      FastLED.show();
      break;
    }
    case 13:
    
    case 14:
      break;
    case 15:
      break;
    case 16:
    {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds3, NUM_LEDS, CRGB(0,0,0));
      FastLED.show(); 
      break;
    }
    default:
      break;
  }
}
void handleStop(void)
{

    for (int i = 0; i < 50; i++)
    {
      fadeToBlackBy( leds, NUM_LEDS, 10);
      fadeToBlackBy( leds1, NUM_LEDS, 10);
      fadeToBlackBy( leds2, NUM_LEDS, 10);
      fadeToBlackBy( leds3, NUM_LEDS, 10);
      int pos = random16(NUM_LEDS);
      leds[pos] += CHSV( gpal + random8(64), 200, 255);
      pos = random16(NUM_LEDS);
      leds1[pos] += CHSV( gpal + random8(64), 200, 255);
      pos = random16(NUM_LEDS);
      leds2[pos] += CHSV( gpal + random8(64), 200, 255);
      pos = random16(NUM_LEDS);
      leds3[pos] += CHSV( gpal + random8(64), 200, 255); 
      FastLED.show();
    }
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
    fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
    fill_solid(leds3, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
}
void bpm(uint8_t note)
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 120;
  CRGBPalette16 palette = PartyColors_p; //RainbowStripeColors_p; ForestColors_p; OceanColors_p;  LavaColors_p;CloudColors_p;
  CRGBPalette16 palette2 = RainbowStripeColors_p;
  CRGBPalette16 palette1 = HeatColors_p;
  CRGBPalette16 palette3 = ForestColors_p;
  CRGBPalette16 palette4 = OceanColors_p;
  CRGBPalette16 pal[5] = {palette, palette1, palette2, palette3, palette4};
  int sel = note/51 -1;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(pal[sel], note+(i*2), beat-note+(i*10));
    leds1[i] = ColorFromPalette(pal[sel], note+(i*2), beat-note+(i*10));
    leds2[i] = ColorFromPalette(pal[sel], note+(i*2), beat-note+(i*10));
    leds3[i] = ColorFromPalette(pal[sel], note+(i*2), beat-note+(i*10));
  }
}
void setup()
{
    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
    MIDI.setHandleStop(handleStop);
    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);
    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.addLeds<NEOPIXEL, DATA_PIN1>(leds1, NUM_LEDS);
    FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds2, NUM_LEDS);
    FastLED.addLeds<NEOPIXEL, DATA_PIN3>(leds3, NUM_LEDS);
}

void loop()
{
    // Call MIDI.read the fastest you can for real-time performance.
    MIDI.read();
    EVERY_N_MILLISECONDS( 200 ) { gpal++; }
    // There is no need to check if there are messages incoming
    // if they are bound to a Callback function.
    // The attached method will be called automatically
    // when the corresponding message has been received.
}
