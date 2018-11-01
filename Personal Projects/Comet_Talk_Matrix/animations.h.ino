// my CT sign functions
void corner_pulse_out(uint8_t note, uint8_t sat, uint8_t bright)
{
int waiting = 40;
display_matrix_right(inside, note, hue, global_sat, 255, bright, 0);
FastLED.delay(waiting);
display_matrix_right(middle, note, hue, global_sat, 255, bright, 0);
FastLED.delay(waiting);
display_matrix_right(outside, note, hue, global_sat, 255, bright, 0);
for(int i=0; i < left_num_6; i++) 
    leds_2[ left_side_6[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_6; i++) 
    leds_2[ top_side_6[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_6; i++) 
    leds_2[ right_side_6[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_6; i++) 
    leds_2[ bottom_side_6[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();

for(int i=0; i < left_num_5; i++) 
    leds_2[ left_side_5[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_5; i++) 
    leds_2[ top_side_5[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_5; i++) 
    leds_2[ right_side_5[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_5; i++) 
    leds_2[ bottom_side_5[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
for(int i=0; i < left_num_4; i++) 
    leds_2[ left_side_4[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_4; i++) 
    leds_2[ top_side_4[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_4; i++) 
    leds_2[ right_side_4[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_4; i++) 
    leds_2[ bottom_side_4[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
for(int i=0; i < left_num_3; i++) 
    leds_2[ left_side_3[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_3; i++) 
    leds_2[ top_side_3[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_3; i++) 
    leds_2[ right_side_3[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_3; i++) 
    leds_2[ bottom_side_3[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
for(int i=0; i < left_num_2; i++) 
    leds_2[ left_side_2[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_2; i++) 
    leds_2[ top_side_2[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_2; i++) 
    leds_2[ right_side_2[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_2; i++) 
    leds_2[ bottom_side_2[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
for(int i=0; i < left_num_1; i++) 
    leds_2[ left_side_1[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_1; i++) 
    leds_2[ top_side_1[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_1; i++) 
    leds_2[ right_side_1[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_1; i++) 
    leds_2[ bottom_side_1[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
  
  }
void corner_pulse_in(uint8_t note, uint8_t sat, uint8_t bright)
{
int waiting = 40;
for(int i=0; i < left_num_1; i++) 
    leds_2[ left_side_1[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_1; i++) 
    leds_2[ top_side_1[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_1; i++) 
    leds_2[ right_side_1[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_1; i++) 
    leds_2[ bottom_side_1[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
for(int i=0; i < left_num_2; i++) 
    leds_2[ left_side_2[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_2; i++) 
    leds_2[ top_side_2[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_2; i++) 
    leds_2[ right_side_2[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_2; i++) 
    leds_2[ bottom_side_2[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
for(int i=0; i < left_num_3; i++) 
    leds_2[ left_side_3[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_3; i++) 
    leds_2[ top_side_3[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_3; i++) 
    leds_2[ right_side_3[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_3; i++) 
    leds_2[ bottom_side_3[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
for(int i=0; i < left_num_4; i++) 
    leds_2[ left_side_4[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_4; i++) 
    leds_2[ top_side_4[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_4; i++) 
    leds_2[ right_side_4[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_4; i++) 
    leds_2[ bottom_side_4[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
for(int i=0; i < left_num_5; i++) 
    leds_2[ left_side_5[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_5; i++) 
    leds_2[ top_side_5[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_5; i++) 
    leds_2[ right_side_5[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_5; i++) 
    leds_2[ bottom_side_5[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
for(int i=0; i < left_num_6; i++) 
    leds_2[ left_side_6[i] ] = CHSV( gHue, sat, bright);
for(int i=0; i < top_num_6; i++) 
    leds_2[ top_side_6[i] ] = CHSV( gHue + 70, sat, bright);
for(int i=0; i < right_num_6; i++) 
    leds_2[ right_side_6[i] ] = CHSV( gHue + 140, sat, bright);
for(int i=0; i < bottom_num_6; i++) 
    leds_2[ bottom_side_6[i] ] = CHSV( gHue + 190 + 30, sat, bright);
FastLED.show();
display_matrix_right(outside, note, hue, global_sat, 255, bright, 0);
FastLED.delay(waiting);
display_matrix_right(middle, note, hue, global_sat, 255, bright, 0);
FastLED.delay(waiting);
display_matrix_right(inside, note, hue, global_sat, 255, bright, 0);
}
void sat_effect()
{
  if (sat_flag == 0)
  {
    global_sat = global_sat+1;
    if (global_sat == 250)
      sat_flag = 1;
  }
  else
  {
    global_sat = global_sat - 1;
    if (global_sat == 150)
      sat_flag = 0;   
  }
  if (bright_flag == 0)
  {
    global_bright = (global_bright + 2);
    if (global_bright > 239)
      bright_flag = 1;
  }
  else
  {
    if (global_bright == 80)
    {
      count++;
      if (count > 50)
      {
        count = 0;
        bright_flag = 0;
      }  
    }
    else 
      global_bright = (global_bright - 1);  
  }
}// these are demo functions handy to have around
void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds_2, NUM_2_LEDS, gHue, 7);
}
void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) 
  {
    uint16_t pos = random16(NUM_LEDS);
    leds[ pos ] += CRGB(255,255,255); 
    uint16_t pos2 = random16(NUM_LEDS);
    leds_2[ pos2 ] += CRGB(255,255,255); 
  }
}
void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_2_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds_2[beatsin16( i+7, 0, NUM_2_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
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
  for( int i = 0; i < NUM_LEDS; i++) 
  { //9948
    leds[i] = ColorFromPalette(pal[sel], note+(i*2), beat-note+(i*10));   
    leds_2[i] = ColorFromPalette(pal[sel], note+(i*2), beat-note+(i*10));   
  }
}
