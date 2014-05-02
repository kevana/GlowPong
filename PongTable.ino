#include "SPI.h"
#include "WS2801.h"

/*****************************************************************************
Example sketch for driving WS2801 pixels
*****************************************************************************/

int dataPin = 11;
int clockPin = 13;

// Strip has 25 pixels, only first 10 are used
WS2801 strip = WS2801(10, dataPin, clockPin);

void setup() {
  strip.begin();
  // Initial state is all LEDs off
  strip.show();
}


void loop() {
  cornerTriangles(255);
  rowStep(255);
  colorWipe(Color()
}

// Cycle through rainbow of colors 
void rainbow(uint8_t wait) {
  int i, j;

  for (j=0; j < 256; j++) { // 3 cycles of all 256 colors in the wheel
    for (i=0; i < 10; i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < 10; i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / 10) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < 10; i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

// Triangles of side length 3 are formed in each corner
// Red, green, blue, traveling in a circle for 2 revolutions
void cornerTriangles(uint8_t wait) {
  uint32_t r = Color(255, 0, 0);
  uint32_t g = Color(0, 255, 0);
  uint32_t b = Color(0, 0, 255);
  uint32_t w = Color(255,255,266);
  uint32_t colors[] = {r, g, b};
  
  for (int i=0; i < 6; i++) {
    // Lower left corner
    strip.setPixelColor(0, colors[i]);
    strip.setPixelColor(2, colors[i]);
    strip.setPixelColor(7, colors[i]);
    // Upper corner
    strip.setPixelColor(4, colors[(i+1)%3]);
    strip.setPixelColor(6, colors[(i+1)%3]);
    strip.setPixelColor(9, colors[(i+1)%3]);
    // Lower right corner
    strip.setPixelColor(1, colors[(i+2)%3]);
    strip.setPixelColor(3, colors[(i+2)%3]);
    strip.setPixelColor(8, colors[(i+2)%3]);
    // Center pixel
    strip.setPixelColor(5, w);
    strip.show();
    delay(wait);
  }
}

// Rows are stepped through one at a time, then built
void rowStep(uint8_t wait) {
  uint32_t r = Color(255, 0, 0);
  uint8_t rows[][4] = {{0,1,2,3}, {4,5,6}, {7,8}, {9}};
  for (int i = 0; i < 4; i++) {
    clearPixels();
    for (int j = 0; j < 4-i; j++) {
      strip.setPixelColor(rows[i][j], r);
    }
    strip.show();
    delay(wait);
  }
}

// Clear all pixels
void clearPixels() {
  for (int i = 0; i < 10; i++) {
    strip.setPixelColor(i, 0,0,0);
  }
}
