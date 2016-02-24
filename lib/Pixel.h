#ifndef PIXEL_H
#define PIXEL_H

//#define DRIZLY

#include "Arduino.h"

typedef enum _Direction{
  Up, Off, Down
} Direction;

class Pixel{
  public:
    Pixel();
    Direction direction;
    uint16_t hue[3];
    uint16_t saturation;
    uint16_t value;
    uint8_t x;
    uint8_t y;
    uint32_t color();

    void push();
};
#endif
