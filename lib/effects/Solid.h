#ifndef SOLID_H
#define SOLID_H

#include "Arduino.h"
#include "Effect.h"

class Solid: public Effect {

  public:
    Solid();
    void run(Sign &sign, EffectData &data);
    void push(IrInput input);
    void setConfig(uint8_t kConfig);

  private:
    Direction direction;

};

#endif
