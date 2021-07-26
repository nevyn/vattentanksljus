#include <Adafruit_NeoPixel.h>

int ledPin = 10;
int ledCount = 16;

unsigned long onFor = 8*60*60*1000;
unsigned long offFor = 16*60*60*1000;
unsigned long dayLength = onFor + offFor;

Adafruit_NeoPixel strip(ledCount, ledPin, NEO_GRB + NEO_KHZ800);



void setup() 
{  
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip.show();            // Turn OFF all pixels ASAP
}

void loop() {
  bool on = true;
  unsigned long now = millis();
  unsigned long timeIntoDay = now % dayLength;
  if(timeIntoDay > onFor)
  {
    on = false;
  }

  if(on) {
    strip.setBrightness(100);
    rainbow(20);
  } else {
    strip.setBrightness(0);
    strip.show();
  }    
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void blinky(uint8_t wait) {
  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.setPixelColor(1, strip.Color(0, 255, 0));
  strip.show();
  delay(wait);
  strip.setPixelColor(1, strip.Color(255, 0, 0));
  strip.setPixelColor(0, strip.Color(0, 255, 0));
  strip.show();
  delay(wait);
}
