#include "Timer.h"
#include "FastLED.h"

FASTLED_USING_NAMESPACE
#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define ANA A4
#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    144
CRGB leds[NUM_LEDS];
CRGBPalette16 gPal;
#define BRIGHTNESS   200
#define FRAMES_PER_SECOND  20

Timer t;
uint8_t color=0;
uint8_t bright;
int value=0;
int val;
int tempval;
int tempval_1 = 0;
int tempval_2 = 0;
int idle_flag =0;
int rate;
int count = 0;
int debug = 0;
uint8_t bright_dir;
#define SPARKING 120
#define COOLING  55
bool gReverseDirection = false;
uint8_t gHue = 0;

void setup() {
  Serial.begin(9600);
    delay(3000); // 3 second delay for Fast LED recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  gPal = OceanColors_p;
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  int tickEvent = t.every(1, control);
  int tickEvent1 = t.every(1000, control_1);

}

void loop() {
  // put your main code here, to run repeatedly:
  val = value;
 if (idle_flag == 0){ 
  if (val !=tempval)
  {
    lights(val);
    }
val= tempval;
 

}
else if (idle_flag ==1)
{
  random16_add_entropy( random());
  Fire2012WithPalette(); 
  FastLED.delay(20);
  }
FastLED.show();
t.update();
EVERY_N_MILLISECONDS( 20 ) { gHue++; }
}
void control(){
 
    value = analogRead(ANA);
    
}
void control_1(){
  
    tempval_1 = analogRead(ANA);
    if (debug)
    {
      Serial.print(tempval_1);
      Serial.print(" ");
      Serial.println(tempval_2);
    }
    if ((tempval_1 <= (tempval_2+5))&& (tempval_1 >= (tempval_2-5)))
    {

        count = count +1;
        if (count > 8)
        {
          idle_flag = 1;
          count = 0;
        }
    }
    else 
    {
      idle_flag = 0;
      count = 0;
    }
    tempval_2 = tempval_1;
    if (debug)
      Serial.println(idle_flag);
}
void lights(int val){

   color = map(val, 286, 982, 190, 0);
   for (int i = 0; i < 72;  i++){    
    leds[i] = CHSV(color, 200, bright);
   }
   for (int j = 72; j < 144;  j++){
    leds[j] = CHSV(color+50, 200, bright);
   }
  //add more tracers by copying lines, you can change the sin function in the next line
  int pos = beatsin16(color/6,27,NUM_LEDS);
  leds[pos] += CHSV( color+75, 255, 255);
  leds[max(pos-15,0)] += CHSV( color+100, 255, 255);
  leds[max(pos-30,0)] += CHSV( color-50, 255, 255);
  
     
     if (bright_dir == 0) {
    bright = (bright - val/4)+4;
  } else {
    bright = (bright + val/2)+2;
  }

  if (bright > val) {
    bright_dir = 0;
  } else if (bright < 100) {
    bright_dir = 1;
  }
  //rate = frame;
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
      CRGB color_1 = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color_1;
    }
}
void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}
