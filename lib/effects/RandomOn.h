#ifndef RANDOM_ON_H
#define RANDOM_ON_H

#include "Arduino.h"
#include "Effect.h"

class RandomOn : public Effect{

  public:
    RandomOn();
    void run(Sign &sign, EffectData &data);
    void randomize();
    void push(IrInput input);
    void setConfig(uint8_t kConfig);

  private:
    uint8_t onCount;
    bool shouldReset;
    bool turnOn;

};
#endif
