#ifndef SIGN_H
#define SIGN_H

#include "Pixel.h"

const uint8_t LED_WIDTH = 7;
const uint8_t LED_HEIGHT = 5;

class Sign{
  public:
    void init();
    void off();
    Pixel pixels[LED_WIDTH][LED_HEIGHT];
    Pixel* pixelAtIndex(uint8_t index);
    Pixel* randomPixel();

  private:
    uint8_t ledXY[LED_WIDTH*LED_HEIGHT][2] = {
      {0,0}, {0,1}, {0,2}, {0,3}, {0,4},
      {1,4}, {1,3}, {1,2}, {1,1}, {1,0},
      {2,0}, {2,1}, {2,2}, {2,3}, {2,4},
      {3,4}, {3,3}, {3,2}, {3,1}, {3,0},
      {4,0}, {4,1}, {4,2}, {4,3}, {4,4},
      {5,4}, {5,3}, {5,2}, {5,1}, {5,0},
      {6,0}, {6,1}, {6,2}, {6,3}, {4,4}
    };
};
#endif
