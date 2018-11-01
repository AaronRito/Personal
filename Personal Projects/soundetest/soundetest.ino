
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 6
int led = 13;
int base = 2;
int quietish = 15; //Change This
int rock =30;
int balls = 50;
int loud =90;
int crazy = 120;
int volume;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

void setup() {                
  Serial.begin(9600); // For debugging
  pinMode(led, OUTPUT);     
  strip.begin();
  strip.show();
}
 
void loop() {
  
  volume = analogRead(A0); // Reads the value from the Analog PIN A0
  volume = map(volume,0,1023,0,255);
  volume = constrain(volume, 0, 255);
  
    //Debug mode
    Serial.println(volume);
    delay(1);
    
      if(volume>base && volume<quietish){
   
      theaterChase(strip.Color(0, 127, 127), 10); // Lblue
  }  
    else if(volume>quietish && volume<rock){
   
      theaterChase(strip.Color(127, 0, 127), 100); // purple
  }
    else if(volume>rock && volume<balls){
  
     theaterChase(strip.Color(127, 0, 0), 100); // red
  }
  else if(volume>balls && volume<loud){
   
     theaterChase(strip.Color(0, 127, 0), 300); // green
  }
  else if(volume>loud && volume<crazy){
    
     rainbow(1);
  }
   else if(volume>crazy){
    theaterChaseRainbow(1);
     
  }
  else{
    theaterChase(strip.Color(0, 0, 0), 10); // green
    
  }
 
 
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<1; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(20);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(.004);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(0);
  }
}
