void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  Serial.println("note on");
  int chan = channel;
  uint8_t note = pitch*2 + 30;
  uint8_t bright = velocity*2;
  uint8_t touch_sat = velocity*2;
  //display_matrix_right(pattern, gHue, hue, global_sat, 255, 255, 0);
  
  // handle the channel message
  switch(chan)
  {
    case 1: // I dont use channel one for LEDS as the clock tends to reside here.....
      {
        addGlitter(200);
        FastLED.show();
        break;
      }
    case 2: // This fills the whole strip without looping
    {
        fill_gradient(leds, 0, CHSV( note, global_sat, bright), NUM_LEDS, CHSV( note + offset_grad, global_sat, bright),SHORTEST_HUES);
        display_matrix_right(pattern, note, note, global_sat, 255, 0, 255);
        FastLED.show();
        break;
    }
    case 3:
    {
        fill_gradient(leds, 0, CHSV( note, global_sat, bright), NUM_LEDS, CHSV( note + offset_grad, global_sat, bright),SHORTEST_HUES);
        display_matrix_right(pattern, note, note, global_sat, 255, 255, 255);
        FastLED.show();
        break;
    }
    case 4:
    {
        fill_gradient(leds, 0, CHSV( note,  255, bright), NUM_LEDS, CHSV( note + offset_grad, global_sat, bright),SHORTEST_HUES);
       
        fill_gradient(leds_2, 0, CHSV( note,  255, bright), NUM_2_LEDS, CHSV( note + offset_grad, global_sat, bright),SHORTEST_HUES);
        
        display_matrix_right(pattern, gHue, note, global_sat, 255, 0, 255); 
        FastLED.show();
        break;
    }
    case 5:
    { 
      int pos = 0;
      while ( pos < 5)
      {
        bpm(200);
        FastLED.show();
        FastLED.delay(50);
        pos++;
      }
      
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      FastLED.show();
      break;
      break;
    }
    case 6:
    {
      int pos = 0;
      while ( pos < 5)
      {
        bpm(note);
        FastLED.show();
        FastLED.delay(50);
        pos++;
      }
      
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      FastLED.show();
      break;
    }
    case 7:
    {
      corner_pulse_out(note, global_sat, bright);
      corner_pulse_out(note, global_sat, 0);      
      break;
    }
    case 8:
    {
      display_matrix_right(inside, note, hue, global_sat, 255, 255, 0);     
      break;
    }
    case 9: //Kick, fills a color
    {
      bottom_side(note, global_sat, bright);  
      FastLED.show();
      break;
    }
    case 10:// Deep kick
    {
      display_matrix_right(pattern, gHue, gHue, global_sat, 255, 0, 255); 
      fill_solid(leds_2, NUM_LEDS, CHSV(gHue,global_sat,global_bright));        
      FastLED.show();
      FastLED.delay(200);
      break;
    }
    case 11: // Clap fills the odd LEDs w a rainbow
    {    
      top_side(note, global_sat, bright);
      FastLED.show();  
      for (int k = 0; k < NUM_LEDS; k++)       
      {
        if (k %4 == 0)
          leds[k] = CHSV( gHue +50, global_sat, bright);
        gHue++;
      }
      FastLED.show();
      break;
    }
    case 12: // Snare fills the odd leds w a color
    {
      top_side(note, global_sat, bright); 
      for (int k = 0; k < NUM_LEDS; k++)      
      {
        if (k %4 != 0)
          leds[k] = CHSV( gHue-50, global_sat, bright);
      }
      gHue++;
      FastLED.show();
      break;
    }
    case 13: // hi hat
    {
      if (side_flag == 0)
      {
        right_side(note, global_sat, bright);
        side_flag = 1;
      }
      else
      {
        left_side(note, global_sat, bright);
        side_flag = 0;
      }
      break;
    }
    case 14:// second hi hat
    {
      if (side_flag == 0)
      {
        left_side(note, global_sat, bright);
        side_flag = 1;
      }
      else
      {
        right_side(note, global_sat, bright);
        side_flag = 0;
      }
      break;
    }
    case 15: //crash DO SOMETHIGN WILD HERE
    {
      corner_pulse_in(note, global_sat, bright);
      corner_pulse_in(note, global_sat, 0);
    
      break;
    }
    case 16: // This is a white strobe DANGER: use cation when increasing brightness, high amps needed.
    {
      fill_solid(leds, NUM_LEDS, CHSV(0,0,100));   
      display_matrix_right(pattern, pitch*2 + 30, hue, global_sat, 0, 255, 255);  
      fill_solid(leds_2, NUM_LEDS, CHSV(0,0,100));     
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
      fadeToBlackBy( leds_2, NUM_2_LEDS, 10);
 
      int pos = random16(NUM_LEDS);
      leds[pos] += CHSV( gHue + random8(64), 200, 255);
      pos = random16(NUM_LEDS);
      leds_2[pos] += CHSV( gHue + random8(64), 200, 255);
      FastLED.show();
    }
    fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
    fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
    FastLED.show();
}
void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  int chan = channel;
  switch(chan)
  {
    case 1:
    {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
    
      break;
    }
    case 2:
    {
      for (int k = 0; k < NUM_LEDS; k++)         
        leds[k].fadeToBlackBy( 200 ); 
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      FastLED.show(); 
      break;
    }
    case 3:
    {
      for (int k = 0; k < NUM_LEDS; k++)         
        leds[k].fadeToBlackBy( 255 ); 
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      display_matrix_right(pattern, pitch*2 + 30, hue, global_sat, 255, 255, 0);
      FastLED.show(); 
      break;
    }
    case 4:
    {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      FastLED.show();
      break;
    }
    case 5: 
    {    
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      display_matrix_right(pattern, pitch*2 + 30, hue, global_sat, 255, 255, 0);
      FastLED.show();
      break;
    }
    case 6:
    {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      display_matrix_right(pattern, pitch*2 + 30, hue, global_sat, 255, 255, 0);
      FastLED.show();
      break;
    }
    case 7:
    {
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      break;
    }
    case 8:
    {
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      display_matrix_right(pattern, pitch*2 + 30, hue, global_sat, 255, 255, 0);
      break;
    }
    case 9:
    {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      FastLED.show();
      break;
    }
    case 10:
    {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      FastLED.show();
      break;
    }
    case 11:
    {
      for (int k = 0; k < NUM_LEDS; k++)       
      {
        if (k %4 == 0)
          leds[k] = CHSV(0, 255, 0);      
      } 
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      //display_matrix_right(pattern, pitch*2 + 30, hue, global_sat, 255, 255, 0);
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      FastLED.show();
      break;
    }
    case 12:
    {
      for (int k = 0; k < NUM_LEDS; k++)      
      {
        if (k %4 != 0)
          leds[k] = CHSV( 0, 255, 0);
      }
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      //display_matrix_right(pattern, pitch*2 + 30, hue, global_sat, 255, 255, 0);
      FastLED.show();
      break;
    }
    case 13:
    {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      //display_matrix_right(pattern, pitch*2 + 30, hue, global_sat, 255, 255, 0);
      FastLED.show();
      break;
    }  
    case 14:
      {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      //display_matrix_right(pattern, pitch*2 + 30, hue, global_sat, 255, 255, 0);
      FastLED.show();
      break;
      }
    case 15:
      break;
    case 16:
    {
      fill_solid(leds, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds_2, NUM_2_LEDS, CRGB(0,0,0));
      display_matrix_right(pattern, pitch*2 + 30, hue, global_sat, 255, 255, 0);
      FastLED.show(); 
      break;
    }
    default:
      break;
  }
}
