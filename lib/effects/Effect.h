#ifndef EFFECT_H
#define EFFECT_H

#include "Sign.h"
#include "EffectData.h"
#include "Remote.h"

class Effect{
  public:
    Effect();
    virtual void push(IrInput input);
    virtual void run(Sign &sign, EffectData &data);
    virtual void randomize();
};
#endif
