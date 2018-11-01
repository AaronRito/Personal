/* This program uses control voltage or value from a 0-5v pot to make a LED strip go freaking bonkers,
 *  depending on the value of the analog pin. 
 *  Author: Aaron Rito 
 *  Date : 8/18/15
 */
#include <Adafruit_NeoPixel.h>  // include the pixel library or dare to write your own. 
#include <avr/power.h>          // avr helper

#define PIN 6     // define PIN as the interger 6

//initialize the LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(144, PIN, NEO_GRB + NEO_KHZ800);

//define here the global variables we will use in the program. Global variables use more memory but are easier to use
//then dealing with dynamic memory in a non-professional hacker IDE
int r;
int g;
int b;
int i;
int x;

void setup() {  // put your setup code here, to run once:

  Serial.begin(9600); // For debuggin
  pixels.begin(); // pixels start
  strip.begin(); // strip start, we're not using this one right now but we might. 
  strip.show(); // more strip stuff
}

void loop() {                  // Main loop. This repeats endlessly unless you tell it to stop. It will execute each line in order according to your logic. 
                               // Loops and case staements have to be enclosed by curly braces "{ stuff }" I try to keep mine indented in line with the statement
                               //so I dont get confused.

  for(int i=0;i<144;i++){      //the for loop defines "i"  as 0 and increments the strip position everytime a tracer is done
                               // we have 144 led's, we will count to 144 over and over since we're in the main loop.

   x = analogRead(A0);         // Reads the value from the Analog PIN A0 each time a tracer ends
   x = map(x,0,1023,0,200);    // restricting the value to 0-200
   Serial.println (x);         //prints value on a new line in monitor

    if (x == 0){               // this case is for 0V. Lights out. If you want x = something you need 2 equals signs ==.....
                
        pixels.setPixelColor((i), pixels.Color((0),(0),(0)));
        pixels.show();
    }
    
    else if (x < 80) {         //the first condition of x, this same code repeats over and over.
                               //I've commented the first case so you can see what to do.
      
        r = 200;               // in each case you can change the color here.
        g = 0;
        b = 0;
        
        freakshow(i,r,g,b);   //the freakshow function uses the variables we defined,
                              // "i", is the position on the strip, "r,g,b" is colors.
                              // no need to modify this line
                            
        i++;                  // "i++;" increments the strip position, add more of them or
                              // remove some to change the tracer speed on the strip. Make sure to include the ";" 
    }

    else if (x > 79 && x < 100) {        // when using 2 conditions, they are combined by "and" = "&&" , or alternativly "or" = "||".
      
        r = 175;
        g = 25;
        b = 0;
        freakshow(i,r,g,b);
        i++;
        i++;
    }

    else if (x > 99 && x < 110) {
      
        r = 125;
        g = 75;
        b = 0;
        freakshow(i,r,g,b);
        i++;
        i++;
        i++;
    }
    
    else if (x > 109 && x < 120) {
            
        r = 50;
        g = 150;
        b = 0;
        freakshow(i,r,g,b);
        i++;
        i++;
        i++;
        i++;
    }
    
    else if (x > 119 && x < 130) {
            
        r = 0;
        g = 200;
        b = 0;
        freakshow(i,r,g,b);
        i++;
        i++;
        i++;
        i++;
        i++;
    }
    
    else if (x > 129 && x < 140) {
          
        r = 0;
        g = 150;
        b = 50;
        freakshow(i,r,g,b);
    }
    
    else if (x > 139 && x < 150) {
           
        r = 0;
        g = 50;
        b = 150;
        i++;
        freakshow(i,r,g,b);
        i++;
    }
    
    else if (x > 149 && x < 160) {
            
        r = 150;
        g =  0;
        b = 50;
        i++;
        i++;
        freakshow(i,r,g,b);
        i++;
        i++;
    }
    
    else if (x > 159 && x < 170) {
            
        r = 100;
        g = 0;
        b = 150;
        freakshow(i,r,g,b);
        i++;
        i++;
        i++;
        i++;
        
    }
    
    else if (x > 169 && x < 180) {      
      
        r = 50;
        g = 50;
        b = 100;
        i++;
        freakshow(i,r,g,b);
    }
    
    else if (x > 179 && x < 190) {
            
        r = 50;
        g = 100;
        b = 200;
        i++;
        i++;
        i++;
        i++;
        freakshow(i,r,g,b);
    }
    
    else if (x > 189 && x < 199) {
            
        r = 100;
        g = 0;
        b = 200;
        freakshow(i,r,g,b);
        i++;
        
    }
    
    else if (x > 199) {
            
        r = 0;
        g = 0;
        b = 200;
        i++;
        freakshow(i,r,g,b);
        i++;
    }
  }
}

void freakshow(int i, int r, int g, int b) {       // "freakshow gets passed the variables i, r, g, b, This is a complicated technique but makes things
                                                   // way easier to change
    
        pixels.setPixelColor(i, pixels.Color((r),(g),(b))); 
        pixels.show();       
        pixels.setPixelColor((i), pixels.Color((0),(0),(0)));
        i++;
        
        pixels.setPixelColor(i, pixels.Color((r),(g),(b))); 
        pixels.show();       
        pixels.setPixelColor((i), pixels.Color((0),(0),(0)));
        i++;
        i++;
        
        pixels.setPixelColor(i, pixels.Color((r),(g),(b))); 
        pixels.show();       
        pixels.setPixelColor((i), pixels.Color((0),(0),(0)));
        i++;
        i++;
        i++;
}
  
  
  
  
