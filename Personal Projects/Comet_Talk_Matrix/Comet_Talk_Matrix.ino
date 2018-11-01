#include <FastLED.h>
#include <MIDI.h>
#define LED_2_PIN 4
#define LED_PIN  3

#define COLOR_ORDER GRB
#define CHIPSET     WS2812

#define BRIGHTNESS 60
#define NUM_LEDS (512)
#define NUM_2_LEDS (450)
// MIDI library init
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

CRGB leds[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
uint8_t global_sat = 0;
uint8_t global_bright = 2;
uint8_t flag = 0;
uint8_t flag1 = 0;
uint8_t sat_flag =0;
uint8_t side_flag = 0;
uint8_t bright_flag =0;
uint8_t hue=0;
uint8_t count =0;
uint8_t gHue = 0;
uint8_t offset_grad = 18;

//#########################################################################################################
// the bitmap for "COMET TALK" 
uint8_t pattern[] = {
          
               //right side up to start, right is top
               // Comet
               0,0,0,0,0,0,0,0, //30
               0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0, //1
               0,0,1,1,1,1,0,0, //2
               0,1,0,0,0,0,1,0, //3
               1,0,0,0,0,0,0,1, //4
               1,0,0,0,0,0,0,1, //5
               0,0,0,0,0,0,0,0, //6
               0,0,1,1,1,1,0,0, //7
               0,1,0,0,0,0,1,0, //8
               1,0,0,0,0,0,0,1, //9
               0,1,0,0,0,0,1,0, //10
               0,0,1,1,1,1,0,0, //11
               0,0,0,0,0,0,0,0, //12
               1,1,1,1,1,1,1,1, //13
               0,0,0,0,0,0,1,0, //14  
               0,0,1,0,0,0,0,0, //15               
               0,0,0,0,0,1,0,0, //16
               0,1,0,0,0,0,0,0, //17
               1,1,1,1,1,1,1,1, //18
               0,0,0,0,0,0,0,0, //19
               1,1,1,1,1,1,1,1, //20
               1,0,0,1,0,0,0,1, //21
               1,0,0,0,1,0,0,1, // 22
               1,0,0,1,0,0,0,1, //23
               0,0,0,0,0,0,0,0, //24
               1,0,0,0,0,0,0,0, // 25
               0,0,0,0,0,0,0,1, //26
               1,1,1,1,1,1,1,1, //27
               0,0,0,0,0,0,0,1, //28
               1,0,0,0,0,0,0,0, //29
                //31
               0,0,0,0,0,0,0,0, //32
                 
               0,0,0,0,0,0,0,0, 
               0,0,0,0,0,0,0,0,              
               0,0,0,0,0,0,0,0, //1
               0,0,0,0,0,0,0,0, //2
               0,0,0,0,0,0,0,0, //3
               0,0,0,0,0,0,0,1, //4
               1,0,0,0,0,0,0,0, //5
               1,1,1,1,1,1,1,1, //6
               1,0,0,0,0,0,0,0, //7
               0,0,0,0,0,0,0,1, //8
               0,0,0,0,0,0,0,0, //9
               1,1,1,1,1,1,0,0, //10
               0,1,0,1,0,0,0,0, //11
               0,0,0,0,1,0,0,1, //12
               0,1,0,1,0,0,0,0, //13
               1,1,1,1,1,1,0,0, //14  
               0,0,0,0,0,0,0,0, //15               
               1,1,1,1,1,1,1,1, //16
               0,0,0,0,0,0,0,1, //17
               1,0,0,0,0,0,0,0, //18
               0,0,0,0,0,0,0,1, //19
               1,0,0,0,0,0,0,0, //20
               0,0,0,0,0,0,0,0, //21
               1,1,1,1,1,1,1,1, // 22
               0,0,0,1,1,0,0,0, //23
               0,0,1,0,0,1,0,0, //24
               0,1,0,0,0,0,1,0, // 25
               1,0,0,0,0,0,0,1, //26
               0,0,0,0,0,0,0,0, //27
               0,0,0,0,0,0,0,0, //28
               0,0,0,0,0,0,0,0, //29 //31
               0,0,0,0,0,0,0,0 //32
};
uint8_t outside[] = {
                      1,1,1,1,1,1,1,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,1,1,1,1,1,1,1
  };

uint8_t middle[] = {
                      0,0,0,0,0,0,0,0,
                      0,0,1,1,1,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,0,0,1,0,0,
                      0,0,1,1,1,1,0,0,
                      0,0,0,0,0,0,0,0                  
  };
uint8_t mouth[] = {
                      0,0,0,1,1,0,0,0,
                      0,0,1,0,0,1,0,0,
                      0,1,0,0,0,0,1,0,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      1,0,0,0,0,0,0,1,
                      0,1,0,0,0,0,1,0,
                      0,0,1,0,0,1,0,0,
                      0,0,0,1,1,0,0,0                
  };
uint8_t inside[] = {
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,1,1,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0
  };
// ##########################################################################################
//                        DEFINE THE SIGN IN QUADRENTS

//left
int left_side_1[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
uint8_t left_num_1 = 17;
int left_side_2[] = {103,104,105,106,107,108,109,110,111,112,113,114,115,116,117};
uint8_t left_num_2 = 15;
int left_side_3[] ={194,195,196,197,198,199,200,201,202,203,204,205,206}; 
int left_num_3 = 13;
int left_side_4[] ={275,276,277,278,279,280,281,282,283,284};
int left_num_4 = 10;
int left_side_5[] ={343,344,345,346,347,348,349};
int left_num_5 = 7;
int left_side_6[] = {401,402,403,404,405};
int left_num_6 = 5;

//top
int top_side_1[] = {17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
uint8_t top_num_1 = 35;
int top_side_2[] = {118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149};
uint8_t top_num_2 = 32;
int top_side_3[] = {207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235};
uint8_t top_num_3 = 29;
int top_side_4[] = {285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308};
uint8_t top_num_4 = 24; 
int top_side_5[] = {350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372};
int top_num_5 = 23;
int top_side_6[] = {406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426};
int top_num_6 = 21;
  
//right
int right_side_1[] = {52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68};
uint8_t right_num_1 = 17;
int right_side_2[] = {150,151,152,153,154,155,156,157,158,159,160,161,162};
uint8_t right_num_2 = 13; 
int right_side_3[] = {236,237,238,239,240,241,242,243,244,245,246,247};
uint8_t right_num_3 = 12;
int right_side_4[] = {309,310,311,312,313,314,315,316,317};
uint8_t right_num_4 = 9;
int right_side_5[] = {373,374,375,376,377,378};
uint8_t right_num_5 = 6;
int right_side_6[] = {427,428,429,430};
uint8_t right_num_6 = 4;

//bottom
int bottom_side_1[] = {69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102};
uint8_t bottom_num_1 = 34;
int bottom_side_2[] = {163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193};
int bottom_num_2 = 31;
int bottom_side_3[] = {248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274};
int bottom_num_3 = 27;
int bottom_side_4[] = {318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342};
int bottom_num_4 = 25;
int bottom_side_5[] = {379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400};
int bottom_num_5 = 22;
int bottom_side_6[] = {431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,448,449};
int bottom_num_6 = 19;
void myProgramChange(byte channel, byte program)
{
  Serial.println(channel);
  }
void setup() 
{
  MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
  MIDI.setHandleStop(handleStop);
  // Do the same for NoteOffs
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleProgramChange(myProgramChange);
  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.addLeds<CHIPSET, LED_2_PIN, COLOR_ORDER>(leds_2, NUM_2_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness( BRIGHTNESS );

}

void loop() {
  
  sat_effect();
  EVERY_N_MILLISECONDS(20 ) { gHue++; }
  EVERY_N_MILLISECONDS(1000 ) { flag_change(); }
  EVERY_N_MILLISECONDS(1000 ) { flag_change(); }
  EVERY_N_MILLISECONDS(10 ) { addGlitter(80); }
  //corners(global_sat,global_bright);
  //FastLED.show();
  //for (int i = 2; i< 16; i++)
    MIDI.read();
}


void display_matrix_right(uint8_t array_in[], uint8_t color, uint8_t back_color, uint8_t sat, uint8_t back_sat, uint8_t bright, uint8_t back_bright)
{
   for (int i = 0; i < 64; i++) 
   {
    for (int j = 0; j < 8; j++) 
    {
      int pos = getLEDpos(i,j);
      if (array_in[pos]  == 1) 
        leds[ pos ] = CHSV( color, sat, bright);      
      else if (array_in[pos] == 0)     
        leds[ pos ] = CHSV( back_color, back_sat, back_bright); 
     color++;    
      }
    }
    FastLED.show();
}
void corners(uint8_t sat, uint8_t bright)
{
  // corners() splits the sign in 4 quadrents around the matrix. good for testing. 
  //left
  //bright = bright +40;
  for(int i=0; i < left_num_1; i++) 
    leds_2[ left_side_1[i] ] = CHSV( gHue, sat, bright);
  for(int i=0; i < left_num_2; i++) 
    leds_2[ left_side_2[i] ] = CHSV( gHue, sat, bright);
  for(int i=0; i < left_num_3; i++) 
    leds_2[ left_side_3[i] ] = CHSV( gHue, sat, bright);
  for(int i=0; i < left_num_4; i++) 
    leds_2[ left_side_4[i] ] = CHSV( gHue, sat, bright);
  for(int i=0; i < left_num_5; i++) 
    leds_2[ left_side_5[i] ] = CHSV( gHue, sat, bright);
  for(int i=0; i < left_num_6; i++) 
    leds_2[ left_side_6[i] ] = CHSV( gHue, sat, bright);


   //top 
  for(int i=0; i < top_num_1; i++) 
    leds_2[ top_side_1[i] ] = CHSV( gHue + 70, sat, bright);
  for(int i=0; i < top_num_2; i++) 
    leds_2[ top_side_2[i] ] = CHSV( gHue + 70, sat, bright);
  for(int i=0; i < top_num_3; i++) 
    leds_2[ top_side_3[i] ] = CHSV( gHue + 70, sat, bright);
  for(int i=0; i < top_num_4; i++) 
    leds_2[ top_side_4[i] ] = CHSV( gHue + 70, sat, bright);
  for(int i=0; i < top_num_5; i++) 
    leds_2[ top_side_5[i] ] = CHSV( gHue + 70, sat, bright);
  for(int i=0; i < top_num_6; i++) 
    leds_2[ top_side_6[i] ] = CHSV( gHue + 70, sat, bright);

  //right
  for(int i=0; i < right_num_1; i++) 
    leds_2[ right_side_1[i] ] = CHSV( gHue + 140, sat, bright);
  for(int i=0; i < right_num_2; i++) 
    leds_2[ right_side_2[i] ] = CHSV( gHue + 140, sat, bright);
  for(int i=0; i < right_num_3; i++) 
    leds_2[ right_side_3[i] ] = CHSV( gHue + 140, sat, bright);
  for(int i=0; i < right_num_4; i++) 
    leds_2[ right_side_4[i] ] = CHSV( gHue + 140, sat, bright);
  for(int i=0; i < right_num_5; i++) 
    leds_2[ right_side_5[i] ] = CHSV( gHue + 140, sat, bright);
  for(int i=0; i < right_num_6; i++) 
    leds_2[ right_side_6[i] ] = CHSV( gHue + 140, sat, bright);

  //bottom
  for(int i=0; i < bottom_num_1; i++) 
    leds_2[ bottom_side_1[i] ] = CHSV( gHue + 190 + 30, sat, bright);
  for(int i=0; i < bottom_num_2; i++) 
    leds_2[ bottom_side_2[i] ] = CHSV(gHue +  190 + 30, sat, bright);
  for(int i=0; i < bottom_num_3; i++) 
    leds_2[ bottom_side_3[i] ] = CHSV( gHue + 190 + 30, sat, bright);
  for(int i=0; i < bottom_num_4; i++) 
    leds_2[ bottom_side_4[i] ] = CHSV( gHue + 190 + 30, sat, bright);
  for(int i=0; i < bottom_num_5; i++) 
    leds_2[ bottom_side_5[i] ] = CHSV( gHue + 190 + 30, sat, bright);
  for(int i=0; i < bottom_num_6; i++) 
    leds_2[ bottom_side_6[i] ] = CHSV( gHue + 190 + 30, sat, bright);  
}

// callbacks
int getLEDpos(int x, int y){ // for a serpentine raster
   int pos;
   if(x & 0x1) { // is X odd
      pos = x * 8 + (8 -1 - y) ;
   } else { // x is even
      pos = x * 8 + y;
   } 
   return pos;
}
void flag_change()
{
  if (flag == 0)
    flag = 1;
  else
    flag = 0;
  }
void flag_change1()
{
  if (flag1 == 0)
    flag1 = 1;
  else
    flag1 = 0;
}
void left_side(uint8_t color, uint8_t sat, uint8_t bright)
{
  for(int i=0; i < left_num_1; i++) 
    leds_2[ left_side_1[i] ] = CHSV( gHue, sat, bright);
  for(int i=0; i < left_num_2; i++) 
    leds_2[ left_side_2[i] ] = CHSV( gHue + 10, sat, bright);
  for(int i=0; i < left_num_3; i++) 
    leds_2[ left_side_3[i] ] = CHSV( gHue+ 15, sat, bright);
  for(int i=0; i < left_num_4; i++) 
    leds_2[ left_side_4[i] ] = CHSV( gHue+ 20, sat, bright);
  for(int i=0; i < left_num_5; i++) 
    leds_2[ left_side_5[i] ] = CHSV( gHue+ 25, sat, bright);
  for(int i=0; i < left_num_6; i++) 
    leds_2[ left_side_6[i] ] = CHSV( gHue+ 30, sat, bright);
  FastLED.show();
}
void right_side(uint8_t color, uint8_t sat, uint8_t bright)
{
  for(int i=0; i < right_num_1; i++) 
    leds_2[ right_side_1[i] ] = CHSV( gHue + 30, sat, bright);
  for(int i=0; i < right_num_2; i++) 
    leds_2[ right_side_2[i] ] = CHSV( gHue + 35, sat, bright);
  for(int i=0; i < right_num_3; i++) 
    leds_2[ right_side_3[i] ] = CHSV( gHue + 40, sat, bright);
  for(int i=0; i < right_num_4; i++) 
    leds_2[ right_side_4[i] ] = CHSV( gHue + 45, sat, bright);
  for(int i=0; i < right_num_5; i++) 
    leds_2[ right_side_5[i] ] = CHSV( gHue + 50, sat, bright);
  for(int i=0; i < right_num_6; i++) 
    leds_2[ right_side_6[i] ] = CHSV( gHue + 55, sat, bright);
    FastLED.show();
}
void top_side(uint8_t color, uint8_t sat, uint8_t bright)
{  for(int i=0; i < top_num_1; i++) 
    leds_2[ top_side_1[i] ] = CHSV( gHue + 60, sat, bright);
  for(int i=0; i < top_num_2; i++) 
    leds_2[ top_side_2[i] ] = CHSV( gHue + 65, sat, bright);
  for(int i=0; i < top_num_3; i++) 
    leds_2[ top_side_3[i] ] = CHSV( gHue + 70, sat, bright);
  for(int i=0; i < top_num_4; i++) 
    leds_2[ top_side_4[i] ] = CHSV( gHue + 75, sat, bright);
  for(int i=0; i < top_num_5; i++) 
    leds_2[ top_side_5[i] ] = CHSV( gHue + 80, sat, bright);
  for(int i=0; i < top_num_6; i++) 
    leds_2[ top_side_6[i] ] = CHSV( gHue + 85, sat, bright);
    FastLED.show();
}
void bottom_side(uint8_t color, uint8_t sat, uint8_t bright)
{
    for(int i=0; i < bottom_num_1; i++) 
    leds_2[ bottom_side_1[i] ] = CHSV( gHue + 90, sat, bright);
  for(int i=0; i < bottom_num_2; i++) 
    leds_2[ bottom_side_2[i] ] = CHSV(gHue +  95, sat, bright);
  for(int i=0; i < bottom_num_3; i++) 
    leds_2[ bottom_side_3[i] ] = CHSV( gHue + 100, sat, bright);
  for(int i=0; i < bottom_num_4; i++) 
    leds_2[ bottom_side_4[i] ] = CHSV( gHue + 105, sat, bright);
  for(int i=0; i < bottom_num_5; i++) 
    leds_2[ bottom_side_5[i] ] = CHSV( gHue + 110, sat, bright);
  for(int i=0; i < bottom_num_6; i++) 
    leds_2[ bottom_side_6[i] ] = CHSV( gHue + 115, sat, bright);
    FastLED.show();
}
