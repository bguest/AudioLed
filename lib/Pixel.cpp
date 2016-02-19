#include "Pixel.h"
// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
void Pixel::push(){
  hue[2] = hue[1];
  hue[1] = hue[0];
}

uint32_t Pixel::color() {
  uint16_t b = brightness >> 8;
  uint8_t h = hue[0] >> 8;
  if(h < 85) {
    return Color( h*3*b/255, (255 - h*3)*b/255, 0);
  }
  else if(h < 170) {
    h -= 85;
    return Color((255 - h*3)*b/255, 0, h*3*b/255);
  }
  else {
    h -= 170;
    return Color(0, h*3*b/255, (255 - h*3)*b/255);
  }
}

