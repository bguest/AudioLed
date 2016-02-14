#ifndef TWO_COLOR_H
#define TWO_COLOR_H

#include "Effect.h"

class TwoColor : public Effect{

  public:
    TwoColor();
    void run(Sign &sign, EffectData &data);
    void randomize();

  private:
    uint8_t hue[2];

}
#endif