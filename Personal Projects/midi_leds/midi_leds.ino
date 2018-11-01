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

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
MIDI_CREATE_DEFAULT_INSTANCE();

// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// http://arduinomidilib.fortyseveneffects.com/a00022.html

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    // Do whatever you want when a note is pressed.
    
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
    if (channel == 12)
     {
      uint8_t note = (pitch * 2);
      int i= 0;
      while (i < NUM_LEDS)       
      {
        //if (i %3 == 0)
          leds[i] = CHSV( 200, 255, 255);
        i++;
      }
      FastLED.show();
     }
    if (channel == 9)
    {
      uint8_t note1 = (pitch);
      int j= 0;
      while (j < NUM_LEDS)       
      {
        //if (j % 4 == 0)
          leds2[j] = CHSV( 0, 255, 255);
        j++;
      }
      FastLED.show();
    }
    if (channel == 2)
    {
      uint8_t note2 = (pitch*2);
      int k= 0;
      while (k < NUM_LEDS)       
      {
        leds1[k] = CHSV( note2, 255, 255);
        k++;
      }
      FastLED.show();
    }
    if (channel == 3)
    {
      uint8_t note3 = (pitch*2);
      int m= 0;
      while (m < NUM_LEDS)       
      {
        leds3[m] = CHSV( note3, 255, 255);
        m++;
      }
      FastLED.show();
    }
  //FastLED.show();
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
   
     if (channel == 12)
     {
      uint8_t note = (pitch * 2);
      int i= 0;
      while (i < NUM_LEDS)       
      {
        //if (i %3 == 0)
          leds[i].fadeLightBy( 255 );
        i++;
      }
      //FastLED.show();
     }
    if (channel == 9)
    {
      uint8_t note1 = (pitch);
      int j= 0;
      while (j < NUM_LEDS)       
      {
        //if (j % 4 == 0)
          leds2[j].fadeLightBy( 255 );
        j++;
      }
      //FastLED.show();
    }
    if (channel == 3)
    {
      uint8_t note2 = (pitch*2);
      int k= 0;
      while (k < NUM_LEDS)       
      {
        leds3[k].fadeLightBy( 255 );
        k++;
      }  
    }
}
void handleClock(void)
{
  
}
void handleStop(void)
{
    int k= 0;
      while (k < NUM_LEDS)       
      {
        leds[k] = CHSV( 0, 0, 0);
        leds1[k] = CHSV( 0,0, 0);
        leds2[k] = CHSV( 0, 0, 0);
        leds3[k] = CHSV( 0, 0, 0);
        k++;
      } 
      FastLED.show();
}
// -----------------------------------------------------------------------------

void setup()
{
    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
    MIDI.setHandleStop(handleStop);
    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.setHandleClock(handleClock);
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

    // There is no need to check if there are messages incoming
    // if they are bound to a Callback function.
    // The attached method will be called automatically
    // when the corresponding message has been received.
}
