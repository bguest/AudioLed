#ifndef SINGLE_FADE_H
#define SINGLE_FADE_H

#include "Effect.h"

class SingleFade : public Effect{

  public:
    SingleFade();
    void run(Sign &sign, EffectData &data);
    void randomize();

  private:
    uint8_t activePixel[2];
    unsigned long lastStep;
    uint16_t maxHueStep;

    void updateActive();
};
#endif
