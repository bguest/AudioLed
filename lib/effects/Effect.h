#ifndef EFFECT_H
#define EFFECT_H

#include "EffectData.h"

class Effect{
  public:
    Effect();
    virtual void run(Sign &sign, EffectData &data);
    virtual void randomize();
};
#endif