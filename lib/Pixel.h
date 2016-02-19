#ifndef PIXEL_H
#define PIXEL_H

#include "Arduino.h"

class Pixel{
  public:
    bool isOn;
    uint16_t hue[3];
    uint16_t brightness;
    uint8_t x;
    uint8_t y;
    uint32_t color();

    void push();
};
#endif
