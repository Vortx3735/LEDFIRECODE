#include <Wire.h>
#include <FastLED.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     5

#define NUM_LEDS    64
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define BRIGHTNESS  200
#define FRAMES_PER_SECOND 60
CRGB leds[64];
boolean didRun = false;
int DEFAULT_BIRGHTNESS = 200;
boolean isRed = true; 

#define COOLING  55

#define SPARKING 120
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(60, 5, NEO_GRB + NEO_KHZ800);
CRGBPalette16 gPal;
bool gReverseDirection = false;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Green,  CRGB::Green);
  pixels.begin();
  
  Wire.begin(5);
  Wire.onReceive(Receive);
 

////--bootup sequence starts


  
//bootup sequence ends
} 
void loop()
{
  

}
void Receive()
{
  
    byte c = Wire.read();
    Serial.println(c);
    
 
      if(c == 10)
      {
    autotom();
       
      
        }
     if(c == 30)
     {
         random16_add_entropy( random());
         VortexFire();
         FastLED.show(); //1 display this frame
         FastLED.delay(1000 / 60);
     } 
    
  
    }
 

void VortexFire()
{

  static byte heat[NUM_LEDS];

  // Step 1.  Cooling
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heating
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  sparks
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  MapLED_PINg
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
void autotom()
{
    pixels.clear();
for(int i = 0;i<2;i++)
{
for(int e = 0; e < NUM_LEDS;e++)
  {
    pixels.setPixelColor(e,0,255,0);
    pixels.show();
    delay(10);
  }
   for(int e = 0; e < NUM_LEDS;e++)
  {
    pixels.setPixelColor(e,0,0,255);
    pixels.show();
   delay(10);
  }
}
 
}

