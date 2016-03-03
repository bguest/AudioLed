#ifndef WAVE0_H
#define WAVE0_H

#include "Arduino.h"

class Wave0: public Effect{
  public:
    Wave0();
    void randomize();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);

  private:
    bool isFixedBoundary;
    uint16_t forceConstant;
    uint32_t velocityConstant;
    unsigned long time[2];
    void wave(Sign &sign, uint8_t x, uint8_t y, int32_t deltaT2);
    uint8_t influence;
};

#endif
